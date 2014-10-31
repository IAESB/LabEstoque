#ifndef WIN32
#	include <unistd.h>
#endif
#include <stdlib.h>
#include <direct.h>
#include <signal.h>
#include <iostream>
#include <fstream>
#include <boost/thread.hpp>
#include <mongoose/Server.h>
#include "control/materialcontroller.h"
#include "control/entradacontroller.h"
#include "control/saidacontroller.h"

using namespace std;
using namespace Mongoose;

#define ARQ_LOCK "tmp/labEstoque.lock"

void configureDao(){
    DaoPrt dao = Dao::getInstance("tcp://localhost:3306", "root", "root", "estoque_lab_quimica");
}

volatile static bool running = true;

extern "C" __declspec(dllexport) void handle_signal(int sig)
{
    if (running) {
        cout << "Signal: "<< sig << endl << "Exiting..." << endl;
        running = false;
    }
}

bool verificaArqLock()
{
	ifstream arq(ARQ_LOCK);
	return ! arq.is_open();
}

#ifdef SHARED_LIB
int run(char** argv)
#else
int main(int argc, char** argv)
#endif
{
	if (argc < 2)
	{
		std::cerr << "Usage: labStoqueServer <port>\n";
		return 1;
	}

	signal(SIGINT, handle_signal);

	string path = argv[0];
	path = path.substr(0, path.rfind("\\"));
#ifdef _MSC_VER
	path = path.substr(0, path.rfind("\\"));
	path = path.substr(0, path.rfind("\\"));
#endif
	chdir(path.c_str());

    configureDao();
    cout << "Server Up!" << endl;
    Server server(stoi(argv[1]), "WebContent");
    server.setOption("enable_directory_listing", "false");
    MaterialController material;
    EntradaController entrada;
    SaidaController saida;
    server.registerController(&material);
    server.registerController(&entrada);
    server.registerController(&saida);

    server.start();
	
	mkdir("tmp");
	ofstream arq(ARQ_LOCK);
	arq << "running" << endl;
	arq.close();

    while (running) {
#ifdef WIN32
        Sleep(2000);
#else
        sleep(2);
#endif
		if (verificaArqLock())
			handle_signal(0);
    }

	cout << "Server Down!" << endl;
    return 0;
}

extern "C" __declspec(dllexport) int startServer(int argc, char** argv)
{
#ifdef SHARED_LIB
	boost::thread thread(run, argv);
#endif
	return 0;
}
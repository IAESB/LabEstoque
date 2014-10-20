#ifndef WIN32
#	include <unistd.h>
#endif
#include <stdlib.h>
#include <direct.h>
#include <signal.h>
#include <iostream>
#include <mongoose/Server.h>
#include "control/materialcontroller.h"
#include "control/entradacontroller.h"
#include "control/saidacontroller.h"

using namespace std;
using namespace Mongoose;

void configureDao(){
    DaoPrt dao = Dao::getInstance("tcp://localhost:3306", "root", "root", "estoque_lab_quimica");
}

volatile static bool running = true;

void handle_signal(int sig)
{
    if (running) {
        cout << "Exiting..." << endl;
        running = false;
    }
}

int main(int argc, char** argv)
{
	//chdir("..");
    configureDao();
    cout << "Server Up!" << endl;
    Server server(8080, "WebContent");
    server.setOption("enable_directory_listing", "false");
    MaterialController material;
    EntradaController entrada;
    SaidaController saida;
    server.registerController(&material);
    server.registerController(&entrada);
    server.registerController(&saida);

    server.start();

    while (running) {
#ifdef WIN32
        Sleep(10000);
#else
        sleep(10);
#endif
    }

    return 0;
}


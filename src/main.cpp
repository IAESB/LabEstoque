#ifndef WIN32
#   define DLL_EXPORT
#	include <unistd.h>
#   include <sys/stat.h>
#else
#   define DLL_EXPORT __declspec(dllexport)
#   include <direct.h>
#endif
#include <stdlib.h>
#include <signal.h>
#include <iostream>
#include <fstream>
#include <boost/thread.hpp>
#include "boost/program_options.hpp" 
#include <mongoose/Server.h>
#include "control/materialcontroller.h"
#include "control/entradacontroller.h"
#include "control/saidacontroller.h"
#include "control/pesquisacontroller.h"

using namespace std;
using namespace Mongoose;
using namespace boost::program_options;


namespace
{
	const size_t SUCCESS = 0;
	const size_t ERROR_IN_COMMAND_LINE = 1;
	const size_t ERROR_IN_FILE_LOCK = 2;
#ifndef _MSC_VER
    const size_t ERROR_UNHANDLED_EXCEPTION = 3;
#endif


	const char* ARQ_LOCK = "tmp/labEstoque.lock";

    void configureDao(const string& url, const string& user, const string& password, const string& dataBase){
		DaoPrt dao = Dao::getInstance(url, user, password, dataBase);
	}

	volatile static bool running = true;

    extern "C" DLL_EXPORT void handle_signal(int sig)
	{
		cout << "Signal: " << sig << endl << "Exiting..." << endl;
		running = false;
	}

	bool verificaArqLock()
	{
		ifstream arq(ARQ_LOCK);
		return !arq.is_open();
	}

} // namespace

int main(int argc, char** argv)
{
	signal(SIGINT, handle_signal);
	signal(SIGSEGV, handle_signal);
	signal(SIGABRT, handle_signal);

	namespace po = boost::program_options;

	/** Define and parse the program options
	*/
	po::options_description desc("Options");
	try
	{
		desc.add_options()
			("help,h", "Print help messages")
			("port,p", po::value<int>(), "<PORT> set port to open socket ex.: 8080")
			("webdir,w", po::value<string>(), "<DIR> set dir to web content ex.: ../WebContent")
			("url-data-base,r", po::value<string>(), "<URL> set url to connect data base ex.: tcp://localhost:3306")
			("user-data-base,u", po::value<string>(), "<USER> set user connect data base ex.: root")
			("passowrd-data-base,s", po::value<string>(), "<PASSWORD> set user connect data base ex.: root")
			("data-base,d", po::value<string>(), "<DATA BASE> set data base ex.: estoque_lab");

		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, desc),
			vm); // can throw 
		po::notify(vm); // throws on error, so do after help in case there are any problems 

		if (vm.count("help"))
		{
			std::cout << "Basic Command Line Parameter App" << std::endl
				<< desc << std::endl;
			return SUCCESS;
		}
		int porta = 8080;
		if (vm.count("port"))
		{
			porta = vm["port"].as<int>();
			std::cerr << "Usando porta: " << porta << endl;
		}
		string webDir = "../WebContent";
		if (vm.count("webdir"))
		{
			webDir = vm["webdir"].as<string>();
		}
		cout << "WebDir: " << webDir << endl;

        mkdir("tmp", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		ofstream arq(ARQ_LOCK);
		if (!arq.good()){
			cerr << "problemas ao criar o arquivo de trava: " << ARQ_LOCK << endl;
			return ERROR_IN_FILE_LOCK;
		}
		arq << "running" << endl;
		arq.close();

		configureDao(vm.count("url-data-base") ? vm["url-data-base"].as<string>() : "tcp://localhost:3306", 
					 vm.count("user-data-base") ? vm["user-data-base"].as<string>() : "root", 
					 vm.count("passowrd-data-base") ? vm["passowrd-data-base"].as<string>() : "root", 
					 vm.count("data-base") ? vm["data-base"].as<string>() : "lab_estoque");
		cout << "Server Up!" << endl;
		Server server(porta, webDir.c_str());
		server.setOption("enable_directory_listing", "false");
		MaterialController material;
		EntradaController entrada;
		SaidaController saida;
        PesquisaController relatorio;
		server.registerController(&material);
		server.registerController(&entrada);
		server.registerController(&saida);
		server.registerController(&relatorio);

		server.start();		

		while (running) {
            boost::this_thread::sleep(boost::posix_time::seconds(1));
			if (verificaArqLock())
				handle_signal(0);
		}

        server.stop();
		cout << "Server Down!" << endl;
	}
	catch (po::error& e)
	{
		std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
		std::cerr << desc << std::endl;
		return ERROR_IN_COMMAND_LINE;
	}
	catch (std::exception& e)
	{
		std::cerr << "Unhandled Exception reached the top of main: "
			<< e.what() << ", application will now exit" << std::endl;
		return ERROR_UNHANDLED_EXCEPTION;

	}

	return SUCCESS;
}

extern "C" DLL_EXPORT int startServer(int argc, char** argv)
{
#ifdef SHARED_LIB
	boost::thread thread(run, argv);
#endif
	return 0;
}

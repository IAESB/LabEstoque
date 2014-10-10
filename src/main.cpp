#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <iostream>
#include <mongoose/Server.h>
#include "control/materialcontroller.h"
#include "control/entradacontroller.h"

using namespace std;
using namespace Mongoose;

void configureDao(){
    DaoPrt dao = Dao::getInstance("tcp://localhost:3306", "root", "root", "estoque_lab_quimica");
    if( ! dao->isConnected())
        dao->reconnect();
}

int main(int argc, char** argv)
{
    configureDao();
    cout << "Hello World!" << endl;
    Server server(8080, "WebContent");
    server.setOption("enable_directory_listing", "false");
    MaterialController material;
    EntradaController entrada;
    server.registerController(&material);
    server.registerController(&entrada);

    server.start();

    while (true) {
        configureDao();
        sleep(10);
    }

    return 0;
}


#include <iostream>
#include "model/materialmodel.h"
using namespace std;

void configureDao()
{
    DaoPrt dao = Dao::getInstance("tcp://127.0.0.1:3306", "root", "root", "estoque_lab_quimica");
}

int main(int argc, char** argv)
{
    configureDao();
    Mateiral mat;
    MaterialModel matModel;
    matModel.salvarMaterial(mat);
    ListMateiral listMat = matModel.getListMaterial();
    matModel.alterarMaterial(mat);
    matModel.excluirMaterial(mat);

    cout << "Hello World!" << endl;
    return 0;
}


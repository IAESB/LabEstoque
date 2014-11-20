#ifndef LABORATORIO_H
#define LABORATORIO_H

#include <iostream>
#include <vector>
#include <memory>
#include <soci/row.h>
using namespace std;

class Laboratorio
{
    int id;
    string nome;
public:
    Laboratorio();
    Laboratorio(int id);
    Laboratorio(soci::row& rs);
    string getSqlInsert();
    int getId() const;
    void setId(int value);
    string getNome() const;
    void setNome(const string &value);
};
typedef shared_ptr<Laboratorio> LaboratorioPtr;
typedef shared_ptr< vector<LaboratorioPtr> > LaboratorioList;
#endif // LABORATORIO_H

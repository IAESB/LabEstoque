#ifndef SOLICITANTE_H
#define SOLICITANTE_H

#include <iostream>
#include <memory>
#include <vector>
#include <cppconn/resultset.h>
using namespace std;

class Solicitante
{
    int id;
    string nome;
    string matricula;
public:
    Solicitante();
    Solicitante(int id);
    Solicitante(sql::ResultSet& rs);
    string getSqlInsert();
    int getId() const;
    void setId(int value);
    string getNome() const;
    void setNome(const string &value);
    string getMatricula() const;
    void setMatricula(const string &value);
};
typedef shared_ptr<Solicitante> SolicitantePtr;
typedef shared_ptr< vector<SolicitantePtr> > SolicitanteList;

#endif // SOLICITANTE_H

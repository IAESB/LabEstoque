#ifndef MATEIRAL_H
#define MATEIRAL_H

#include <iostream>
#include <vector>
#include <cppconn/resultset.h>
#include "grupo.h"
using namespace std;

class Mateiral
{
    int id;
    string nome;
    string formula;
    string lote;
    string validade;
    GrupoPtr grupo;
public:
    Mateiral();
    Mateiral(sql::ResultSet& rs);

    string getSqlInsert();
    string getSqlUpdate();
    string getSqlDelete();
    string getValidade() const;
    void setValidade(const string &value);
    string getLote() const;
    void setLote(const string &value);
    string getFormula() const;
    void setFormula(const string &value);
    string getNome() const;
    void setNome(const string &value);
    int getId() const;
    void setId(int value);
    GrupoPtr getGrupo() const;
    void setGrupo(const GrupoPtr &value);
};

typedef shared_ptr<Mateiral> MateiralPtr;
typedef shared_ptr< vector<Mateiral> > ListMateiral;

#endif // MATEIRAL_H

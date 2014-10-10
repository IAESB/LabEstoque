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
    string descricao;
    string imagem;
    GrupoPtr grupo;
public:
    Mateiral();
    Mateiral(const int& id);
    Mateiral(sql::ResultSet& rs);

    string getSqlInsert();
    string getSqlUpdate();
    string getSqlDelete();
    string getDescricao() const;
    void setDescricao(const string &value);
    string getNome() const;
    void setNome(const string &value);
    int getId() const;
    void setId(int value);
    GrupoPtr getGrupo() const;
    void setGrupo(const GrupoPtr &value);
    string getImagem() const;
    void setImagem(const string &value);
};

typedef shared_ptr<Mateiral> MateiralPtr;
typedef shared_ptr< vector<MateiralPtr> > MateiralList;

#endif // MATEIRAL_H

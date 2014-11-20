#ifndef LOTE_H
#define LOTE_H

#include <string>
#include <soci/row.h>
#include <vector>
#include <memory>
using namespace std;

class Lote
{
    int id;
    string nome;
    string validade;
    int quantidade;
public:
    Lote();
    Lote(const int& id);
    Lote(soci::row& rs);
    string getSqlInsert();
    string getSqlUpdate();
    string getSqlDelete();
    int getId() const;
    void setId(int value);
    string getNome() const;
    void setNome(const string &value);
    string getValidade() const;
    void setValidade(const string &value);
    int getQuantidade() const;
    void setQuantidade(int value);
};
typedef shared_ptr<Lote> LotePtr;
typedef shared_ptr< vector<LotePtr> > LoteList;

#endif // LOTE_H

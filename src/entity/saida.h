#ifndef SAIDA_H
#define SAIDA_H

#include "usuario.h"
#include "mateiral.h"
#include "laboratorio.h"
#include "solicitante.h"
#include "saidadematerial.h"

class SaidaDeMaterial;
typedef shared_ptr<SaidaDeMaterial> SaidaDeMaterialPtr;
typedef shared_ptr< vector<SaidaDeMaterialPtr> > SaidaDeMaterialList;

class Saida
{
    int id;
    string data;
    string anotacao;
    UsuarioPtr usuario;
    LaboratorioPtr laboratorio;
    SolicitantePtr solicitante;
    SaidaDeMaterialList materiais;
public:
    Saida();
    Saida(int id);
    Saida(soci::row& rs);
	string getSqlInsert();
	string getSqlUpdate();
	string getSqlDelete();
    int getId() const;
    void setId(int value);
    string getData() const;
    void setData(const string &value);
    UsuarioPtr getUsuario() const;
    void setUsuario(const UsuarioPtr &value);
    LaboratorioPtr getLaboratorio() const;
    void setLaboratorio(const LaboratorioPtr &value);
    SolicitantePtr getSolicitante() const;
    void setSolicitante(const SolicitantePtr &value);
    SaidaDeMaterialList getSaidaDeMaterialList() const;
    void setSaidaDeMateriais(const SaidaDeMaterialList &value);
    string getAnotacao() const;
    void setAnotacao(const string &value);
};
typedef shared_ptr<Saida> SaidaPtr;
typedef shared_ptr< vector<SaidaPtr> > SaidaList;

#endif // SAIDA_H

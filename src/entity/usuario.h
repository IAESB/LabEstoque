#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>
#include <memory>
using namespace std;

class Usuario
{
    int id;
    string nome;
    string senha;
public:
    Usuario();
    int getId() const;
    void setId(int value);
    string getNome() const;
    void setNome(const string &value);
    string getSenha() const;
    void setSenha(const string &value);
};
typedef shared_ptr<Usuario> UsuarioPtr;

#endif // USUARIO_H

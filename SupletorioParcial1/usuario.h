#ifndef USUARIO_H
#define USUARIO_H
#include <vehiculo.h>
#include <list>
#include <iostream>

using namespace std;

class usuario
{
public:
    usuario();
    list <vehiculo> VehiculosRegistrados;
    void SetContrasena(string);
    void SetNombreUsuario(string);
    string GetNombreUsuario();
    string GetContasena();
private:
    string NombreUsuario;
    string contrasena;
};

#endif // USUARIO_H

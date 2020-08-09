#include "usuario.h"

usuario::usuario()
{

}

void usuario::SetContrasena(string ContrasenaEntrante)
{
    contrasena=ContrasenaEntrante;
}

void usuario::SetNombreUsuario(string NombreUsuarioEntrante)
{
    NombreUsuario=NombreUsuarioEntrante;
}

string usuario::GetNombreUsuario()
{
    return NombreUsuario;
}

string usuario::GetContasena()
{
    return contrasena;
}

#include "DatosUsuarios.h"
#include "Usuarios.h"
#include <cstring>
#include <iostream>

using std::string;

DatosUsuarios::DatosUsuarios(int valorUsuario, int valorContra)
{
    establecerUsuario( valorUsuario );
    establecerContra( valorContra );
}
int DatosUsuarios::obtenerUsuario() const
{
   return usuario;
}
void DatosUsuarios::establecerUsuario( int valorUsuario )
{
   usuario = valorUsuario;
}
int DatosUsuarios::obtenerContra() const
{
   return contra;
}
void DatosUsuarios::establecerContra( int valorContra )
{
    contra=valorContra;
}

DatosUsuarios::~DatosUsuarios()
{
    //dtor
}

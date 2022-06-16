#include "DatosJugador.h"
#include <cstring>
#include <iostream>

using std::string;

DatosJugador::DatosJugador(int valorCodigo, string valorNombre)
{
    establecerCodigo( valorCodigo );
    establecerNombre( valorNombre );
}

int DatosJugador::obtenerCodigo() const
{
   return codigo;
}
void DatosJugador::establecerCodigo( int valorCodigo )
{
   codigo = valorCodigo;
}
/*---*/
string DatosJugador::obtenerNombre() const
{
   return nombre;
}
void DatosJugador::establecerNombre( string primerNombre )
{
    const char *valorNombre = primerNombre.data();
    int longitud = strlen( valorNombre );
    longitud = ( longitud < 15 ? longitud : 14 );
    strncpy( nombre, valorNombre, longitud );

    primerNombre[ longitud ] = '\0';

}
DatosJugador::~DatosJugador()
{
    //dtor
}

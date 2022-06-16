#include "DatosEquipo.h"
#include <cstring>
#include <iostream>

using std::string;

DatosEquipo::DatosEquipo( int valorCodigo, string valorNombre )
{
    establecerCodigo( valorCodigo );
    establecerNombre( valorNombre );
}
int DatosEquipo::obtenerCodigo() const
{
   return codigo;
}
void DatosEquipo::establecerCodigo( int valorCodigo )
{
   codigo = valorCodigo;
}
/*---*/
string DatosEquipo::obtenerNombre() const
{
   return nombre;
}
void DatosEquipo::establecerNombre( string primerNombre )
{
    const char *valorNombre = primerNombre.data();
    int longitud = strlen( valorNombre );
    longitud = ( longitud < 15 ? longitud : 14 );
    strncpy( nombre, valorNombre, longitud );

    primerNombre[ longitud ] = '\0';

}

DatosEquipo::~DatosEquipo()
{
    //dtor
}

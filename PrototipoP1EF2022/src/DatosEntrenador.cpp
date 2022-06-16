#include "DatosEntrenador.h"
#include "Entrenador.h"
#include <cstring>
#include <iostream>

using std::string;

DatosEntrenador::DatosEntrenador(int valorCodigo, string valorNombre, string valorNombre2, string valorApellido, string valorApellido2, string valorFecha)
{
    establecerCodigo( valorCodigo );
    establecerNombre( valorNombre );
    establecerNombre2( valorNombre2 );
    establecerApellido( valorApellido );
    establecerApellido2( valorApellido2 );
    establecerFecha( valorFecha );
}

int DatosEntrenador::obtenerCodigo() const
{
   return codigo;
}
void DatosEntrenador::establecerCodigo( int valorCodigo )
{
   codigo = valorCodigo;
}
/*---*/
string DatosEntrenador::obtenerNombre() const
{
   return nombre;
}
void DatosEntrenador::establecerNombre( string primerNombre )
{
    const char *valorNombre = primerNombre.data();
    int longitud = strlen( valorNombre );
    longitud = ( longitud < 15 ? longitud : 14 );
    strncpy( nombre, valorNombre, longitud );

    primerNombre[ longitud ] = '\0';

}
string DatosEntrenador::obtenerNombre2() const
{
   return nombre2;
}
void DatosEntrenador::establecerNombre2( string segundoNombre )
{
    const char *valorNombre2 = segundoNombre.data();
    int longitud = strlen( valorNombre2 );
    longitud = ( longitud < 15 ? longitud : 14 );
    strncpy( nombre2, valorNombre2, longitud );

    segundoNombre[ longitud ] = '\0';

}
string DatosEntrenador::obtenerApellido() const
{
   return apellido;
}
void DatosEntrenador::establecerApellido( string apellidoString )
{
    const char *valorApellido = apellidoString.data();
    int longitud = strlen( valorApellido );
    longitud = ( longitud < 15 ? longitud : 14 );
    strncpy( apellido, valorApellido, longitud );

    apellido[ longitud ] = '\0';
}
/*-----*/
string DatosEntrenador::obtenerApellido2() const
{
   return apellido2;
}
void DatosEntrenador::establecerApellido2( string apellidoString2 )
{
    const char *valorApellido2 = apellidoString2.data();
    int longitud = strlen( valorApellido2 );
    longitud = ( longitud < 15 ? longitud : 14 );
    strncpy( apellido2, valorApellido2, longitud );

    apellido2[ longitud ] = '\0';
}
string DatosEntrenador::obtenerFecha() const
{
   return fecha;
}
void DatosEntrenador::establecerFecha( string fechastring )
{
    const char *valorFecha = fechastring.data();
    int longitud = strlen( valorFecha );
    longitud = ( longitud < 15 ? longitud : 14 );
    strncpy( fecha, valorFecha, longitud );

    fechastring[ longitud ] = '\0';
}

DatosEntrenador::~DatosEntrenador()
{
    //dtor
}

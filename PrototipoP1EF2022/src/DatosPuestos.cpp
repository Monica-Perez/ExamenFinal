#include "DatosPuestos.h"
#include <cstring>
#include <iostream>

using std::string;

DatosPuestos::DatosPuestos(int valorCodigo, string valorNombre, double valorSalario)
{
    establecerCodigo( valorCodigo );
    establecerNombre( valorNombre );
    establecerSalario( valorSalario );
}

int DatosPuestos::obtenerCodigo() const
{
   return codigo;
}
void DatosPuestos::establecerCodigo( int valorCodigo )
{
   codigo = valorCodigo;
}
/*---*/
string DatosPuestos::obtenerNombre() const
{
   return nombre;
}
void DatosPuestos::establecerNombre( string primerNombre )
{
    const char *valorNombre = primerNombre.data();
    int longitud = strlen( valorNombre );
    longitud = ( longitud < 15 ? longitud : 14 );
    strncpy( nombre, valorNombre, longitud );

    primerNombre[ longitud ] = '\0';
}
double DatosPuestos::obtenerSalario() const
{
   return salario;
}
void DatosPuestos::establecerSalario( double valorSalario )
{
   salario = valorSalario;
}
DatosPuestos::~DatosPuestos()
{
    //dtor
}

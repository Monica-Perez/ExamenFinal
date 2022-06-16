#ifndef DATOSPUESTOS_H
#define DATOSPUESTOS_H

#include <iostream>
using std::string;

class DatosPuestos
{
    public:
        DatosPuestos( int = 0, string = "", double = 0.0 );
        virtual ~DatosPuestos();

        void establecerCodigo( int );
        int obtenerCodigo() const;

        void establecerNombre( string );
        string obtenerNombre() const;

        void establecerSalario( double );
        double obtenerSalario() const;


    protected:

    private:
        int codigo;
        char nombre[ 15 ];
        double salario;

};

#endif // DATOSPUESTOS_H

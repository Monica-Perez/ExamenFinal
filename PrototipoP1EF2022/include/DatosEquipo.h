#ifndef DATOSEQUIPO_H
#define DATOSEQUIPO_H

#include <iostream>
using std::string;

class DatosEquipo
{
    public:
        virtual ~DatosEquipo();
        DatosEquipo( int = 0, string = "" );

        void establecerCodigo( int );
        int obtenerCodigo() const;

        void establecerNombre( string );
        string obtenerNombre() const;

    protected:

    private:
        int codigo;
        char nombre[ 15 ];
};

#endif // DATOSEQUIPO_H

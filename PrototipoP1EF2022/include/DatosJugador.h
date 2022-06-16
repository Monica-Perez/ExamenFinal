#ifndef DATOSJUGADOR_H
#define DATOSJUGADOR_H

#include <iostream>
using std::string;

class DatosJugador
{
    public:
        virtual ~DatosJugador();
        DatosJugador( int = 0, string = "" );

        void establecerCodigo( int );
        int obtenerCodigo() const;

        void establecerNombre( string );
        string obtenerNombre() const;


    protected:

    private:
        int codigo;
        char nombre[ 15 ];
};

#endif // DATOSJUGADOR_H

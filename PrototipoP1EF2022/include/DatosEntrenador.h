#ifndef DATOSENTRENADOR_H
#define DATOSENTRENADOR_H

#include <iostream>
using std::string;

class DatosEntrenador
{
    public:
        virtual ~DatosEntrenador();
        DatosEntrenador( int = 0, string = "", string = "", string = "", string = "", string = "" );

        void establecerCodigo( int );
        int obtenerCodigo() const;

        void establecerNombre( string );
        string obtenerNombre() const;

        void establecerNombre2( string );
        string obtenerNombre2() const;

        void establecerApellido( string );
        string obtenerApellido() const;

        void establecerApellido2( string );
        string obtenerApellido2() const;

        void establecerFecha( string );
        string obtenerFecha() const;

    protected:

    private:
        int codigo;
        char nombre[ 15 ];
        char nombre2[ 15 ];
        char apellido[ 15 ];
        char apellido2[ 15 ];
        char fecha[ 15 ];
};

#endif // DATOSENTRENADOR_H

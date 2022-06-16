#include "Procesos.h"
#include "DatosEntrenador.h"
#include "DatosPuestos.h"
#include "DatosEquipo.h"
#include "DatosJugador.h"
#include <iostream>
#include <ctime>
#include <vector>

using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::ios;
using std::left;
using std::right;
using std::fixed;
using std::showpoint;

#include <fstream>
using std::ofstream;
using std::ostream;
using std::fstream;

#include <iomanip>
using std::setw;
using std::setprecision;
#include <cstdlib>

int opcionPro();
void consultarRegistroPro( fstream& );
void mostrarLineaPantallaPro( const DatosEntrenador &);

void consultarRegistroPro2( fstream& );
void mostrarLineaPantallaPro2( const DatosPuestos &);

void consultarRegistroPro3( fstream& );
void mostrarLineaPantallaPro3( const DatosEquipo &);

void consultarRegistroPro4( fstream& );
void mostrarLineaPantallaPro4( const DatosJugador &);

Procesos::Procesos()
{
    fstream creditoEntradaSalida( "Entrenador.dat", ios::in | ios::out | ios::binary);
    fstream creditoEntradaSalida2( "Puestos.dat", ios::in | ios::out | ios::binary);
    fstream creditoEntradaSalida3( "Equipo.dat", ios::in | ios::out | ios::binary);
    fstream creditoEntradaSalida4( "Jugador.dat", ios::in | ios::out | ios::binary);
    if ( !creditoEntradaSalida && creditoEntradaSalida2 && creditoEntradaSalida3 && creditoEntradaSalida4 ) {
        cerr << "No se pudo abrir el archivo." << endl;
    }
    enum Opciones { entrenador = 1, puestos, equipo, jugador, FIN };
    int opcion;
    while (( opcion = opcionPro() ) != FIN)
    {
        switch ( opcion ) {
            case entrenador:
                {
                    consultarRegistroPro(creditoEntradaSalida);
                }
            break;
            case puestos:
                {
                    consultarRegistroPro2(creditoEntradaSalida2);
                }
            break;
            case equipo:
                {
                    consultarRegistroPro3(creditoEntradaSalida3);
                }
            break;
            case jugador:
                {
                    consultarRegistroPro4(creditoEntradaSalida4);
                }
            break;
        }
    } //FIN SWITCH
        creditoEntradaSalida.clear();

} //FIN WHILE

int opcionPro(){
    system("cls");

    cout<<"\t\t\t--------------------------------------------------"<<endl;
	cout<<"\t\t\t |   MENU INFORMES, MONICA PEREZ; 9959-21-1840  |"<<endl;
	cout<<"\t\t\t--------------------------------------------------"<<endl;

    cout<< "\n\n\t\t\t 1. Entrenador" << endl
        << "\t\t\t 2. Puesto" << endl
        << "\t\t\t 3. Equipo" << endl
        << "\t\t\t 4. Jugador" << endl
        << "\t\t\t 5. Pais" << endl
        << "\t\t\t 6. Regresar al Menu Principal" << endl
        <<"\n\t\t\t---------------------------------------------------"<<endl
        << "\n\t\t\tIngrese su opcion: ";
    int opcionMenu ;

    cin >> opcionMenu;

   return opcionMenu;
}
void consultarRegistroPro( fstream &leerDeArchivo )
{
    cout << left << setw( 10 ) << "\nCodigo" << setw( 14 ) << " Nombre" << setw( 12 ) << " 2do Nombre" << setw( 16 ) << " Apellido" << setw( 15 )
    << " 2do Apellido" << setw( 10 ) << "Fecha " << endl;
    leerDeArchivo.seekg( 0 );
    DatosEntrenador entrenador;
    leerDeArchivo.read( reinterpret_cast< char * >( &entrenador ), sizeof( DatosEntrenador ) );
    while ( !leerDeArchivo.eof() ) {
        if ( entrenador.obtenerCodigo() != 0 )
            mostrarLineaPantallaPro( entrenador );
            leerDeArchivo.read( reinterpret_cast< char * >( &entrenador ), sizeof( DatosEntrenador ) );

   } //FIN WHILE
    cout<<"\n";
    system("pause");
} //FIN CONSULTAR REGISTRO
void mostrarLineaPantallaPro( const DatosEntrenador &registro )
{
   cout << left <<" "<< setw( 10 ) << registro.obtenerCodigo()
          << setw( 14 ) << registro.obtenerNombre().data()
          << setw( 12 ) << registro.obtenerNombre2().data()
          << setw( 16 ) << registro.obtenerApellido().data()
          << setw( 15 ) << registro.obtenerApellido2().data()
          << setw( 12 ) << registro.obtenerFecha().data() << endl;
} //FIN -MOSTRARLINEAENOANTALLA-

void consultarRegistroPro2( fstream &leerDeArchivo )
{
    cout << left << setw( 10 ) << "\nCodigo" << setw( 14 ) << " Nombre" << setw( 12 ) << " Salario" << endl;
    leerDeArchivo.seekg( 0 );
    DatosPuestos puestos;
    leerDeArchivo.read( reinterpret_cast< char * >( &puestos ), sizeof( DatosPuestos ) );
    while ( !leerDeArchivo.eof() ) {
        if ( puestos.obtenerCodigo() != 0 )
            mostrarLineaPantallaPro2( puestos );
            leerDeArchivo.read( reinterpret_cast< char * >( &puestos ), sizeof( DatosPuestos ) );

   } //FIN WHILE
    cout<<"\n";
    system("pause");
} //FIN CONSULTAR REGISTRO
void mostrarLineaPantallaPro2( const DatosPuestos &registro )
{
   cout << left <<" "<< setw( 10 ) << registro.obtenerCodigo()
          << setw( 14 ) << registro.obtenerNombre().data()
          << setw( 12 ) << registro.obtenerSalario() << endl;
} //FIN -MOSTRARLINEAENOANTALLA-

void consultarRegistroPro3( fstream &leerDeArchivo )
{
    cout << left << setw( 10 ) << "\nCodigo" << setw( 14 ) << " Nombre" << endl;
    leerDeArchivo.seekg( 0 );
    DatosEquipo equipo;
    leerDeArchivo.read( reinterpret_cast< char * >( &equipo ), sizeof( DatosEquipo ) );
    while ( !leerDeArchivo.eof() ) {
        if ( equipo.obtenerCodigo() != 0 )
            mostrarLineaPantallaPro3( equipo );
            leerDeArchivo.read( reinterpret_cast< char * >( &equipo ), sizeof( DatosEquipo ) );

   } //FIN WHILE
    cout<<"\n";
    system("pause");
} //FIN CONSULTAR REGISTRO
void mostrarLineaPantallaPro3( const DatosEquipo &registro )
{
   cout << left <<" "<< setw( 10 ) << registro.obtenerCodigo()
          << setw( 14 ) << registro.obtenerNombre().data()<< endl;
} //FIN -MOSTRARLINEAENOANTALLA-

void consultarRegistroPro4( fstream &leerDeArchivo )
{
    cout << left << setw( 10 ) << "\nCodigo" << setw( 14 ) << " Nombre" << endl;
    leerDeArchivo.seekg( 0 );
    DatosJugador jugador;
    leerDeArchivo.read( reinterpret_cast< char * >( &jugador ), sizeof( DatosJugador ) );
    while ( !leerDeArchivo.eof() ) {
        if ( jugador.obtenerCodigo() != 0 )
            mostrarLineaPantallaPro4( jugador );
            leerDeArchivo.read( reinterpret_cast< char * >( &jugador ), sizeof( DatosJugador ) );

   } //FIN WHILE
    cout<<"\n";
    system("pause");
} //FIN CONSULTAR REGISTRO
void mostrarLineaPantallaPro4( const DatosJugador &registro )
{
   cout << left <<" "<< setw( 10 ) << registro.obtenerCodigo()
          << setw( 14 ) << registro.obtenerNombre().data() << endl;
}
Procesos::~Procesos()
{
    //dtor
}

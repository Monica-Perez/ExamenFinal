#include "Procesos.h"
#include "DatosEntrenador.h"
#include "DatosPuestos.h"
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

Procesos::Procesos()
{
    fstream creditoEntradaSalida( "Entrenador.dat", ios::in | ios::out | ios::binary);
    fstream creditoEntradaSalida2( "Puestos.dat", ios::in | ios::out | ios::binary);
    if ( !creditoEntradaSalida && creditoEntradaSalida2 ) {
        cerr << "No se pudo abrir el archivo." << endl;
    }
    enum Opciones { entrenador = 1, puestos, /*equipo, jugador, pais,*/ FIN };
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
            /*case equipo:
                {
                    Equipo claseequipo;
                }
            break;
            case jugador:
                {
                    Jugador clasejugador;
                }
            break;*/
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

Procesos::~Procesos()
{
    //dtor
}

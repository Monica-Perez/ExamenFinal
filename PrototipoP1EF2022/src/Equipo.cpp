#include "Equipo.h"
#include "DatosEquipo.h"
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

int opcionE();
void imprimirRegistroE( fstream& );
void crearArchivoCreditoE();
void mostrarLineaE( ostream&, const DatosEquipo & );
void nuevoRegistroE( fstream& );
int obtenernCodigoE( const char * const );
void modificarRegistroE( fstream& );
void eliminarRegistroE( fstream& );
void consultarRegistroE( fstream& );
void mostrarLineaPantallaE( const DatosEquipo &);

using namespace std;


Equipo::Equipo()
{
    fstream creditoEntradaSalida( "Equipo.dat", ios::in | ios::out | ios::binary);
    if ( !creditoEntradaSalida ) {
        cerr << "No se pudo abrir el archivo." << endl;
        crearArchivoCreditoE();
        cout <<  "Archivo creado satisfactoriamente, pruebe de nuevo\n";
        exit ( 1 );
    }

    enum Opciones { agregar = 1, nuevo, modificar, eliminar, mostrar, FIN };
    int opcion;
    while ( ( opcion = opcionE() ) != FIN ) {
        switch ( opcion ) {
            case agregar:
                imprimirRegistroE( creditoEntradaSalida );
            break;
            case nuevo:
                nuevoRegistroE( creditoEntradaSalida );
            break;
            case modificar:
                modificarRegistroE( creditoEntradaSalida );
            break;
            case eliminar:
                eliminarRegistroE( creditoEntradaSalida );
            break;
            case mostrar:
                consultarRegistroE( creditoEntradaSalida );
            break;
            default:
            cerr << "Opcion incorrecta" << endl;
            break;

      } //FIN SWITCH

       creditoEntradaSalida.clear();

   } //FIN WHILE

}
int opcionE()
{
    system("cls");

    time_t now = time(0);
    tm * time = localtime(&now);

    vector<string> dia_semana;
    dia_semana.push_back("Domingo");
    dia_semana.push_back("Lunes");
    dia_semana.push_back("Martes");
    dia_semana.push_back("Miercoles");
    dia_semana.push_back("Jueves");
    dia_semana.push_back("Viernes");
    dia_semana.push_back("Sabado");

    vector<string> mes;
    mes.push_back("Enero");
    mes.push_back("Febrero");
    mes.push_back("Marzo");
    mes.push_back("Abril");
    mes.push_back("Mayo");
    mes.push_back("Junio");
    mes.push_back("Julio");
    mes.push_back("Agosto");
    mes.push_back("Septiembre");
    mes.push_back("Octubre");
    mes.push_back("Noviembre");
    mes.push_back("Diciembre");

    int year = 1900 + time->tm_year;

    cout<< "\n";
    cout << "Hoy " << dia_semana[time->tm_wday] << ", ";
    cout << time->tm_mday << " de " << mes[time->tm_mon] << " del " << year << endl;
    cout << time->tm_hour << ":" << time->tm_min << ":" << time->tm_sec << endl;


    cout<<"\t\t\t-------------------------------------------"<<endl;
	cout<<"\t\t\t |   EQUIPO, MONICA PEREZ; 9959-21-1840  |"<<endl;
	cout<<"\t\t\t-------------------------------------------"<<endl;

    cout<< "\n\n\t\t\t 1. Guardar archivo de texto para Imprimirlo" << endl
        << "\t\t\t 2. Agregar Equipo" << endl
        << "\t\t\t 3. Modificar Equipo" << endl
        << "\t\t\t 4. Eliminar Equipo" << endl
        << "\t\t\t 5. Mostrar Lista de Equipos" << endl
        << "\t\t\t 6. Regresar al Menu Principal" << endl
        <<"\n\t\t\t-----------------------------------------------"<<endl
        << "\n\t\t\tIngrese su opcion: ";
    int opcionMenu ;

    cin >> opcionMenu;

   return opcionMenu;
}
void imprimirRegistroE( fstream &leerDeArchivo )
{
    ofstream archivoImprimirSalida( "ImprimirEquipo.txt", ios::out );
    if ( !archivoImprimirSalida ) {
        cerr << "No se pudo crear el archivo." << endl;
        exit( 1 );

    } //FIN DE INSTRUCCION if

    archivoImprimirSalida << left << setw( 14 ) << "Codigo" << setw( 16 )<< "Nombre" << endl;
    leerDeArchivo.seekg( 0 );

    DatosEquipo equipo;
    leerDeArchivo.read( reinterpret_cast< char * >( &equipo ), sizeof( DatosEquipo ) );

    while ( !leerDeArchivo.eof() ) {
        if ( equipo.obtenerCodigo() != 0 )
        mostrarLineaE( archivoImprimirSalida, equipo );
        leerDeArchivo.read( reinterpret_cast< char * >( &equipo ), sizeof( DatosEquipo ) );
    } //FIN DE WHILE
    cout<<"\n";
    system("pause");
} //FIN DE LA FUNCION -IMPRIMIR REGISTRO-
void mostrarLineaE( ostream &salida, const DatosEquipo &registro )
{
   salida << left << setw( 18 ) << registro.obtenerCodigo()
          << setw( 16 ) << registro.obtenerNombre().data()<< endl;

}//FIN -MOSTRARLINEA-
void crearArchivoCreditoE()
{
    ofstream creditoSalida( "Equipo.dat", ios::out | ios::binary );
    if ( !creditoSalida ) {
      cerr << "No se pudo abrir el archivo." << endl;
      exit( 1 );
    }
    DatosEquipo equipoEnBlanco;
    for ( int i = 0; i < 100; i++ )
        creditoSalida.write(reinterpret_cast< const char * >( &equipoEnBlanco ), sizeof( DatosEquipo ) );
    cout<<"\n";
    system("pause");
}
void nuevoRegistroE( fstream &insertarEnArchivo )
{
    int codigo = obtenernCodigoE( "\nEscriba el Codigo del Equipo " );
    insertarEnArchivo.seekg( ( codigo - 1 ) * sizeof( DatosEquipo ) );
    DatosEquipo equipo;
    insertarEnArchivo.read( reinterpret_cast< char * >( &equipo ), sizeof( equipo ) );

    if ( equipo.obtenerCodigo() == 0 ) {
        char nombre[ 15 ];

        cout<<"Escriba el Nombre del Equipo: ";
        cin>> setw( 15 ) >> nombre;
        equipo.establecerNombre( nombre );
        equipo.establecerCodigo( codigo );

        insertarEnArchivo.seekp( ( codigo - 1 ) * sizeof( equipo ) );
        insertarEnArchivo.write( reinterpret_cast< const char * >( &equipo ), sizeof( equipo ) );
        cout<<"\n Equipo agregado Exitosamente..."<<endl;

    } //FIN IF
    else
        cerr << "El Equipo con codigo #" << codigo << " ya contiene informacion.\n" << endl;
    cout<<"\n";
    system("pause");
}
int obtenernCodigoE( const char * const indicador )
{
   int codigo;
    do {
      cout << indicador << "(1 - 100): ";
      cin >> codigo;

    } while ( codigo < 1 || codigo > 100 );

   return codigo;

} //FIN -OBTENERCODIGO-
void modificarRegistroE( fstream &actualizarArchivo )
{
    int opcionAc=0;
    cout<<"\nEscoja opcion a Actualizar: \n 1. Nombre\n  R - ";
    cin>>opcionAc;

    if (opcionAc == 1){
        int codigo = obtenernCodigoE( "\nEscriba el codigo del Equipo que desea Modifcar" );

        actualizarArchivo.seekg(( codigo - 1 ) * sizeof( DatosEquipo ));

        DatosEquipo equipo;
        actualizarArchivo.read( reinterpret_cast< char * >( &equipo ), sizeof( DatosEquipo ) );

        if (equipo.obtenerCodigo() != 0 ) {
            mostrarLineaE( cout, equipo );
            cout << "\nEscriba el nuevo Nombre: ";
            string nombre;
            cin >> nombre;

            string nombreAnterior = equipo.obtenerNombre();
            equipo.establecerNombre( nombre );
            mostrarLineaE( cout, equipo );

            actualizarArchivo.seekp(( codigo - 1 ) * sizeof( DatosEquipo ));

            actualizarArchivo.write(reinterpret_cast< const char * >( &equipo ), sizeof( DatosEquipo ) );
        }

    }
    cout<<"\n";
    system("pause");

} //FIN DE -ACTUALIZAR REGISTRO-
void eliminarRegistroE( fstream &eliminarDeArchivo )
{
    int codigo = obtenernCodigoE( "\nEscriba el codigo del Equipo a Eliminar" );
    eliminarDeArchivo.seekg( ( codigo - 1 ) * sizeof( DatosEquipo ) );
    DatosEquipo equipo;
    eliminarDeArchivo.read( reinterpret_cast< char * >( &equipo ), sizeof( DatosEquipo ) );

    if ( equipo.obtenerCodigo() != 0 ) {
        DatosEquipo equipoEnBlanco;
        eliminarDeArchivo.seekp( ( codigo - 1 ) * sizeof( DatosEquipo ) );
        eliminarDeArchivo.write( reinterpret_cast< const char * >( &equipoEnBlanco ), sizeof( DatosEquipo ) );

      cout << " Cuenta #" << codigo << " eliminada Exitosamente.\n";

   } //FIN IF

   //ERROR SI NO EXISTE
   else
      cerr << "La cuenta #" << codigo << " esta vacia.\n";
    cout<<"\n";
    system("pause");
} //FIN -ELIMINARREGISTRO-
void consultarRegistroE( fstream &leerDeArchivo )
{
    cout << left << setw( 10 ) << "\nCodigo" << setw( 14 ) << " Nombre" << endl;
    leerDeArchivo.seekg( 0 );
    DatosEquipo equipo;
    leerDeArchivo.read( reinterpret_cast< char * >( &equipo ), sizeof( DatosEquipo ) );
    while ( !leerDeArchivo.eof() ) {
        if ( equipo.obtenerCodigo() != 0 )
            mostrarLineaPantallaE( equipo );
            leerDeArchivo.read( reinterpret_cast< char * >( &equipo ), sizeof( DatosEquipo ) );

   } //FIN WHILE
    cout<<"\n";
    system("pause");
} //FIN CONSULTAR REGISTRO
void mostrarLineaPantallaE( const DatosEquipo &registro )
{
   cout << left <<" "<< setw( 10 ) << registro.obtenerCodigo()
          << setw( 14 ) << registro.obtenerNombre().data()<< endl;
} //FIN -MOSTRARLINEAENOANTALLA-

Equipo::~Equipo()
{
    //dtor
}

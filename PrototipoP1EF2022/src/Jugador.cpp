#include "Jugador.h"
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

int opcionJ();
void imprimirRegistroJ( fstream& );
void crearArchivoCreditoJ();
void mostrarLineaJ( ostream&, const DatosJugador & );
void nuevoRegistroJ( fstream& );
int obtenernCodigoJ( const char * const );
void modificarRegistroJ( fstream& );
void eliminarRegistroJ( fstream& );
void consultarRegistroJ( fstream& );
void mostrarLineaPantallaJ( const DatosJugador &);

using namespace std;

Jugador::Jugador()
{
    fstream creditoEntradaSalida( "Jugador.dat", ios::in | ios::out | ios::binary);
    if ( !creditoEntradaSalida ) {
        cerr << "No se pudo abrir el archivo." << endl;
        crearArchivoCreditoJ();
        cout <<  "Archivo creado satisfactoriamente, pruebe de nuevo\n";
        exit ( 1 );
    }

    enum Opciones { agregar = 1, nuevo, modificar, eliminar, mostrar, FIN };
    int opcion;
    while ( ( opcion = opcionJ() ) != FIN ) {
        switch ( opcion ) {
            case agregar:
                imprimirRegistroJ( creditoEntradaSalida );
            break;
            case nuevo:
                nuevoRegistroJ( creditoEntradaSalida );
            break;
            case modificar:
                modificarRegistroJ( creditoEntradaSalida );
            break;
            case eliminar:
                eliminarRegistroJ( creditoEntradaSalida );
            break;
            case mostrar:
                consultarRegistroJ( creditoEntradaSalida );
            break;
            default:
            cerr << "Opcion incorrecta" << endl;
            break;

      } //FIN SWITCH

       creditoEntradaSalida.clear();

   } //FIN WHILE
}
int opcionJ()
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


    cout<<"\t\t\t--------------------------------------------"<<endl;
	cout<<"\t\t\t |   JUGADOR, MONICA PEREZ; 9959-21-1840  |"<<endl;
	cout<<"\t\t\t--------------------------------------------"<<endl;

    cout<< "\n\n\t\t\t 1. Guardar archivo de texto para Imprimirlo" << endl
        << "\t\t\t 2. Agregar Jugador" << endl
        << "\t\t\t 3. Modificar Jugador" << endl
        << "\t\t\t 4. Eliminar Jugador" << endl
        << "\t\t\t 5. Mostrar Lista de Jugadores" << endl
        << "\t\t\t 6. Regresar al Menu Principal" << endl
        <<"\n\t\t\t-----------------------------------------------"<<endl
        << "\n\t\t\tIngrese su opcion: ";
    int opcionMenu ;

    cin >> opcionMenu;

   return opcionMenu;
}
void imprimirRegistroJ( fstream &leerDeArchivo )
{
    ofstream archivoImprimirSalida( "ImprimirJugador.txt", ios::out );
    if ( !archivoImprimirSalida ) {
        cerr << "No se pudo crear el archivo." << endl;
        exit( 1 );

    } //FIN DE INSTRUCCION if

    archivoImprimirSalida << left << setw( 14 ) << "Codigo" << setw( 16 )<< "Nombre"  << endl;
    leerDeArchivo.seekg( 0 );

    DatosJugador jugador;
    leerDeArchivo.read( reinterpret_cast< char * >( &jugador ), sizeof( DatosJugador ) );

    while ( !leerDeArchivo.eof() ) {
        if ( jugador.obtenerCodigo() != 0 )
        mostrarLineaJ( archivoImprimirSalida, jugador );
        leerDeArchivo.read( reinterpret_cast< char * >( &jugador ), sizeof( DatosJugador ) );
    } //FIN DE WHILE
    cout<<"\n";
    system("pause");
} //FIN DE LA FUNCION -IMPRIMIR REGISTRO-
void mostrarLineaJ( ostream &salida, const DatosJugador &registro )
{
   salida << left << setw( 18 ) << registro.obtenerCodigo()
          << setw( 16 ) << registro.obtenerNombre().data()<< endl;

}//FIN -MOSTRARLINEA-
void crearArchivoCreditoJ()
{
    ofstream creditoSalida( "Jugador.dat", ios::out | ios::binary );
    if ( !creditoSalida ) {
      cerr << "No se pudo abrir el archivo." << endl;
      exit( 1 );
    }
    DatosJugador jugadorEnBlanco;
    for ( int i = 0; i < 100; i++ )
        creditoSalida.write(reinterpret_cast< const char * >( &jugadorEnBlanco ), sizeof( DatosJugador ) );
    cout<<"\n";
    system("pause");
}
void nuevoRegistroJ( fstream &insertarEnArchivo )
{
    int codigo = obtenernCodigoJ( "\nEscriba el Codigo del Jugador " );
    insertarEnArchivo.seekg( ( codigo - 1 ) * sizeof( DatosJugador ) );
    DatosJugador jugador;
    insertarEnArchivo.read( reinterpret_cast< char * >( &jugador ), sizeof( jugador ) );

    if ( jugador.obtenerCodigo() == 0 ) {
        char nombre[ 15 ];

        cout<<"Escriba el Nombre del Jugador: ";
        cin>> setw( 15 ) >> nombre;

        jugador.establecerNombre( nombre );
        jugador.establecerCodigo( codigo );

        insertarEnArchivo.seekp( ( codigo - 1 ) * sizeof( jugador ) );
        insertarEnArchivo.write( reinterpret_cast< const char * >( &jugador ), sizeof( jugador ) );
        cout<<"\n Jugador agregado Exitosamente..."<<endl;

    } //FIN IF
    else
        cerr << "El Jugador con codigo #" << codigo << " ya contiene informacion.\n" << endl;
    cout<<"\n";
    system("pause");
}
int obtenernCodigoJ( const char * const indicador )
{
   int codigo;
    do {
      cout << indicador << "(1 - 100): ";
      cin >> codigo;

    } while ( codigo < 1 || codigo > 100 );

   return codigo;

} //FIN -OBTENERCODIGO-
void modificarRegistroJ( fstream &actualizarArchivo )
{
    int opcionAc=0;
    cout<<"\nEscoja opcion a Actualizar: \n 1. Nombre\n  R - ";
    cin>>opcionAc;

    if (opcionAc == 1){
        int codigo = obtenernCodigoJ( "\nEscriba el codigo del Jugador que desea Modifcar" );

        actualizarArchivo.seekg(( codigo - 1 ) * sizeof( DatosJugador ));

        DatosJugador jugador;
        actualizarArchivo.read( reinterpret_cast< char * >( &jugador ), sizeof( DatosJugador ) );

        if (jugador.obtenerCodigo() != 0 ) {
            mostrarLineaJ( cout, jugador );
            cout << "\nEscriba el nuevo Nombre: ";
            string nombre;
            cin >> nombre;

            string nombreAnterior = jugador.obtenerNombre();
            jugador.establecerNombre( nombre );
            mostrarLineaJ( cout, jugador );

            actualizarArchivo.seekp(( codigo - 1 ) * sizeof( DatosJugador ));

            actualizarArchivo.write(reinterpret_cast< const char * >( &jugador ), sizeof( DatosJugador ) );
        }
    }
    cout<<"\n";
    system("pause");

} //FIN DE -ACTUALIZAR REGISTRO-
void eliminarRegistroJ( fstream &eliminarDeArchivo )
{
    int codigo = obtenernCodigoJ( "\nEscriba el codigo del Jugador a Eliminar" );
    eliminarDeArchivo.seekg( ( codigo - 1 ) * sizeof( DatosJugador ) );
    DatosJugador jugador;
    eliminarDeArchivo.read( reinterpret_cast< char * >( &jugador ), sizeof( DatosJugador ) );

    if ( jugador.obtenerCodigo() != 0 ) {
        DatosJugador jugadorEnBlanco;
        eliminarDeArchivo.seekp( ( codigo - 1 ) * sizeof( DatosJugador ) );
        eliminarDeArchivo.write( reinterpret_cast< const char * >( &jugadorEnBlanco ), sizeof( DatosJugador ) );

      cout << " Cuenta #" << codigo << " eliminada Exitosamente.\n";

   } //FIN IF

   //ERROR SI NO EXISTE
   else
      cerr << "La cuenta #" << codigo << " esta vacia.\n";
    cout<<"\n";
    system("pause");
} //FIN -ELIMINARREGISTRO-
void consultarRegistroJ( fstream &leerDeArchivo )
{
    cout << left << setw( 10 ) << "\nCodigo" << setw( 14 ) << " Nombre" << endl;
    leerDeArchivo.seekg( 0 );
    DatosJugador jugador;
    leerDeArchivo.read( reinterpret_cast< char * >( &jugador ), sizeof( DatosJugador ) );
    while ( !leerDeArchivo.eof() ) {
        if ( jugador.obtenerCodigo() != 0 )
            mostrarLineaPantallaJ( jugador );
            leerDeArchivo.read( reinterpret_cast< char * >( &jugador ), sizeof( DatosJugador ) );

   } //FIN WHILE
    cout<<"\n";
    system("pause");
} //FIN CONSULTAR REGISTRO
void mostrarLineaPantallaJ( const DatosJugador &registro )
{
   cout << left <<" "<< setw( 10 ) << registro.obtenerCodigo()
          << setw( 14 ) << registro.obtenerNombre().data() << endl;
}

Jugador::~Jugador()
{
    //dtor
}

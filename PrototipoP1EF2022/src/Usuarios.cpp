#include "Usuarios.h"
#include "DatosUsuarios.h"
#include <iostream>
#include<cstdlib>
#include<conio.h>
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

int opcionUs();
void imprimirRegistroUs( fstream& );
void crearArchivoCreditoUs();
void mostrarLineaUs( ostream&, const DatosUsuarios & );
void nuevoRegistroUs( fstream& );
int obtenernUsuario( const char * const );
void modificarRegistroUs( fstream& );
int obtenerncontra( const char * const );

using namespace std;

Usuarios::Usuarios()
{
    fstream creditoEntradaSalida( "usuario.dat", ios::in | ios::out | ios::binary);
    if ( !creditoEntradaSalida ) {
        cerr << "No se pudo abrir el archivo." << endl;
        crearArchivoCreditoUs();
        cout <<  "Archivo creado satisfactoriamente, pruebe de nuevo\n";
        exit ( 1 );
    }
    modificarRegistroUs(creditoEntradaSalida);

    /*enum Opciones { agregar = 1, nuevo, FIN };
    int opcion;
    while ( ( opcion = opcionUs() ) != FIN ) {
        switch ( opcion ) {
            case agregar:
                imprimirRegistroUs( creditoEntradaSalida );
            break;
            case nuevo:
                nuevoRegistroUs( creditoEntradaSalida );
            break;
        }
    }*/

}
/*int opcionUs(){
    //system("cls");
    cout<<"\n\t\t\t\t------------------"<<endl;
	cout<<"\t\t\t\t |   Registrar  |"<<endl;
	cout<<"\t\t\t\t------------------"<<endl;

    cout<< "\nEscriba su opcion" << endl
        << " 1. Guardar archivo de texto para Imprimirlo" << endl
        << " 2. Agregar" << endl
        << " 3. Salir \nR- ";

   int opcionMenu;
   cin >> opcionMenu;

   return opcionMenu;
}
void imprimirRegistroUs( fstream &leerDeArchivo )
{
    ofstream archivoImprimirSalida( "ImprimirUsuarios.txt", ios::out );
    if ( !archivoImprimirSalida ) {
        cerr << "No se pudo crear el archivo." << endl;
        exit( 1 );

    } //FIN DE INSTRUCCION if

    archivoImprimirSalida << left << setw( 10 ) << "Usuario" << right << setw( 10 ) << "Contra" << endl;
    leerDeArchivo.seekg( 0 );

    DatosUsuarios usuario;
    leerDeArchivo.read( reinterpret_cast< char * >( &usuario ), sizeof( DatosUsuarios ) );

    while ( !leerDeArchivo.eof() ) {
        if ( usuario.obtenerUsuario() != 0 )
        mostrarLineaUs( archivoImprimirSalida, usuario );
        leerDeArchivo.read( reinterpret_cast< char * >( &usuario ), sizeof( DatosUsuarios ) );
    } //FIN DE WHILE

} //FIN DE LA FUNCION -IMPRIMIR REGISTRO-*/
void mostrarLineaUs( ostream &salida, const DatosUsuarios &registro )
{
   salida << left << setw( 10 ) << registro.obtenerUsuario()
          << setw( 16 ) << setprecision( 2 ) << right << fixed<< showpoint << registro.obtenerContra() << endl;

}//FIN -MOSTRARLINEA-
void crearArchivoCreditoUs()
{
    ofstream creditoSalida( "usuario.dat", ios::out | ios::binary );
    if ( !creditoSalida ) {
      cerr << "No se pudo abrir el archivo." << endl;
      exit( 1 );
    }
    DatosUsuarios usuarioEnBlanco;
    for ( int i = 0; i < 100; i++ )
        creditoSalida.write(reinterpret_cast< const char * >( &usuarioEnBlanco ), sizeof( DatosUsuarios ) );
}
void nuevoRegistroUs( fstream &insertarEnArchivo )
{
    int usuario = obtenernUsuario( "\nEscriba el Usuario " );
    insertarEnArchivo.seekg( ( usuario - 1 ) * sizeof( DatosUsuarios ) );
    DatosUsuarios usuarioos;
    insertarEnArchivo.read( reinterpret_cast< char * >( &usuarioos ), sizeof( DatosUsuarios ) );

    if ( usuarioos.obtenerUsuario() == 0 ) {
        int contra;
        cout<<"Escriba la Contra: ";
        cin>> setw( 15 ) >> contra;
        usuarioos.establecerContra( contra );
        usuarioos.establecerUsuario( usuario );

        insertarEnArchivo.seekp( ( usuario - 1 ) * sizeof( DatosUsuarios ) );
        insertarEnArchivo.write( reinterpret_cast< const char * >( &usuarioos ), sizeof( DatosUsuarios ) );
        cout<<"\n Empleado agregado Exitosamente..."<<endl;

    } //FIN IF
    else
        cerr << "El Usuario #" << usuario << " ya contiene informacion.\n" << endl;

}
int obtenernUsuario( const char * const indicador )
{
   int usuario;
    do {
      cout << indicador << ": ";
      cin >> usuario;

    } while ( usuario < 1 || usuario > 100 );

   return usuario;

} //FIN -OBTENERCODIGO-
int obtenerncontra( const char * const indicador )
{
   int contra;
    do {
      cout << indicador << ": ";
      cin >> contra;

    } while ( contra < 1 || contra > 100000 );

   return contra;
}
void modificarRegistroUs( fstream &verificarArchivoUsuario )
{
    int contador=0;
    bool ingresa = false;
    do{
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

        cout << "Hoy " << dia_semana[time->tm_wday] << ", ";
        cout << time->tm_mday << " de " << mes[time->tm_mon] << " del " << year << endl;
        cout << time->tm_hour << ":" << time->tm_min << ":" << time->tm_sec << endl;

        cout<<"\t\t\t------------------------------------------------------"<<endl;
        cout<<"\t\t\t |   INICIO DE SESION - MONICA PEREZ; 9959-21-1840  |"<<endl;
        cout<<"\t\t\t------------------------------------------------------"<<endl;

        DatosUsuarios usuarioos;
        int usuario = obtenernUsuario( "\n\t\t\tIngrese Usuario" );
        int contra = obtenerncontra("\n\t\t\tIngrese Contrasena");

        verificarArchivoUsuario.seekg(( usuario - 1 ) * sizeof( DatosUsuarios ));
        verificarArchivoUsuario.read( reinterpret_cast< char * >( &usuarioos ), sizeof( DatosUsuarios ) );

        if(usuario==usuarioos.obtenerUsuario() && contra==usuarioos.obtenerContra())
        {
            ingresa = true;
        }
        else{
            cout<<"\n\t\t\tUsuario o Contrasena Incorrectos\n\n";
            contador ++;
        }
    }while( ingresa == false && contador < 3);

    if( ingresa == false){
        cout<<"\t\t\tIntentos Agotados...\n"<<endl;
        exit(1);
    }else{
        system("color a");
        cout<<"\n\t\t\tBienvenido al Sistema, Inicio de sesion Exitoso...";
        getch();
    }

}

Usuarios::~Usuarios()
{
    //dtor
}

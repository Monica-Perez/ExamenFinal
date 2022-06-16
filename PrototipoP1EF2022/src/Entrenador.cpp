#include "Entrenador.h"
#include "DatosEntrenador.h"
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

int opcionEnt();
void imprimirRegistroEnt( fstream& );
void crearArchivoCreditoEnt();
void mostrarLineaEnt( ostream&, const DatosEntrenador & );
void nuevoRegistroEnt( fstream& );
int obtenernCodigoEnt( const char * const );
void modificarRegistroEnt( fstream& );
void eliminarRegistroEnt( fstream& );
void consultarRegistroEnt( fstream& );
void mostrarLineaPantallaEnt( const DatosEntrenador &);

using namespace std;

Entrenador::Entrenador()
{
    fstream creditoEntradaSalida( "Entrenador.dat", ios::in | ios::out | ios::binary);
    if ( !creditoEntradaSalida ) {
        cerr << "No se pudo abrir el archivo." << endl;
        crearArchivoCreditoEnt();
        cout <<  "Archivo creado satisfactoriamente, pruebe de nuevo\n";
        exit ( 1 );
    }

    enum Opciones { agregar = 1, nuevo, modificar, eliminar, mostrar, FIN };
    int opcion;
    while ( ( opcion = opcionEnt() ) != FIN ) {
        switch ( opcion ) {
            case agregar:
                imprimirRegistroEnt( creditoEntradaSalida );
            break;
            case nuevo:
                nuevoRegistroEnt( creditoEntradaSalida );
            break;
            case modificar:
                modificarRegistroEnt( creditoEntradaSalida );
            break;
            case eliminar:
                eliminarRegistroEnt( creditoEntradaSalida );
            break;
            case mostrar:
                consultarRegistroEnt( creditoEntradaSalida );
            break;
            default:
            cerr << "Opcion incorrecta" << endl;
            break;

      } //FIN SWITCH

       creditoEntradaSalida.clear();

   } //FIN WHILE
}
int opcionEnt()
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


    cout<<"\t\t\t-----------------------------------------------"<<endl;
	cout<<"\t\t\t |   ENTRENADOR, MONICA PEREZ; 9959-21-1840  |"<<endl;
	cout<<"\t\t\t-----------------------------------------------"<<endl;

    cout<< "\n\n\t\t\t 1. Guardar archivo de texto para Imprimirlo" << endl
        << "\t\t\t 2. Agregar Entrenador" << endl
        << "\t\t\t 3. Modificar Entrenador" << endl
        << "\t\t\t 4. Eliminar Entrenador" << endl
        << "\t\t\t 5. Mostrar Lista de Entrenadores" << endl
        << "\t\t\t 6. Regresar al Menu Principal" << endl
        <<"\n\t\t\t-----------------------------------------------"<<endl
        << "\n\t\t\tIngrese su opcion: ";
    int opcionMenu ;

    cin >> opcionMenu;

   return opcionMenu;
}
void imprimirRegistroEnt( fstream &leerDeArchivo )
{
    ofstream archivoImprimirSalida( "ImprimirEntrenador.txt", ios::out );
    if ( !archivoImprimirSalida ) {
        cerr << "No se pudo crear el archivo." << endl;
        exit( 1 );

    } //FIN DE INSTRUCCION if

    archivoImprimirSalida << left << setw( 14 ) << "Codigo" << setw( 16 )<< "Nombre" << setw( 14 ) << "2doNombre" << setw( 20 ) << "Apellido"
       << setw( 16 ) << "2doApellido" << right << setw( 12 ) << "Nacimiento" << endl;
    leerDeArchivo.seekg( 0 );

    DatosEntrenador entrenador;
    leerDeArchivo.read( reinterpret_cast< char * >( &entrenador ), sizeof( DatosEntrenador ) );

    while ( !leerDeArchivo.eof() ) {
        if ( entrenador.obtenerCodigo() != 0 )
        mostrarLineaEnt( archivoImprimirSalida, entrenador );
        leerDeArchivo.read( reinterpret_cast< char * >( &entrenador ), sizeof( DatosEntrenador ) );
    } //FIN DE WHILE
    cout<<"\n";
    system("pause");
} //FIN DE LA FUNCION -IMPRIMIR REGISTRO-
void mostrarLineaEnt( ostream &salida, const DatosEntrenador &registro )
{
   salida << left << setw( 18 ) << registro.obtenerCodigo()
          << setw( 16 ) << registro.obtenerNombre().data()
          << setw( 16 ) << registro.obtenerNombre2().data()
          << setw( 15 ) << registro.obtenerApellido().data()
          << setw( 15 ) << registro.obtenerApellido2().data()
          << setw( 10 ) << registro.obtenerFecha().data()<< endl;

}//FIN -MOSTRARLINEA-
void crearArchivoCreditoEnt()
{
    ofstream creditoSalida( "Entrenador.dat", ios::out | ios::binary );
    if ( !creditoSalida ) {
      cerr << "No se pudo abrir el archivo." << endl;
      exit( 1 );
    }
    DatosEntrenador entrenadorEnBlanco;
    for ( int i = 0; i < 100; i++ )
        creditoSalida.write(reinterpret_cast< const char * >( &entrenadorEnBlanco ), sizeof( DatosEntrenador ) );
    cout<<"\n";
    system("pause");
}
void nuevoRegistroEnt( fstream &insertarEnArchivo )
{
    int codigo = obtenernCodigoEnt( "\nEscriba el Codigo del Entrenador " );
    insertarEnArchivo.seekg( ( codigo - 1 ) * sizeof( DatosEntrenador ) );
    DatosEntrenador entrenador;
    insertarEnArchivo.read( reinterpret_cast< char * >( &entrenador ), sizeof( entrenador ) );

    if ( entrenador.obtenerCodigo() == 0 ) {
        char nombre[ 15 ];
        char nombre2[ 15 ];
        char apellido[ 15 ];
        char apellido2[ 15 ];
        char fecha[ 15 ];

        cout<<"Escriba el Nombre del Entrenador: ";
        cin>> setw( 15 ) >> nombre;
        cout<<"Escriba el 2do Nombre del Entrenador: ";
        cin>> setw( 15 ) >> nombre2;
        cout<<"Escriba el Apellido del Entrenador: ";
        cin>> setw( 15 ) >> apellido;
        cout<<"Escriba el 2do Apellido del Entrenador: ";
        cin>> setw( 15 ) >> apellido2;
        cout<<"Escriba el Fecha de Nacimiento del Entrenador: ";
        cin>> setw( 15 ) >> fecha;
        entrenador.establecerNombre( nombre );
        entrenador.establecerNombre2( nombre2 );
        entrenador.establecerApellido( apellido );
        entrenador.establecerApellido2( apellido2 );
        entrenador.establecerFecha( fecha );
        entrenador.establecerCodigo( codigo );

        insertarEnArchivo.seekp( ( codigo - 1 ) * sizeof( entrenador ) );
        insertarEnArchivo.write( reinterpret_cast< const char * >( &entrenador ), sizeof( entrenador ) );
        cout<<"\n Entrenador agregado Exitosamente..."<<endl;

    } //FIN IF
    else
        cerr << "El Entrenador con codigo #" << codigo << " ya contiene informacion.\n" << endl;
    cout<<"\n";
    system("pause");
}
int obtenernCodigoEnt( const char * const indicador )
{
   int codigo;
    do {
      cout << indicador << "(1 - 100): ";
      cin >> codigo;

    } while ( codigo < 1 || codigo > 100 );

   return codigo;

} //FIN -OBTENERCODIGO-
void modificarRegistroEnt( fstream &actualizarArchivo )
{
    int opcionAc=0;
    cout<<"\nEscoja opcion a Actualizar: \n 1. Nombre\n 2. 2do Nombre\n 3. Apellido \n 4. 2do Apellido\n  R - ";
    cin>>opcionAc;

    if (opcionAc == 1){
        int codigo = obtenernCodigoEnt( "\nEscriba el codigo del Entrenador que desea Modifcar" );

        actualizarArchivo.seekg(( codigo - 1 ) * sizeof( DatosEntrenador ));

        DatosEntrenador entrenador;
        actualizarArchivo.read( reinterpret_cast< char * >( &entrenador ), sizeof( DatosEntrenador ) );

        if (entrenador.obtenerCodigo() != 0 ) {
            mostrarLineaEnt( cout, entrenador );
            cout << "\nEscriba el nuevo Nombre: ";
            string nombre;
            cin >> nombre;

            string nombreAnterior = entrenador.obtenerNombre();
            entrenador.establecerNombre( nombre );
            mostrarLineaEnt( cout, entrenador );

            actualizarArchivo.seekp(( codigo - 1 ) * sizeof( DatosEntrenador ));

            actualizarArchivo.write(reinterpret_cast< const char * >( &entrenador ), sizeof( DatosEntrenador ) );
        }

    }else if (opcionAc== 2){
        int codigo = obtenernCodigoEnt( "\nEscriba el codigo del Entrenador que desea Modifcar" );

        actualizarArchivo.seekg(( codigo - 1 ) * sizeof( DatosEntrenador ));

        DatosEntrenador entrenador;
        actualizarArchivo.read( reinterpret_cast< char * >( &entrenador ), sizeof( DatosEntrenador ) );

        if (entrenador.obtenerCodigo() != 0 ) {
            mostrarLineaEnt( cout, entrenador );
            cout << "\nEscriba el nuevo Nombre: ";
            string nombre2;
            cin >> nombre2;

            string nombreAnterior = entrenador.obtenerNombre2();
            entrenador.establecerNombre2( nombre2 );
            mostrarLineaEnt( cout, entrenador );

            actualizarArchivo.seekp(( codigo - 1 ) * sizeof( DatosEntrenador ));
            actualizarArchivo.write(reinterpret_cast< const char * >( &entrenador ), sizeof( DatosEntrenador ) );
        }
    }else if(opcionAc == 3){
        int codigo = obtenernCodigoEnt( "\nEscriba el codigo del Entrenador que desea Modifcar" );

        actualizarArchivo.seekg(( codigo - 1 ) * sizeof( DatosEntrenador ));

        DatosEntrenador entrenador;
        actualizarArchivo.read( reinterpret_cast< char * >( &entrenador ), sizeof( DatosEntrenador ) );

        if (entrenador.obtenerCodigo() != 0 ) {
                mostrarLineaEnt( cout, entrenador );
                cout << "\nEscriba el nuevo Apellido: ";
                string apellido;
                cin >> apellido;

                string apellidoAnterior = entrenador.obtenerApellido();
                entrenador.establecerApellido( apellido );
                mostrarLineaEnt( cout, entrenador );

                actualizarArchivo.seekp(( codigo - 1 ) * sizeof( DatosEntrenador ));

                actualizarArchivo.write(reinterpret_cast< const char * >( &entrenador ), sizeof( DatosEntrenador ) );
        }
    }else if(opcionAc == 4){
        int codigo = obtenernCodigoEnt( "\nEscriba el codigo del Entrenador que desea Modifcar" );

        actualizarArchivo.seekg(( codigo - 1 ) * sizeof( DatosEntrenador ));

        DatosEntrenador entrenador;
        actualizarArchivo.read( reinterpret_cast< char * >( &entrenador ), sizeof( DatosEntrenador ) );

        if (entrenador.obtenerCodigo() != 0 ) {
                mostrarLineaEnt( cout, entrenador );
                cout << "\nEscriba el nuevo Apellido: ";
                string apellido2;
                cin >> apellido2;

                string apellidoAnterior = entrenador.obtenerApellido2();
                entrenador.establecerApellido2( apellido2 );
                mostrarLineaEnt( cout, entrenador );

                actualizarArchivo.seekp(( codigo - 1 ) * sizeof( DatosEntrenador ));

                actualizarArchivo.write(reinterpret_cast< const char * >( &entrenador ), sizeof( DatosEntrenador ) );
        }
    }
    cout<<"\n";
    system("pause");

} //FIN DE -ACTUALIZAR REGISTRO-
void eliminarRegistroEnt( fstream &eliminarDeArchivo )
{
    int codigo = obtenernCodigoEnt( "\nEscriba el codigo del Entrenador a Eliminar" );
    eliminarDeArchivo.seekg( ( codigo - 1 ) * sizeof( DatosEntrenador ) );
    DatosEntrenador entrenador;
    eliminarDeArchivo.read( reinterpret_cast< char * >( &entrenador ), sizeof( DatosEntrenador ) );

    if ( entrenador.obtenerCodigo() != 0 ) {
        DatosEntrenador entrenadorEnBlanco;
        eliminarDeArchivo.seekp( ( codigo - 1 ) * sizeof( DatosEntrenador ) );
        eliminarDeArchivo.write( reinterpret_cast< const char * >( &entrenadorEnBlanco ), sizeof( DatosEntrenador ) );

      cout << " Cuenta #" << codigo << " eliminada Exitosamente.\n";

   } //FIN IF

   //ERROR SI NO EXISTE
   else
      cerr << "La cuenta #" << codigo << " esta vacia.\n";
    cout<<"\n";
    system("pause");
} //FIN -ELIMINARREGISTRO-
void consultarRegistroEnt( fstream &leerDeArchivo )
{
    cout << left << setw( 10 ) << "\nCodigo" << setw( 14 ) << " Nombre" << setw( 12 ) << " 2do Nombre" << setw( 16 ) << " Apellido" << setw( 15 )
    << " 2do Apellido" << setw( 10 ) << "Fecha " << endl;
    leerDeArchivo.seekg( 0 );
    DatosEntrenador entrenador;
    leerDeArchivo.read( reinterpret_cast< char * >( &entrenador ), sizeof( DatosEntrenador ) );
    while ( !leerDeArchivo.eof() ) {
        if ( entrenador.obtenerCodigo() != 0 )
            mostrarLineaPantallaEnt( entrenador );
            leerDeArchivo.read( reinterpret_cast< char * >( &entrenador ), sizeof( DatosEntrenador ) );

   } //FIN WHILE
    cout<<"\n";
    system("pause");
} //FIN CONSULTAR REGISTRO
void mostrarLineaPantallaEnt( const DatosEntrenador &registro )
{
   cout << left <<" "<< setw( 10 ) << registro.obtenerCodigo()
          << setw( 14 ) << registro.obtenerNombre().data()
          << setw( 12 ) << registro.obtenerNombre2().data()
          << setw( 16 ) << registro.obtenerApellido().data()
          << setw( 15 ) << registro.obtenerApellido2().data()
          << setw( 12 ) << registro.obtenerFecha().data() << endl;
} //FIN -MOSTRARLINEAENOANTALLA-

Entrenador::~Entrenador()
{
    //dtor
}

#include "Puestos.h"
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

int opcionP();
void imprimirRegistroP( fstream& );
void crearArchivoCreditoP();
void mostrarLineaP( ostream&, const DatosPuestos & );
void nuevoRegistroP( fstream& );
int obtenernCodigoP( const char * const );
void modificarRegistroP( fstream& );
void eliminarRegistroP( fstream& );
void consultarRegistroP( fstream& );
void mostrarLineaPantallaP( const DatosPuestos &);

using namespace std;

Puestos::Puestos()
{
    fstream creditoEntradaSalida( "Puestos.dat", ios::in | ios::out | ios::binary);
    if ( !creditoEntradaSalida ) {
        cerr << "No se pudo abrir el archivo." << endl;
        crearArchivoCreditoP();
        cout <<  "Archivo creado satisfactoriamente, pruebe de nuevo\n";
        exit ( 1 );
    }

    enum Opciones { agregar = 1, nuevo, modificar, eliminar, mostrar, FIN };
    int opcion;
    while ( ( opcion = opcionP() ) != FIN ) {
        switch ( opcion ) {
            case agregar:
                imprimirRegistroP( creditoEntradaSalida );
            break;
            case nuevo:
                nuevoRegistroP( creditoEntradaSalida );
            break;
            case modificar:
                modificarRegistroP( creditoEntradaSalida );
            break;
            case eliminar:
                eliminarRegistroP( creditoEntradaSalida );
            break;
            case mostrar:
                consultarRegistroP( creditoEntradaSalida );
            break;
            default:
            cerr << "Opcion incorrecta" << endl;
            break;

      } //FIN SWITCH

       creditoEntradaSalida.clear();

   } //FIN WHILE
}
int opcionP()
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
	cout<<"\t\t\t |   PUESTOS, MONICA PEREZ; 9959-21-1840  |"<<endl;
	cout<<"\t\t\t--------------------------------------------"<<endl;

    cout<< "\n\n\t\t\t 1. Guardar archivo de texto para Imprimirlo" << endl
        << "\t\t\t 2. Agregar Puesto" << endl
        << "\t\t\t 3. Modificar Puesto" << endl
        << "\t\t\t 4. Eliminar Puesto" << endl
        << "\t\t\t 5. Mostrar Lista de Puestos" << endl
        << "\t\t\t 6. Regresar al Menu Principal" << endl
        <<"\n\t\t\t--------------------------------------------"<<endl
        << "\n\t\t\tIngrese su opcion: ";
    int opcionMenu ;

    cin >> opcionMenu;

   return opcionMenu;
}
void imprimirRegistroP( fstream &leerDeArchivo )
{
    ofstream archivoImprimirSalida( "ImprimirPuesto.txt", ios::out );
    if ( !archivoImprimirSalida ) {
        cerr << "No se pudo crear el archivo." << endl;
        exit( 1 );

    } //FIN DE INSTRUCCION if

    archivoImprimirSalida << left << setw( 14 ) << "Codigo" << setw( 15 )<< "Nombre" << setw( 14 ) << "Salario" << endl;
    leerDeArchivo.seekg( 0 );

    DatosPuestos puestos;
    leerDeArchivo.read( reinterpret_cast< char * >( &puestos ), sizeof( DatosPuestos ) );

    while ( !leerDeArchivo.eof() ) {
        if ( puestos.obtenerCodigo() != 0 )
        mostrarLineaP( archivoImprimirSalida, puestos );
        leerDeArchivo.read( reinterpret_cast< char * >( &puestos ), sizeof( DatosPuestos ) );
    } //FIN DE WHILE

    cout<<"\n";
    system("pause");
} //FIN DE LA FUNCION -IMPRIMIR REGISTRO-
void mostrarLineaP( ostream &salida, const DatosPuestos &registro )
{
   salida << left << setw( 18 ) << registro.obtenerCodigo()
          << setw( 16 ) << registro.obtenerNombre().data()
          << setw( 14 ) << registro.obtenerSalario() << endl;

}//FIN -MOSTRARLINEA-
void crearArchivoCreditoP()
{
    ofstream creditoSalida( "Puestos.dat", ios::out | ios::binary );
    if ( !creditoSalida ) {
      cerr << "No se pudo abrir el archivo." << endl;
      exit( 1 );
    }
    DatosPuestos puestosEnBlanco;
    for ( int i = 0; i < 100; i++ )
        creditoSalida.write(reinterpret_cast< const char * >( &puestosEnBlanco ), sizeof( DatosPuestos ) );
    cout<<"\n";
    system("pause");
}
void nuevoRegistroP( fstream &insertarEnArchivo )
{
    int codigo = obtenernCodigoP( "\nEscriba el Codigo del Puesto " );
    insertarEnArchivo.seekg( ( codigo - 1 ) * sizeof( DatosPuestos ) );
    DatosPuestos puestos;
    insertarEnArchivo.read( reinterpret_cast< char * >( &puestos ), sizeof( puestos ) );

    if ( puestos.obtenerCodigo() == 0 ) {
        char nombre[ 15 ];
        double salario;

        cout<<"Escriba el Nombre del Puesto: ";
        cin>> setw( 15 ) >> nombre;
        cout<<"Escriba el Salario del Puesto: ";
        cin>> salario;
        puestos.establecerNombre( nombre );
        puestos.establecerSalario( salario );
        puestos.establecerCodigo( codigo );

        insertarEnArchivo.seekp( ( codigo - 1 ) * sizeof( puestos ) );
        insertarEnArchivo.write( reinterpret_cast< const char * >( &puestos ), sizeof( puestos ) );
        cout<<"\n Puesto agregado Exitosamente..."<<endl;

    } //FIN IF
    else
        cerr << "El Puesto con codigo #" << codigo << " ya contiene informacion.\n" << endl;
    cout<<"\n";
    system("pause");
}
int obtenernCodigoP( const char * const indicador )
{
   int codigo;
    do {
      cout << indicador << "(1 - 100): ";
      cin >> codigo;

    } while ( codigo < 1 || codigo > 100 );

   return codigo;

} //FIN -OBTENERCODIGO-
void modificarRegistroP( fstream &actualizarArchivo )
{
    int opcionAc=0;
    cout<<"\nEscoja opcion a Actualizar: \n 1. Nombre\n 2. Salario\n  R - ";
    cin>>opcionAc;

    if (opcionAc == 1){
        int codigo = obtenernCodigoP( "\nEscriba el codigo del Puesto que desea Modifcar" );

        actualizarArchivo.seekg(( codigo - 1 ) * sizeof( DatosPuestos ));

        DatosPuestos puestos;
        actualizarArchivo.read( reinterpret_cast< char * >( &puestos ), sizeof( DatosPuestos ) );

        if (puestos.obtenerCodigo() != 0 ) {
            mostrarLineaP( cout, puestos );
            cout << "\nEscriba el nuevo Nombre: ";
            string nombre;
            cin >> nombre;

            string nombreAnterior = puestos.obtenerNombre();
            puestos.establecerNombre( nombre );
            mostrarLineaP( cout, puestos );

            actualizarArchivo.seekp(( codigo - 1 ) * sizeof( DatosPuestos ));

            actualizarArchivo.write(reinterpret_cast< const char * >( &puestos ), sizeof( DatosPuestos ) );
        }

    }else if (opcionAc== 2){
        int codigo = obtenernCodigoP( "\nEscriba el codigo del Puesto que desea Modifcar" );

        actualizarArchivo.seekg(( codigo - 1 ) * sizeof( DatosPuestos ));

        DatosPuestos puestos;
        actualizarArchivo.read( reinterpret_cast< char * >( &puestos ), sizeof( DatosPuestos ) );

        if (puestos.obtenerCodigo() != 0 ) {
            mostrarLineaP( cout, puestos );
            cout << "\nEscriba el nuevo Salario: ";
            double salario;
            cin >> salario;

            double salarioAnterior = puestos.obtenerSalario();
            puestos.establecerSalario( salario );
            mostrarLineaP( cout, puestos );

            actualizarArchivo.seekp(( codigo - 1 ) * sizeof( DatosPuestos ));
            actualizarArchivo.write(reinterpret_cast< const char * >( &puestos ), sizeof( DatosPuestos ) );
        }
    }
    cout<<"\n";
    system("pause");

} //FIN DE -ACTUALIZAR REGISTRO-
void eliminarRegistroP( fstream &eliminarDeArchivo )
{
    int codigo = obtenernCodigoP( "\nEscriba el codigo del Puesto a Eliminar" );
    eliminarDeArchivo.seekg( ( codigo - 1 ) * sizeof( DatosPuestos ) );
    DatosPuestos puestos;
    eliminarDeArchivo.read( reinterpret_cast< char * >( &puestos ), sizeof( DatosPuestos ) );

    if ( puestos.obtenerCodigo() != 0 ) {
        DatosPuestos puestoEnBlanco;
        eliminarDeArchivo.seekp( ( codigo - 1 ) * sizeof( DatosPuestos ) );
        eliminarDeArchivo.write( reinterpret_cast< const char * >( &puestoEnBlanco ), sizeof( DatosPuestos ) );

      cout << " Cuenta #" << codigo << " eliminada Exitosamente.\n";

   } //FIN IF

   //ERROR SI NO EXISTE
   else
      cerr << "La cuenta #" << codigo << " esta vacia.\n";
    cout<<"\n";
    system("pause");
} //FIN -ELIMINARREGISTRO-
void consultarRegistroP( fstream &leerDeArchivo )
{
    cout << left << setw( 10 ) << "\nCodigo" << setw( 14 ) << " Nombre" << setw( 12 ) << " Salario" << endl;
    leerDeArchivo.seekg( 0 );
    DatosPuestos puestos;
    leerDeArchivo.read( reinterpret_cast< char * >( &puestos ), sizeof( DatosPuestos ) );
    while ( !leerDeArchivo.eof() ) {
        if ( puestos.obtenerCodigo() != 0 )
            mostrarLineaPantallaP( puestos );
            leerDeArchivo.read( reinterpret_cast< char * >( &puestos ), sizeof( DatosPuestos ) );

   } //FIN WHILE
    cout<<"\n";
    system("pause");
} //FIN CONSULTAR REGISTRO
void mostrarLineaPantallaP( const DatosPuestos &registro )
{
   cout << left <<" "<< setw( 10 ) << registro.obtenerCodigo()
          << setw( 14 ) << registro.obtenerNombre().data()
          << setw( 12 ) << registro.obtenerSalario() << endl;
} //FIN -MOSTRARLINEAENOANTALLA-

Puestos::~Puestos()
{
    //dtor
}

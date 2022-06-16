#include "Catalogos.h"
#include "Entrenador.h"
#include "Puestos.h"
#include "Equipo.h"

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

int opcionCat();

Catalogos::Catalogos()
{
    enum Opciones { entrenador = 1, puestos, /*equipo, /*jugador, pais,*/ FIN };
    int opcion;
    while (( opcion = opcionCat() ) != FIN)
    {
        switch ( opcion ) {
            case entrenador:
                {
                    Entrenador claseentrenador;
                }
            break;
            case puestos:
                {
                    Puestos clasepuestos;
                }
            break;
            /*case equipo:
                {
                    Equipo claseequipo;
                }
            break;*/
        }
    } //FIN SWITCH

} //FIN WHILE

int opcionCat(){
    system("cls");

    cout<<"\t\t\t---------------------------------------------------"<<endl;
	cout<<"\t\t\t |   MENU CATALOGOS, MONICA PEREZ; 9959-21-1840  |"<<endl;
	cout<<"\t\t\t---------------------------------------------------"<<endl;

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

Catalogos::~Catalogos()
{
    //dtor
}

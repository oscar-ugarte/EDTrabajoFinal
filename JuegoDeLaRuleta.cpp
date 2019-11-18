#include <stdlib.h>
#include <stdio.h>
#include <iostream>
//Para limpiar la pantalla
#include <cstdlib>

using namespace std;

typedef char tcad[30];

//Menu de Opciones
void menuDeInicio(int &opcion);
void menuDeJuego(int &opcion);

main()
{
	int opcion_inicio, opcion_juego;
	do
	{
		system("cls");	
		menuDeInicio(opcion_inicio);
		switch(opcion_inicio)
		{
			case 1:
				
				break;
			case 2:
			
				break;
			case 3:
			
				break;	
			case 4:
			
				break;
				
			case 5:
			
				break;
			case 6:
				do
				{
					system("cls");
					menuDeJuego(opcion_juego);
					switch(opcion_juego)
					{
						case 1:
							
							break;
						case 2:
						
							break;
						case 3:
						
							break;
						case 4:
							cout << "GRACIAS POR JUGAR EN EL CASINO DEL APU 2008 - VUELVA PRONTO!!!" << endl;
							break;
						default:				
							cout << "OPCION INCORRECTA, intente de nuevo." << endl;			
					}
					if(opcion_juego != 4 ) // Se pregunta si es distinto de 4 para que no muestre 2 veces la opcion de presione una tecla.
						system("pause");	
				}while(opcion_juego != 4 );
				break;	
			case 7:
				cout << "FIN DEL PROGRAMA." << endl;
				break;
			default:
				cout << "OPCION INCORRECTA, intente de nuevo." << endl;					
		}
		if(opcion_inicio != 7 ) //Para que cuando salga del juego no pida oprimir una tecla para continuar.
			system("pause");		
	}while(opcion_inicio != 7 );	
}

//Menu de Inicio
void menuDeInicio(int &opcion)
{
	cout << "************ PRINCIPAL ************" << endl;	
	cout << "1- Generar ruleta." << endl;	
	cout << "2- Crear/Leer tapete de apuestas." << endl;	
	cout << "3- Registrar jugador." << endl;	
	cout << "4- Consultar/Modificar jugador." << endl;	
	cout << "5- Listar de jugadores." << endl;	
	cout << "6- Jugar." << endl;
	cout << "7- Salir." << endl;	
	cout << "***********************************" << endl;
	cout << "Elija una opcion: " ;
	cin >> opcion;	
}

//Menu del Juego
void menuDeJuego(int &opcion)
{
	cout << "***** JUEGO DE RULETA *****" << endl;
	cout << "1- Seleccionar jugadores." << endl;
	cout << "2- Realizar apuestas." << endl;
	cout << "3- Girar ruleta." << endl;
	cout << "4- Salir."<< endl;
	cout << "***************************"<< endl;
	cout << "Elija una opcion: ";
	cin >> opcion;
}

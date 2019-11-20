#include <stdlib.h>
#include <stdio.h>
#include <iostream>
//Para limpiar la pantalla
#include <cstdlib>

//Archivos que contienen las funcionalidades por aparte
#include "ListaDobleRuleta.hpp"
#include "ManejoTapete.h"
#include "ManejoJugadores.hpp"

using namespace std;

typedef FILE *parchivo; //Para el meno de archivos

//Menu de Opciones
void menuDeInicio(int &opcion);
void menuDeJuego(int &opcion);

main()
{
	parchivo tapete, jugadores;
	
	//Para la ruleta
	tlistaDC lista_ruleta;
	iniciarListaDoble(lista_ruleta);
	
	//Para el tapete
	tlistaS lista_tapete;
	iniciarListaSimple(lista_tapete);
	pnodo2 nodo_ganador;
	//Para los jugadores	
	pnodo3 arbol_jugadores;
	iniciarArbol(arbol_jugadores);
	tjugador jugador;
	tcad nombre_buscado, apellido_buscado ;
	
	int opcion_inicio, opcion_juego, numero_ganador, id_buscado;
	char respuesta_sentido, respuesta;
	do
	{
		system("cls");	
		menuDeInicio(opcion_inicio);
		switch(opcion_inicio)
		{
			case 1:
				if(lista_ruleta.inicio == NULL )
				{
					generarRuleta(lista_ruleta);
					cout << "Se creo la ruleta." << endl;
				}
				else
				{
					cout << "Crear una nueva ruleta S/N: " ;
					cin >> respuesta;
					if( respuesta == 'S' || respuesta == 's' )
					{
						generarRuleta(lista_ruleta);
						cout << "Se creo una nueva ruleta." << endl;	
					}
				}
				cout << "Mostrar el contenido (Sentido Horario) de la ruleta S/N: " ;
				cin >> respuesta;
				if ( respuesta == 'S' || respuesta == 's' )
					mostrarContenidoRuleta(lista_ruleta);
				break;
			case 2:
				if(existeArchivoDelTapete()  == true )
				{
					cout << "El archivo tapete.txt ya existe." << endl;
				}
				else
				{
					crearTapete(tapete);
					cout << "Se creo el archivo del tapete." << endl;
				}
				crearListaDelTapete(tapete, lista_tapete);
				cout << "Ver el contenido del tapete (Lista) S/N: " ;
				cin >> respuesta;
				if(respuesta == 'S' || respuesta == 's' )
				{
					mostrarListaTapete(lista_tapete);	
				}
				cout << endl;			
				break;
			case 3:
				altaDeJugadores(jugadores);
				break;	
			case 4:
				//Se pregunta si existe el archivo jugadores.txt para que no de error
				if( existeArchivoDeJugadores() == false )
				{
					cout << "El archivo de jugadores no existe. Acceda primero a la opcion 3 y cargue jugadores." << endl;
				}
				else
				{
					if( tieneJugadoresCargados() == true )
					{
						cout << "Consultar jugador por ID(I) o Nombre y Apellido(N): ";
						cin >> respuesta;
						if( respuesta == 'I' || respuesta == 'i' )
						{
							cout << "Ingrese ID para buscar: " ;
							cin >> id_buscado;
							jugador = obtenerJugadorPorID(jugadores, id_buscado);
						}
						else
						{
							fflush( stdin );
							cout << "Ingrese nombre: " ;
							gets(nombre_buscado);
							fflush( stdin );
							cout << "Ingrese apellido: " ;
							gets(apellido_buscado);
							fflush( stdin );
							jugador = obtenerJugadorPorNyA(jugadores, nombre_buscado, apellido_buscado);					
						}
						//Si el jugador obtenido tiene un id = -1 quiere decir que no lo encontro.
						if( jugador.id_jugador == -1 )
							cout << "Jugador no encontrado." << endl;
						else
						{
							cout << "Jugador Encontrado:" << endl;
							mostrarJugador(jugador);
							cout << "Cambiar monto del jugador S/N: " ;
							cin >> respuesta ;
							if( respuesta == 'S' || respuesta == 's' )
								modificarMontoDelJugador(jugadores, jugador.id_jugador);
						}	
					}
					else
					{
						cout << "No hay jugadores cargados para consultar. Elija la opcion 3 y cargue jugadores para consultar." << endl;
					}	
				}
				break;				
			case 5:
				//Se pregunta si existe el archivo jugadores.txt para que no de error
				if( existeArchivoDeJugadores() == false )
				{
					cout << "El archivo de jugadores no existe. Acceda primero a la opcion 3 y cargue jugadores." << endl;
				}
				else
				{
					//Se pregunta si tiene jugadores cargados.
					if( tieneJugadoresCargados() == true )
					{
						//Si ya existe un arbol creado se vaciara y volvera a crear para actualizar los datos.
						if( arbol_jugadores != NULL )
						{
							vaciarArbolDeJugadores(jugadores, arbol_jugadores);
							crearArbolDeJugadores(jugadores, arbol_jugadores);
						}
						else
						{
							crearArbolDeJugadores(jugadores, arbol_jugadores);
						}
						recorrerOrdenDecreciente(arbol_jugadores); //Entonces se muestra el contenido.	
					}
					else
					{
						cout << "No hay jugadores cargados. Elija la opcion 3 y cargue jugadores." << endl;
					}
				}			
				break;
			case 6:
				if( lista_ruleta.inicio != NULL && lista_tapete.inicio != NULL )
				{
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
								cout << "Sentido horario S/N:  ";
								cin >> respuesta_sentido ;
								if( respuesta_sentido == 'S' || respuesta_sentido == 's' )
									numero_ganador = girarRuleta(lista_ruleta, true);
								else
									numero_ganador = girarRuleta(lista_ruleta, false);
									nodo_ganador = obtenerNumeroDeLaListaTapete(lista_tapete, numero_ganador);
									mostrarNumeroDelTapete(nodo_ganador->numero);							
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
				}
				else
				{
					cout << "Asegurese de haber ingresado a las opciones 1, 2 y 3 antes." << endl;
				}
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

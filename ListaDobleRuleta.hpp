/*
Este archivo contiene todas las funcionalidades y estructuras de la lista
doble circular para la ruleta.
*/
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
//Para generar numeros aleatorios
#include<time.h> 

using namespace std;

typedef struct tnodo *pnodo;
typedef struct tnodo{
	int dato;
	pnodo sig, ant;	
}; 

//tlistaDC para referirse a la lista doble circular y diferenciarla de la otra lista simple.
typedef struct tlistaDC 
{
	pnodo inicio;
	pnodo final;	
};

//Inicia la lista doble para la ruleta
void iniciarListaDoble(tlistaDC &lista)
{
	lista.inicio = NULL;
	lista.final = NULL;
}

//Crea un nodo con el numero pasado por parametro
void crearNodoDeLaRuleta(pnodo &nuevo, int numero)
{
	nuevo = new tnodo;
	if(nuevo == NULL)
		cout << "Memoria insuficiente." << endl;
	else
	{
		nuevo->dato = numero;
		nuevo->sig = NULL;
		nuevo->ant = NULL;	
	}	
}

//Agrega un nuevo nodo al inicio
void agregarAlInicioRuleta(tlistaDC &lista, pnodo nuevo)
{
	if(lista.inicio == NULL)
	{
		nuevo->sig = nuevo;
		nuevo->ant = nuevo;
		lista.inicio = nuevo;
		lista.final = nuevo;
	}
	else
	{
		nuevo->sig = lista.inicio;
		lista.inicio->ant = nuevo;
		lista.inicio = nuevo;
		//Para la lista circular
		lista.inicio->ant = lista.final;
		lista.final->sig = lista.inicio;
	}
}

//Quita el primero valor de la lista
pnodo quitarDelInicioRuleta(tlistaDC &lista)
{
	pnodo eliminado = NULL;
	if( lista.inicio != NULL )
	{
		if(lista.inicio == lista.final)
		{
			eliminado = lista.inicio;
			lista.inicio = NULL;
			lista.final = NULL;
			//eliminado->sig = NULL;
			//eliminado->ant = NULL;	
		}
		else
		{
			eliminado = lista.inicio;
			lista.inicio = lista.inicio->sig;
			lista.inicio->ant = NULL;
			//eliminado->sig = NULL;
			//eliminado->ant = NULL;
			//Para mantener la lista circular
			if(lista.inicio != NULL)
			{
				lista.inicio->ant = lista.final;
			}
		}
		//	
		eliminado->sig = NULL;
		eliminado->ant = NULL;
	}
	return eliminado;	
}

//Para revisar que los valores que vayan a agregarse no se repitan.
bool buscarNumeroRepetido(tlistaDC lista, int buscado)
{
	pnodo i;
	bool encontrado = false;
	if(lista.inicio != NULL)
	{
		if( lista.inicio == lista.final)
		{
			if(lista.inicio->dato == buscado )
				encontrado = true;
		}
		else
		{
			if(lista.inicio->dato == buscado)
				encontrado = true;
			else
			{
				if(lista.final->dato == buscado)
				{
					encontrado = true;
				}
				else
				{
					for(i = lista.inicio->sig ; !encontrado && i != lista.final  ; i = i->sig )
					{
						if(i->dato == buscado)
						{
							encontrado = true;
						}
					}	
				}	
			}	
		}
	}
	return encontrado;
}

//Vacia y libera el espacio de los nodos de una lista.
//Sera usada cuando se ingrese a la opcion de crear ruleta y ya exista una. Entonces se vaciarà esa ruleta para crear una nueva.
void vaciarContenidoRuleta(tlistaDC &lista )
{
	pnodo eliminado;
	while(lista.inicio != NULL )
	{
		eliminado = quitarDelInicioRuleta(lista);
		delete eliminado;
	}
}

//Crea la lista doble circular con los 36 valores y el cero.
void generarRuleta(tlistaDC &lista)
{
	pnodo nuevo;
	bool cargado; // Sirve para indicar que cuando es verdadero que ya se carga un valor no repetido.
	int j, numero_generado;
	//Si la lista ya existe se vaciarà el contenido. Entonces se cargara con un nuevo orden.
	if(lista.inicio != NULL )
	{
		vaciarContenidoRuleta(lista);	
	}
	for(j = 1 ; j <= 36 ; j++)
	{
		cargado = false; // Se inicializa en false para que el ciclo de generar numeros se repita hasta generar un numero no repetido.
		while( cargado == false )
		{
			numero_generado = 1+rand()%36; //Entre 1 y 36 . El 0 se agregara al final del metodo
			if( buscarNumeroRepetido(lista, numero_generado) == false )
			{
				crearNodoDeLaRuleta(nuevo, numero_generado);
				if( nuevo != NULL )
				{
					agregarAlInicioRuleta(lista, nuevo);
					cargado = true;
				}
			}
		}
	}
	crearNodoDeLaRuleta(nuevo, 0); //Esto permite que el inicio de la ruleta apunte a 0
	if( nuevo != NULL)
	{
		agregarAlInicioRuleta(lista, nuevo);	
	}
}

//Realiza el giro de la rulete
int girarRuleta(tlistaDC lista, bool horario )
{
	pnodo i ;
	int numero = rand()%10, partida ;
	cout << "Se avanzara espacios = " << numero << endl ;
	i = lista.inicio ;
	if( horario == true )
	{
		for( partida = 0 ; partida <= numero ; partida++ )
		{
			i = i->sig ;
		}
	}
	else
	{
		for( partida = 0 ; partida <= numero ; partida++ )
		{
			i = i->ant;
		}
	}
	cout << "Resultado final: " << i->dato << endl;
	return i->dato;
}

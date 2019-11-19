/*
Este archivo contendra las estructuras y funcionalidades para crear el archivo jugadores.txt, realizar
consultas/actualizaciones y manejar un arbol binario de busqueda con los jugadores.
Para diferenciar los tnodos y pnodos de la ruleta y el tapete aqui se llamaran tnodo3 y pnodo3. 
*/
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstring> //Comparar cadenas
#include <cctype> // Para convertir a mayusculas y minisculas

using namespace std;

typedef char tcad[40];

typedef FILE *parchivo;

/////Estructura para el jugador y el arbol

typedef struct tjugador
{
	int id_jugador;
	tcad nombre;
	tcad apellido;
	double monto_dinero;
	double ganancia;	
};

typedef struct tnodo3 *pnodo3;
typedef struct tnodo3
{
	tjugador jugador;
	pnodo3 izq, der;
};

/////Para la creacion del archivo y su manejo

//Convierte una cadena en minusculas. Para poder compararla despues.
void convertirAMinusculas(tcad cadena)
{
	int i;
	for( i = 0 ; i < strlen(cadena) ; i++ )
	{
		cadena[i] = tolower(cadena[i]);
	}
}

//Valida que el monto que ingrese el usuario no sea negativo.
void validarMonto( double &monto )
{
	do
	{
		cin >> monto;
		if(monto < 0)
			cout << "Monto invalido. Ingrese de nuevo el monto: " ;
	}while( monto < 0 );
}

//Actualiza  el monto de un jugador
void actualizarMonto(tjugador &jugador, double nuevo_monto )
{
	jugador.monto_dinero = nuevo_monto;
}

//Actualiza la ganancia de un jugador
void actualizarGanancia(tjugador &jugador, double ganancia)
{
	jugador.ganancia = ganancia;
}

//Muestra los datos de un jugador
void mostrarJugador(tjugador j)
{
	cout << "ID: " << j.id_jugador << endl;
	cout << "Nombre: " << j.nombre << endl;
	cout << "Apellido:" << j.apellido << endl;
	cout << "Monto: $ " << j.monto_dinero << endl;
	cout << "Ganancia: $ " << j.ganancia << endl;
}

//Crea un nuevo jugador
void crearJugador(tjugador &j)
{
	fflush( stdin );
	cout << "Ingrese id de jugador: " ;
	cin >> j.id_jugador;
	cout << "Ingrese nombre del jugador: " ;
	fflush( stdin );
	gets(j.nombre);
	cout << "Ingrese apellido del jugador: " ;
	fflush( stdin );
	gets(j.apellido);
	cout << "Ingrese el monto del jugador: " ;
	fflush( stdin );
	validarMonto(j.monto_dinero); //Se valida que no ingrese negativos.
	j.ganancia = 0;  
	//cout << "Ingrece ganancia del jugador: "  ;
	//fflush( stdin );
	//cin >> j.ganancia;
}

//Valida que el id del nuevo jugador no se repita
bool jugadorRepetidoID(parchivo jugadores, int id)
{
	bool encontrado = false;
	tjugador jugador;
	jugadores =fopen("jugadores.txt", "rb" );
	while( !feof(jugadores) && !encontrado )
	{
		fread(&jugador, sizeof(jugador), 1, jugadores);
		if( !feof(jugadores) ) 
			if( jugador.id_jugador == id )
				encontrado = true;
	}
	fclose(jugadores);	
	return encontrado;
}

bool jugadorRepetidoNyA(parchivo jugadores, tcad nombre, tcad apellido )
{
	//Convierte a minusculas el nombre y apellido pasado por parametro.
	convertirAMinusculas(nombre);
	convertirAMinusculas(apellido);
	bool encontrado = false;
	tjugador jugador;
	jugadores =fopen("jugadores.txt", "rb" );
	while( !feof(jugadores) && !encontrado )
	{
		fread(&jugador, sizeof(jugador), 1, jugadores);
		if( !feof(jugadores) )
		{
			convertirAMinusculas(jugador.nombre);
			convertirAMinusculas(jugador.apellido);		 
			if( strcmp(jugador.nombre, nombre) == 0 && strcmp(jugador.apellido, apellido) == 0  )
				encontrado = true;	
		}
	}
	fclose(jugadores);	
	return encontrado;
}

//Permite agregar uno o màs jugadores al archivo jugadores.txt
void altaDeJugadores(parchivo &jugadores)
{
	tjugador nuevo_jug;
	char resp;
	do
	{
		cout << "¿Ingresar un jugador? " ;
		cin >> resp;
		if( resp == 'S' || resp == 's' )
		{
			crearJugador(nuevo_jug);
			if( jugadorRepetidoID( jugadores, nuevo_jug.id_jugador ) == false  )
			{
				if( jugadorRepetidoNyA(jugadores, nuevo_jug.nombre, nuevo_jug.apellido) == false )
				{
					//Si el jugador no se repite recien se abre, se agrega y cierra el archivo. Por conflicto con los validadores anteriores 
					jugadores = fopen("jugadores.txt", "ab");
					fwrite(&nuevo_jug, sizeof(nuevo_jug), 1, jugadores );
					fclose(jugadores);	
				}
				else
				{
					cout << "Nombre y apellido del jugador repetido." << endl;
				}
			}
			else
			{
				cout << "ID del jugador repetido." << endl;
			}	
		}
	}while( resp == 'S' || resp == 's' );
}

//Buscar un jugador que coincida con el id pasado por parametros y si lo encuentra lo devuelve.
//Si no lo encuentra devuelve un jugador con id negativo.
tjugador obtenerJugadorPorID(parchivo jugadores, int id)
{
	bool encontrado = false;
	tjugador jugador;
	jugadores =fopen("jugadores.txt", "rb" );
	while( !feof(jugadores) && !encontrado )
	{
		fread(&jugador, sizeof(jugador), 1, jugadores);
		if( !feof(jugadores) ) 
			if( jugador.id_jugador == id )
			{
				encontrado = true;				
			}
	}
	fclose(jugadores);
	if(encontrado == false) //Pregunta si no se encontrò
	{
		jugador.id_jugador = -1; //El id del jugador sera -1. Esto debera controlarse desde donde se llame a la funcion.
	}	
	return jugador ;	
}

//Buscar un jugador que coincida con el nombre y apellido pasado por parametros y si lo encuentra lo devuelve.
//Si no lo encuentra devuelve un jugador con id negativo.
tjugador obtenerJugadorPorNyA(parchivo jugadores, tcad nombre, tcad apellido)
{
	//Convierte a minusculas el nombre y apellido pasado por parametro.
	convertirAMinusculas(nombre);
	convertirAMinusculas(apellido);
	bool encontrado = false;
	tjugador jugador;
	jugadores =fopen("jugadores.txt", "rb" );
	while( !feof(jugadores) && !encontrado )
	{
		fread(&jugador, sizeof(jugador), 1, jugadores);
		if( !feof(jugadores) )
		{
			convertirAMinusculas(jugador.nombre);
			convertirAMinusculas(jugador.apellido);		 
			if( strcmp(jugador.nombre, nombre) == 0 && strcmp(jugador.apellido, apellido) == 0  )
				encontrado = true;	
		}
	}
	fclose(jugadores);
	if(encontrado == false) //Pregunta si no se encontrò
	{
		jugador.id_jugador = -1; //El id del jugador sera -1. Esto debera controlarse desde donde se llame a la funcion.
	}	
	return jugador;	
}

//Buscar un jugador por su id. Si lo encuentra pide que se ingrese un nuevo monto para el jugador.
void modificarMontoDelJugador(parchivo &jugadores, int id)
{
	tjugador jugador;
	bool encontrado = false;
	jugadores = fopen( "jugadores.txt", "rb+" );
	while( !feof(jugadores) && !encontrado )
	{
		fread(&jugador, sizeof(jugador), 1, jugadores);
		if(jugador.id_jugador == id);
		{
			cout << "Jugador elegido: " << endl;
			mostrarJugador(jugador);
			encontrado = true;
		}
	}
	if(encontrado == false)
	{
		cout << "No se encontro jugador." << endl;
	}
	else
	{
		cout << "Ingrese el nuevo monto del jugador: " ;
		validarMonto(jugador.monto_dinero);
		fseek(jugadores, -sizeof(jugador),SEEK_CUR);
		fwrite(&jugador, sizeof(jugador), 1, jugadores);
	}
	fclose(jugadores);
}

//Busca al jugador del ID. Si lo encuentra actualiza el monto de dinero y la ganancia.
//El parametro de monto puede ser positivo o negativo. La ganancia debe ser positivo. 
void actualizarDineroDelJugador(parchivo &jugadores, int id, double monto, double ganancia )
{
	tjugador jugador;
	bool encontrado = false;
	jugadores = fopen( "jugadores.txt", "rb+" );
	while( !feof(jugadores) && !encontrado )
	{
		fread(&jugador, sizeof(jugador), 1, jugadores);
		if(jugador.id_jugador == id);
		{
			encontrado = true;
		}
	}
	if(encontrado == false)
	{
		cout << "No se encontro." << endl;
	}
	else
	{
		actualizarMonto(jugador, jugador.monto_dinero + monto );
		actualizarGanancia(jugador, jugador.ganancia + ganancia );
		fseek(jugadores, -sizeof(jugador),SEEK_CUR);
		fwrite(&jugador, sizeof(jugador), 1, jugadores);
	}
	fclose(jugadores);	
}

//Comprueba si se a creado el archivo de jugadores
bool existeArchivoDeJugadores()
{
	bool existe = false;
	parchivo archivo;
	archivo = fopen("jugadores.txt", "rb");
	if( archivo != NULL )
		existe = true;
	fclose(archivo);
	return existe;	
}

/////Procedimientos y funciones para el manejo del arbol de jugadores

//Iniciar el arbol
void iniciarArbol(pnodo3 &arbol )
{
	arbol = NULL;
}

//Crea un nodo con los datos del jugador pasado por parametro.
void crearNodoDeArbol(pnodo3 &nuevo, tjugador jug )
{
	nuevo = new tnodo3;
	if( nuevo != NULL )
	{
		nuevo->jugador = jug;
		nuevo->der = NULL;
		nuevo->izq = NULL;
	}
	else
	{
		cout << "Memoria insuficiente." << endl;
	}
}

//Recorre el arbol del jugador con mayor ganancia al de menor ganancia.
void recorrerOrdenDecreciente(pnodo3 arbol)
{
	if(arbol != NULL)
	{
		recorrerOrdenDecreciente(arbol->der);
		mostrarJugador(arbol->jugador);
		recorrerOrdenDecreciente(arbol->izq);	
	}
}


//Inserta un nodo del arbol tomando como referencia la ganancia
void insercionArbol(pnodo3 &arbol, pnodo3 nuevo)
{
	if( arbol== NULL )
	{
		arbol = nuevo;
	}
	else
	{
		if( nuevo->jugador.ganancia < arbol->jugador.ganancia )
			insercionArbol(arbol->izq, nuevo);
		else
			insercionArbol(arbol->der, nuevo);
	}
}

//Intercambia 2 jugadores
void cambio(tjugador &jugador1, tjugador &jugador2)
{
	tjugador auxiliar = jugador1;
	jugador1 = jugador2;
	jugador2 = auxiliar;
}

//Busca el nodo con el menor valor (Ganancia) de los mayores del nodo elegido. 
pnodo3 menorMayores(pnodo3 elegido, pnodo3 &menor)
{
	pnodo3 aux;
	if( menor->izq != NULL )
	{
		aux = menorMayores(elegido, menor->izq);
	}
	else
	{
		cambio(elegido->jugador, menor->jugador);
		aux = menor;
		menor = menor->der;
	}
	return aux;
}

//Elimina un nodo del arbol que corresponda al valor de ganancia pasado por parametro
pnodo3 eliminarNodoDelArbol(pnodo3 &arbol, int valor )
{
	pnodo3 aux;
	if(arbol == NULL)
		aux = NULL;
	else
	{
		if( arbol->jugador.ganancia > valor  )	
			aux = eliminarNodoDelArbol(arbol->izq, valor);
		else
		{
			if( arbol->jugador.ganancia < valor )
			{
				aux = eliminarNodoDelArbol(arbol->der, valor);	
			}
			else
			{
				//Aqui ira
				aux = arbol;
				if( arbol->izq == NULL )
					arbol = arbol->der;
				else
				{
					if(arbol->der == NULL)
						arbol= arbol->izq;
					else
						aux = menorMayores(arbol, arbol->der )	;	
				}	
			}	
		}		
	}
	return aux;	
}

//Crea un arbol binario de busqueda con los jugadores del archivo jugadores.txt
void crearArbolDeJugadores(parchivo jugadores, pnodo3 &arbol)
{
	pnodo3 nuevo;
	tjugador jugador;
	jugadores =fopen("jugadores.txt", "rb" );
	while( !feof(jugadores) )
	{
		fread(&jugador, sizeof(jugador), 1, jugadores);
		if( !feof(jugadores) )
		{
			crearNodoDeArbol(nuevo, jugador);
			insercionArbol(arbol, nuevo);	
		} 
	}
	fclose(jugadores);	
}

//Vacia el contenido del arbol de jugadores eliminando los jugadores por la ganancia
void vaciarArbolDeJugadores(parchivo jugadores,  pnodo3 &arbol )
{
	pnodo3 eliminado;
	tjugador jugador;
	jugadores =fopen("jugadores.txt", "rb" );
	while( !feof(jugadores) )
	{
		fread(&jugador, sizeof(jugador), 1, jugadores);
		if( !feof(jugadores) )
		{
			eliminado = eliminarNodoDelArbol(arbol, jugador.ganancia );
			delete eliminado;
		} 
	}
	fclose(jugadores);		
}

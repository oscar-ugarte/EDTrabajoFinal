/*
Este archivo contendra las estructuras y funcionalidades para crear el archivo tapete.txt y
manejar una lista simple con su contenido.
Para diferenciar los tnodos y pnodos de la ruleta aqui se llamaran tnodo2 y pnodo2. 
*/
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

typedef FILE *parchivo;

typedef struct tnumero
{
	int cifra;
	char color; // r = rojo y n = negro
	char paridad; // par = p y impar i
	int docena ; 
	int columna ;
	int mitad;
};

typedef struct tnodo2 *pnodo2;
typedef struct tnodo2
{
	tnumero numero; //En vez de dato se llamara numero
	pnodo2 sig;
};

//La lista se llama tlistaS haciendo referencia a lista simple.
typedef struct tlistaS
{
	pnodo2 inicio, final;
};

/////Para el manejo de la lista

//Inicializa la lista simple.
void iniciarListaSimple(tlistaS &lista)
{
	lista.inicio = NULL;
	lista.final = NULL;
}

//Crea un nodo
void crearNodo(pnodo2 &nuevo, tnumero numero)
{
	nuevo = new tnodo2;
	if(nuevo != NULL)
	{
		nuevo->numero = numero;
		nuevo->sig = NULL;
	}
}

//Agrega un nodo al final de la lista del tapete.
void agregarAlFinalListaTapete(tlistaS &lista, pnodo2 nuevo)
{
	if(lista.inicio == NULL)
	{
		lista.inicio = nuevo;
		lista.final = nuevo;
	}
	else
	{
		lista.final->sig = nuevo;
		lista.final = nuevo;	
	}
}

//Quita un nodo del inicio de la lista del tapete
pnodo2 quitarDelInicioListaTapete(tlistaS &lista )
{
	pnodo2 eliminado = NULL;
	if( lista.inicio != NULL )
	{
		eliminado = lista.inicio;
		lista.inicio = lista.inicio->sig;
		eliminado->sig = NULL;
	}
	return eliminado;
}

//Apartir de una cifra o numero se obtiene el nodo correspondiente.
pnodo2 obtenerNumeroDeLaListaTapete(tlistaS lista, int buscado)
{
	pnodo2 numero = NULL, i;
	if( lista.inicio != NULL )
	{
		if(lista.inicio->numero.cifra == buscado )
		{
			numero = lista.inicio;
		}
		else
		{ 
			if(lista.final->numero.cifra == buscado )
			{
				numero = lista.final;
			}
			else
			{
				for(i = lista.inicio->sig ; i != lista.final && i->numero.cifra != buscado ; i = i->sig  );
				numero = i;
			}
		}
	}
	return numero;
}

/////Procedimientos y funciones generar el numero y mostrar el contenido de uno.

//Obtiene la docena a la que pertenece el numero
int obtenerDocena(int cifra)
{
	if(cifra >= 1 && cifra <= 12)
		return 1;
	else
	{
		if(cifra >= 13 && cifra <= 24)
		{
			return 2;
		}
		else
		{
			return 3;
		}		
	}	
}

//Permite identificar si la cifra pertenece a una columna.
bool comprobarColumna(int num_partida, int cifra)
{
	int i;
	bool pertenece = false;
	for(i = num_partida; i <= 36 && !pertenece ; i = i + 3 )
	{
		if( i == cifra )
			pertenece = true ;  
	}
	return pertenece;
}

//Obtiene la columna a la que pertenece la cifra
int obtenerColumna(int cifra)
{
	if( comprobarColumna(1, cifra) == true ) //Para la primera columna
		return 1;
	else
	{
		if( comprobarColumna(2, cifra) == true ) //Para la segunda columna
			return 2 ;
		else
			return 3 ; //Si no pertenece a las anteriores pertenece a las tercera.
	}	
}

//Crea un numero del tapete con la cifra pasada por parametro. El numero se guarda en el parametro numero.
void generarNumeroDelTapete(tnumero &numero, int cifra)
{
	if( cifra == 0 )
	{
		numero.cifra = cifra;
		numero.color = 'c';
		numero.paridad = 'c';
		numero.docena = 0;
		numero.mitad = 0;
		numero.columna = 0;
	}
	else
	{
		numero.cifra = cifra;
		if( cifra % 2 == 0 )
			numero.paridad = 'p';
		else
			numero.paridad = 'i';
		if( numero.paridad == 'p' )
			numero.color = 'n';
		else
			numero.color = 'r';
		numero.docena = obtenerDocena(cifra);
		numero.columna = obtenerColumna(cifra);
		if( cifra <= 18 )
			numero.mitad = 1;
		else				
			numero.mitad = 2;
	}
}

//Muestra la informaciòn de un numero del tapete.
void mostrarNumeroDelTapete(tnumero numero)
{
	cout << endl;
	cout << "CIFRA: " << numero.cifra << endl ;
	cout << "Paridad:"  << numero.paridad  << endl ;
	cout << "Color: " << numero.color << endl ;
	cout << "Docena: " << numero.docena << endl ;
	cout << "Columna: " << numero.columna << endl ;
	cout << "Mitad: " << numero.mitad << endl ;
}

/////Para generar el archivo tapete.txt, obtner su contenido y comprobar que existe el archivo

//Comprueba si existe el archivo del tapete.
bool existeArchivoDelTapete()
{
	bool existe = false;
	parchivo archivo;
	archivo = fopen("tapete.txt", "rb");
	if( archivo != NULL )
		existe = true;
	fclose(archivo);
	return existe;	
}

//Crea el archivo tapete.txt con su contenido.
void crearTapete(parchivo &tapete)
{
	int i;
	tnumero numero;
	tapete = fopen("tapete.txt", "ab");
	for( i = 0; i <= 36 ; i++ )
	{
		generarNumeroDelTapete(numero, i);
		fwrite(&numero, sizeof(numero), 1, tapete );
	}
	fclose(tapete);
}

//Visualiza el contenido del tapete
void listarTapete(parchivo tapete)
{
	tnumero numero;
	tapete = fopen("tapete.txt", "rb");
	while( !feof(tapete) )
	{
		fread(&numero, sizeof(numero), 1, tapete);
		 if(!feof(tapete))
		 {
		 	mostrarNumeroDelTapete(numero);
		 }
	}
	fclose(tapete);	
}

//Crea la lista simple con el contenido del tapete
void crearListaDelTapete(parchivo tapete, tlistaS &lista)
{
	pnodo2 nuevo;
	tnumero numero;
	tapete = fopen("tapete.txt", "rb");
	while( !feof(tapete) )
	{
		fread(&numero, sizeof(numero), 1, tapete);
		 if(!feof(tapete))
		 {
		 	crearNodo(nuevo, numero);
		 	agregarAlFinalListaTapete(lista, nuevo);
		 }
	}
	fclose(tapete);	
}

//Muestra el contenido de la lista del tapete.
void mostrarListaTapete(tlistaS lista)
{
	pnodo2 i;
	for(i = lista.inicio ; i != NULL ; i = i->sig )
	{
		mostrarNumeroDelTapete(i->numero);	
	}
}

//Vacia el contenido de la lista del tapete
void vaciarListaDelTapete(tlistaS &lista)
{
	pnodo2 i, eliminado;
	while( lista.inicio != NULL )  
	{
		eliminado = quitarDelInicioListaTapete(lista);
		delete eliminado;
	}
}

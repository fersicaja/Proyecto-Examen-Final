#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <string>
#include <Windows.h>

using namespace std;
//***********************************************************************************************************************//
/*Pila de estudiante dinamica*/
struct PilaEstudiante {
	char nom[30];
	char apellido[30];
	int edad;
	PilaEstudiante *sig; //direccion
};

PilaEstudiante *original, *aux; //Pila estudiante original y auxiliar

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x; coord.Y = y;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hStdOut, coord);
}

//asigna color a los textos
void SetColor(int ForgC)
{
	WORD wColor;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
}

//Ingresar datos a la pila
void Push() {
	system("cls");
	if (original == NULL) {
		original = new (PilaEstudiante);
		cout << "Ingresar informacion del estudiante" << endl;
		cout << "Nombre: ";
		cin >> original->nom;
		cout << "Apellido: ";
		cin >> original->apellido;
		cout << "Edad: ";
		cin >> original->edad;
		cout << "Datos ingresados correctamente" << endl;
		original->sig = NULL;
		return;
	}
	aux = new (PilaEstudiante);
	cout << "Ingresar informacion del estudiante" << endl;
	cout << "Nombre: ";
	cin >> aux->nom;
	cout << "Apellido: ";
	cin >> aux->apellido;
	cout << "Edad: ";
	cin >> aux->edad;
	cout << "Datos ingresados correctamente" << endl;
	aux->sig = original;
	original = aux;

}

//Mostrar en pantalla
void Mostrar() {
	system("cls");
	if (original == NULL) {
		cout << "No hay datos en la pila de Estudiantes" << endl;
	}
	aux = original;
	while (aux != NULL) {
		cout << "Informacion de Estudiante" << endl;
		cout << aux->nom << endl;
		cout << aux->apellido << endl;
		cout << aux->edad << " anios" << endl << endl;
		aux = aux->sig;
	}
	cout << "Fin" << endl;
}

//Eliminar datos de la pila
void Pop() {
	if (original == NULL) {
		cout << "No hay datos en la Pila de Estudiantes" << endl;
		return;
	}
	aux = new (PilaEstudiante);
	aux = original;
	cout << "Estudiante Eliminado: " << aux->nom << " " << aux->apellido << ", " << aux->edad << " anios" << endl;
	original = aux->sig;
	delete(aux);
}


//Menu Principal
void MenuPilaDinamica() {
	int opc;
	do {
		system("cls");

		for (int i = 0; i < 6; i++) {
			SetColor(9); gotoxy(49, 5 + i); cout << "|";
			SetColor(9); gotoxy(82, 5 + i); cout << "|";
		}
		for (int i = 0; i < 34; i++) {
			SetColor(9); gotoxy(49 + i, 4); cout << "=";
			SetColor(9); gotoxy(49 + i, 11); cout << "=";
		}

		SetColor(0); gotoxy(50, 5); cout << "  Pila Dinamica de Estudiantes";
		SetColor(0); gotoxy(50, 6); cout << "	1. Ingresar/Push";
		SetColor(0); gotoxy(50, 7); cout << "	2. Mostrar";
		SetColor(0); gotoxy(50, 8); cout << "	3. Eliminar/Pop";
		SetColor(0); gotoxy(50, 9); cout << "	4. Salir";
		SetColor(0); gotoxy(50, 10); cout << "	Ingrese Opcion [   ]";
		SetColor(0); gotoxy(73, 10); cin >> opc;

		switch (opc) {
		case 1:
			system("cls");
			Push(); break;
		case 2:
			system("cls");
			Mostrar(); break;
		case 3:
			system("cls");
			Pop(); break;
		case 4:
			break;
		default: "\nNo es una opcion valida";
		}
		system("pause");
	} while (opc != 4);
}

/*Fin de la pila dinamica*/
//***********************************************************************************************************************************

/*Arbol binario*/
//************************************************************************************************************************************

typedef struct nodo1 {
	int nro;
	struct nodo1 *izq, *der;
}*ABB;
/* es un puntero de tipo nodo que hemos llamado ABB, que ulitizaremos
para mayor facilidad de creacion de variables */

ABB crearNodo(int x)
{
	ABB nuevoNodo = new(struct nodo1);
	nuevoNodo->nro = x;
	nuevoNodo->izq = NULL;
	nuevoNodo->der = NULL;

	return nuevoNodo;
}

void insertar(ABB &arbol, int x)
{

	if (arbol == NULL)
	{
		arbol = crearNodo(x);
	}
	else if (x < arbol->nro)
		insertar(arbol->izq, x);
	else if (x >= arbol->nro)
		insertar(arbol->der, x);
}

int X = 0;
void verArbol(ABB arbol, int Y)
{

	if (arbol == NULL) {
		return;
	}

	X += 5;//variable que permite posicionarse en el eje X
	verArbol(arbol->izq, Y + 2);

	if (arbol->izq != NULL) {
		gotoxy(2 + X - Y, 9 + Y); SetColor(15); cout << "/";
		gotoxy(3 + X - Y, 8 + Y); SetColor(15); cout << "("; SetColor(10); cout << arbol->nro; SetColor(15); cout << ")";
	}
	if (arbol->izq == NULL && arbol->der == NULL) {
		gotoxy(3 + X - Y, 8 + Y); SetColor(15); cout << "("; SetColor(10); cout << arbol->nro; SetColor(15); cout << ")";
	}
	if (arbol->der != NULL) {
		gotoxy(6 + X - Y, 9 + Y); SetColor(15);  printf("%c\n", 92);
		gotoxy(3 + X - Y, 8 + Y); SetColor(15); cout << "("; SetColor(10); cout << arbol->nro; SetColor(15); cout << ")";
	}

	verArbol(arbol->der, Y + 2);

}

int j = 1;
void mostrarTerminales(ABB arbol, int n) {


	if (arbol == NULL)
		return;
	mostrarTerminales(arbol->der, n + 1);

	if (arbol->izq == NULL && arbol->der == NULL)
		cout << "terminal " << j++ << " : " << arbol->nro << endl;

	mostrarTerminales(arbol->izq, n + 1);

}


int opc;
ABB arbol = NULL;   // creado Arbol

int n;  // numero de nodos del arbol
int x; // elemento a insertar en cada nodo


void menuArbol() {
	do {
		system("cls");
		cout << "\n\t\t  ..[ ARBOL BINARIO DE BUSQUEDA ]..  \n\n";

		cout << "\t\tMENU\n";
		cout << "1. Insertar datos" << endl;
		cout << "2. Mostrar arbol" << endl;
		cout << "3. Mostrar terminales" << endl;
		cout << "4. Salir" << endl;
		cout << "\n Ingrese opcion; ";
		cin >> opc;
		switch (opc)
		{
			system("cls");

		case 1:
			cout << " Numero del nodo: ";
			cin >> x;
			insertar(arbol, x);
			break;
		case 2:
			X = 0;
			cout << "\n Mostrando ABB \n\n";
			verArbol(arbol, 0);
			system("pause");
			break;
		case 3:
			cout << " \nTerminales:\n";
			mostrarTerminales(arbol, 0);
			system("pause");
			break;
		default: "opcion invalida";
			break;
		}
	} while (opc != 4);
}

//************************************************************************************************************************************

/*Floyd*/
//************************************************************************************************************************************
int nodos;

void floyds(int b[][10], int b2[][10])
{
	int i, j, k, p;
	int conta = 1;


	SetColor(9); gotoxy(2, 3); cout << "|";

	SetColor(9); gotoxy(2, 2); cout << "==================";
	SetColor(0); gotoxy(3, 3); cout << " Procedimiento: ";
	SetColor(9); gotoxy(2, 4); cout << "==================";

	SetColor(9); gotoxy(19, 3); cout << "|";

	cout << endl << endl;

	for (k = 0; k < nodos; k++)
	{

		for (i = 0; i < nodos; i++)
		{
			cout << endl;
			for (j = 0; j < nodos; j++)
			{
				if ((b[i][k] * b[k][j] != 0) && (i != j))
				{
					if ((b[i][k] + b[k][j] < b[i][j]) || (b[i][j] == 0))
					{
						b[i][j] = b[i][k] + b[k][j];
						b2[i][j] = conta;
					}
				}
				cout << "\t" << b[i][j];

			}
		}
		cout << endl;
		conta++;
	}

	_getch();

}

int vect1[10];
int vect2[10];

void menuFloyd()
{
	system("color F5"); //color de consola

	SetColor(9); gotoxy(40, 8); cout << "|";
	SetColor(9); gotoxy(40, 9); cout << "|";
	SetColor(9); gotoxy(40, 10); cout << "|";
	SetColor(9); gotoxy(40, 11); cout << "|";
	SetColor(9); gotoxy(40, 12); cout << "|";
	SetColor(9); gotoxy(40, 13); cout << "|";
	SetColor(9); gotoxy(40, 14); cout << "|";

	SetColor(9); gotoxy(40, 7); cout << "===============================";
	SetColor(0); gotoxy(41, 8); cout << " Programacion III";

	SetColor(0); gotoxy(41, 10); cout << " Integrantes: ";
	SetColor(0); gotoxy(41, 11); cout << " Ivan Mogollon 0901-16-11239";
	SetColor(0); gotoxy(41, 12); cout << " Luisa Sicaja  0901-16-16081";

	SetColor(0); gotoxy(41, 14); cout << "	Algoritmo de Floyd";

	SetColor(9); gotoxy(40, 15); cout << "===============================";

	SetColor(9); gotoxy(70, 8); cout << "|";
	SetColor(9); gotoxy(70, 9); cout << "|";
	SetColor(9); gotoxy(70, 10); cout << "|";
	SetColor(9); gotoxy(70, 11); cout << "|";
	SetColor(9); gotoxy(70, 12); cout << "|";
	SetColor(9); gotoxy(70, 13); cout << "|";
	SetColor(9); gotoxy(70, 14); cout << "|";

	int b2[10][10];
	SetColor(9); gotoxy(34, 18); cout << "|";

	SetColor(9); gotoxy(34, 17); cout << "===========================================";
	SetColor(0); gotoxy(35, 18); cout << " Con cuantos nodos desea trabajar? [   ] ";
	SetColor(9); gotoxy(34, 19); cout << "===========================================";
	SetColor(9); gotoxy(76, 18); cout << "|";
	SetColor(0); gotoxy(72, 18); cin >> nodos;

	system("cls");

	int b[10][10];

	int contador = 0;
	int opc, opcion2 = 0;
	do {

		system("cls");
		SetColor(9); gotoxy(25, 9); cout << "|";
		SetColor(9); gotoxy(25, 10); cout << "|";
		SetColor(9); gotoxy(25, 11); cout << "|";
		SetColor(9); gotoxy(25, 12); cout << "|";
		SetColor(9); gotoxy(25, 13); cout << "|";
		SetColor(9); gotoxy(25, 14); cout << "|";
		SetColor(9); gotoxy(25, 15); cout << "|";
		SetColor(9); gotoxy(25, 16); cout << "|";
		SetColor(9); gotoxy(25, 17); cout << "|";

		SetColor(9); gotoxy(26, 9);  cout << "================================";
		SetColor(2); gotoxy(26, 10); cout << "\t\tMenu";
		SetColor(9); gotoxy(26, 11); cout << "================================";

		SetColor(0); gotoxy(26, 12); cout << " 1. Ingresar valores de matriz.";
		SetColor(0); gotoxy(26, 13); cout << " 2. Mostrar Matriz de peso.";
		SetColor(0); gotoxy(26, 14); cout << " 3. Mostrar Matriz de estados.";
		SetColor(0); gotoxy(26, 15); cout << " 4. Salir.";
		SetColor(0); gotoxy(26, 16); cout << " Opcion: [   ]";
		SetColor(9); gotoxy(26, 17); cout << "================================";

		SetColor(9); gotoxy(58, 9);  cout << "|";
		SetColor(9); gotoxy(58, 10); cout << "|";
		SetColor(9); gotoxy(58, 11); cout << "|";
		SetColor(9); gotoxy(58, 12); cout << "|";
		SetColor(9); gotoxy(58, 13); cout << "|";
		SetColor(9); gotoxy(58, 14); cout << "|";
		SetColor(9); gotoxy(58, 15); cout << "|";
		SetColor(9); gotoxy(58, 16); cout << "|";
		SetColor(9); gotoxy(58, 17); cout << "|";

		SetColor(0); gotoxy(37, 16); cin >> opc;
		switch (opc) {
		case 1:
			system("cls");
			if (opcion2 == 1)
			{

				SetColor(9); gotoxy(2, 4); cout << "|";

				SetColor(9); gotoxy(2, 3); cout << "=======================";
				SetColor(0); gotoxy(3, 4); cout << " Datos ya ingresados.";
				SetColor(9); gotoxy(2, 5); cout << "=======================";

				SetColor(9); gotoxy(24, 4); cout << "|";
				_getch();

			}
			else {
				for (int i = 0; i < nodos; i++)
				{
					system("cls");
					SetColor(9); gotoxy(3, 3); cout << "|";
					SetColor(9); gotoxy(3, 4); cout << "|";
					SetColor(9); gotoxy(3, 5); cout << "|";
					SetColor(9); gotoxy(4, 3); cout << "==============================";
					SetColor(0); gotoxy(4, 4); cout << "Ingrese valores para  fila: " << (i + 1);
					SetColor(9); gotoxy(4, 5); cout << "==============================";
					opcion2 = 1;
					SetColor(9); gotoxy(34, 3); cout << "|";
					SetColor(9); gotoxy(34, 4); cout << "|";
					SetColor(9); gotoxy(34, 5); cout << "|";

					cout << endl;

					for (int j = 0; j < nodos; j++)
					{

						SetColor(9); gotoxy(4, 7); cout << "==============================";
						SetColor(9); gotoxy(4, 9); cout << "==============================";
						SetColor(0); gotoxy(7, 8); cin >> b[i][j];

						b2[j][i] = i + 1;
						b2[contador][contador] = 0;
					}
					contador++;
				}
			}
			opcion2 = 1;
			_getch();
			break;
		case 2:
			system("cls");
			floyds(b, b2);
			_getch();
			break;
		case 3:
			system("cls");
			int i, j;

			SetColor(9); gotoxy(2, 3); cout << "|";

			SetColor(9); gotoxy(2, 2); cout << "=============";
			SetColor(0); gotoxy(3, 3); cout << " Resultado:";
			SetColor(9); gotoxy(2, 4); cout << "=============";

			SetColor(9); gotoxy(14, 3); cout << "|";

			cout << endl << endl;

			for (i = 0; i < nodos; i++)
			{
				cout << endl;
				for (j = 0; j < nodos; j++)
				{
					cout << "\t";
					SetColor(9); cout << b2[i][j];
				}
			}
			_getch();
			_getch();
			break;
		case 4:
			break;
		}
	} while (opc != 4);

	_getch();
}


/*Fin floyd*/
//************************************************************************************************************************************

/*Hash*/
//************************************************************************************************************************************

struct Nodo {
	char unidad[50];
	Nodo *sig;
};

struct Clave {
	char nombre[50];
	Clave *sig;
	Nodo *cab;
	Nodo *pie;
}*cabeza, *fin;

void CrearClave(char clave[]) {
	Clave *nueva_clave = new Clave();
	strcpy_s(nueva_clave->nombre, clave);
	Clave *actual = new Clave();
	actual = cabeza;
	Clave *anterior = new Clave();

	if (cabeza == NULL) {
		//Si la tabla esta vacia
		cabeza = nueva_clave;
		nueva_clave->sig = NULL;
		fin = cabeza;
	}
	else {
		while (actual != NULL) {
			if (strcmp(clave, actual->nombre) < 0) {
				if (actual == cabeza) {
					//Si la clave es menor que el actual y es la cabeza
					nueva_clave->sig = cabeza;
					cabeza = nueva_clave;
					break;
				}
				else {
					//Si la clave es menor que el actual y no es la cabeza
					anterior->sig = nueva_clave;
					nueva_clave->sig = actual;
					break;
				}
			}
			else if (strcmp(clave, actual->nombre) > 0) {
				if (actual == fin) {
					//Si la clave es mayor que toda la lista, se inserta al final
					fin->sig = nueva_clave;
					nueva_clave->sig = NULL;
					fin = nueva_clave;
					break;
				}
				else {
					//Si la clave es menor al que se analizo, que siga recorriendo la lista
					anterior = actual;
					actual = actual->sig;
				}
			}
			else {
				cout << "No se puede ingresar nuevos" << endl;
				break;
			}
		}
	}
}

void MostrarDatos(Nodo *&encabezado) {
	Nodo *actual = new Nodo();
	actual = encabezado;
	if (actual != NULL) {
		while (actual != NULL) {
			cout << " -> " << actual->unidad << endl;
			actual = actual->sig;
		}
	}
	cout << endl;
}

void MostrarTabla() {
	Clave *actual = new Clave();
	actual = cabeza;

	if (actual != NULL) {
		while (actual != NULL) {
			cout << actual->nombre << endl;
			cout << endl;
			MostrarDatos(actual->cab);
			actual = actual->sig;
		}
	}
}

void RegistrarDatos(Nodo *&encabezado, Nodo *&pie, char unidad[]) {
	Nodo *nuevo_nodo = new Nodo();
	strcpy_s(nuevo_nodo->unidad, unidad);

	if (encabezado == NULL) {
		encabezado = nuevo_nodo;
		nuevo_nodo->sig = NULL;
		pie = encabezado;
	}
	else {
		pie->sig = nuevo_nodo;
		nuevo_nodo->sig = NULL;
		pie = nuevo_nodo;
	}
}

void BuscarClave(Clave *&encabezado, char clave[], char unidad[]) {
	Clave *buscador = new Clave();
	buscador = encabezado;

	if (buscador != NULL) {
		while (buscador != NULL) {
			if (strcmp(clave, buscador->nombre) == 0) {
				RegistrarDatos(buscador->cab, buscador->pie, unidad);
				break;
			}
			buscador = buscador->sig;
		}
	}
}

void MenuHash() {
	int opc = 0;
	int salida = 0;
	char curso[50];
	char unidades[50];

	while (opc != 4) {
		system("cls");
		cout << "Tabla de Hash" << endl;
		cout << "[1] Crear Cursos" << endl;
		cout << "[2] Agregar Unidades" << endl;
		cout << "[3] Mostrar" << endl;
		cout << "[4] Salir" << endl;
		cin >> opc; cin.ignore();

		switch (opc) {
		case 1:
			system("cls");
			cout << "-> Creacion de Cursos <- " << endl;
			cout << endl;
			cout << "Ingrese el nombre del curso " << endl;
			gets_s(curso);
			CrearClave(curso);
			strcpy_s(curso, "");
			system("pause>null");
			break;
		case 2:

			system("cls");
			cout << "-> Unidades <-" << endl;
			cout << endl;
			cout << "Ingrese el nombre del curso" << endl;
			gets_s(curso);

			while (salida != 1) {
				cout << "Ingrese la unidad" << endl;
				gets_s(unidades);

				BuscarClave(cabeza, curso, unidades);
				strcpy_s(unidades, "");

				cout << "Desea Ingresar otra unidad? [SI = 0 | NO = 1]" << endl;
				cin >> salida; cin.ignore();
				cout << endl;
			}
			strcpy_s(curso, "");
			salida = 0;
			system("pause>null");
			break;
		case 3:
			system("cls");
			cout << "-> Mostrar <-" << endl;
			cout << endl;
			MostrarTabla();
			system("pause>null");
			break;
		}
	}
}
/*Fin Hash*/
//************************************************************************************************************************************

/* Lista Doble*/
//************************************************************************************************************************************

struct nodold {
	int dato;
	nodold *siguiente;
	nodold *atras;
}*primero, *ultimo;

void insertarld() {
	nodold* nuevo = new nodold();
	cout << "inserte dato : ";
	//ingresamos el dato al nuevo nodo
	cin >> nuevo->dato;

	if (primero == NULL) { //si la lista no ha sido creada o se encuentra vacia					
		primero = nuevo; //por lo tanto el nuevo->dato sera el primer nodo de la lista
		primero->siguiente = NULL;
		//mientras sea el primero ambos lados apuntaran a NULL	
		primero->atras = NULL;
		//NULL<-[nuevo->dato]->NULL
		ultimo = primero; //se igualan porque mientras solo exista ese nodo entonces sera el primero y el ultimo xd
	}
	else {
		ultimo->siguiente = nuevo; //apuntara al nuevo nodo
		nuevo->siguiente = NULL;
		nuevo->atras = ultimo;
		ultimo = nuevo;
	}
	cout << "dato ingresado\n\n";
}

void mostrarPU() {
	nodold* actual = new nodold();
	actual = primero;//actual se inicializa en el primero
	if (primero != NULL) { //la lista existe
		while (actual != NULL) {
			cout << "\n" << actual->dato; //imprime el valor del dato actual
			actual = actual->siguiente; //se actualiza el apuntador , actual pasara a ser el siguiente dato

		}
	}
	else {
		cout << "la lista se encuentra vacia\n";
	}
	cout << "\n\n";
	system("pause");
}

void mostrarUP() {
	nodold* actual = new nodold();
	actual = ultimo; //empezara con el ultimo
	if (primero != NULL) {
		while (actual != NULL)
		{
			cout << "\n" << actual->dato; //imprime el valor del dato actual
			actual = actual->atras;// actual pasara a ser el anterior
		}
	}
	else {
		cout << "la lista se encuentra vacia\n";
	}
	cout << "\n\n";
	system("pause");
}

void buscarld() {
	nodold *actual = new nodold();
	actual = primero;
	bool encontrado = false;
	int buscado = 0;
	cout << "ingrese dato a buscar: ";
	cin >> buscado;
	if (primero != NULL) {
		while (actual != NULL && encontrado != true) {
			if (actual->dato == buscado) {
				cout << "\nel dato (" << buscado << ") ha sido encontrado \n\n";
				encontrado = true;
			}

			actual = actual->siguiente;
		}

		if (!encontrado) {
			cout << "\ndato no encontrado \n\n";
		}
	}
	else {
		cout << "la lista se encuentra vacia";
	}
	system("pause");
}

void eliminarld() {
	nodold *actual = new nodold();
	actual = primero;
	nodold *anterior = new nodold();
	anterior = NULL;
	bool encontrado = false;
	int buscado = 0;
	cout << "ingrese dato a eliminar: ";
	cin >> buscado;
	if (primero != NULL) {
		while (actual != NULL && encontrado != true) {
			if (actual->dato == buscado) {
				cout << "el dato (" << buscado << ") ha sido encontrado \n\n";
				if (actual == primero) {
					primero = primero->siguiente;
					primero->atras = NULL;

				}
				else if (actual == ultimo) {
					anterior->siguiente = NULL;
					ultimo = anterior;

				}
				else {
					anterior->siguiente = actual->siguiente;
					actual->siguiente->atras = anterior;
				}
				cout << "\ndato eliminado\n\n";
				encontrado = true;
			}
			anterior = actual;
			actual = actual->siguiente;
		}

		if (!encontrado) {
			cout << "\ndato no encontrado \n\n";
		}
	}
	else {
		cout << "la lista se encuentra vacia";
	}
	system("pause");
}

void MenuListaDoble() {

int opcion;

	do {
		system("cls");

	cout << "\tMenu\n\n";
	cout << "1.Insertar \n";
	cout << "2.Mostrar (Primero al Ultimo)\n";
	cout << "3.Mostrar (Ultimo al Primero)\n";
	cout << "4.Buscar\n";
	cout << "5.Eliminar\n";
	cout << "6.Salir\n";
	cout << "\nIngrese opcion: ";
	cin >> opcion;
	
		switch (opcion)
		{
			system("cls");
		case 1:
			system("cls");

			insertarld();
			system("pause");
			break;
		case 2:
			mostrarPU();
			break;
		case 3:
			mostrarUP();
			break;
		case 4:
			buscarld();
			break;
		case 5:
			eliminarld();
			break;
		default: "no es una opcion valida";
			break;
		}
	} while (opcion != 6);
	system("pause");

}

/*Fin Lista Doble*/
//************************************************************************************************************************************


/* Cola Dinamica*/
//************************************************************************************************************************************

struct NodoCola {
	string archivo;
	string usuario;
	int hojas;
	struct NodoCola *sgte;
};

struct Cola {
	NodoCola *delante;
	NodoCola *atras;
};

//encolar elemento
void encolar(struct Cola &q, string file, string user, int hja) {
	struct NodoCola *aux = new (struct NodoCola);
	aux->archivo = file;
	aux->usuario = user;
	aux->hojas = hja;
	aux->sgte = NULL;

	if (q.delante == NULL)
		q.delante = aux; //encola el primer elemento
	else
		(q.atras)->sgte = aux;
	q.atras = aux; //puntero que siempre apunta al ultimo elemento
}

//desencolar elemento
void desencolar(struct Cola &q) {
	string f, u;
	int h;
	struct NodoCola *aux;

	aux = q.delante; //aux apunta al inicio de la cola 
	f = aux->archivo;
	u = aux->usuario;
	h = aux->hojas;
	q.delante = (q.delante)->sgte;
	delete (aux); //libera memoria a donte apunta aux

}

//mostrar cola
void muestraCola(struct Cola q) {
	struct NodoCola *aux;
	aux = q.delante;

	while (aux != NULL) {
		cout << "  " << &aux->archivo << " - " << "Nombre Archivo: " << aux->archivo << endl;
		cout << "  " << &aux->usuario << " - " << "Usuario: " << aux->usuario << endl;
		cout << "  " << &aux->hojas << " - " << "No. Hojas: " << aux->hojas << endl << endl;
		aux = aux->sgte;
	}
}

//eliminar todos los elementos de la cola 
void vaciaCola(struct Cola &q) {
	struct NodoCola *aux;
	while (q.delante != NULL) {
		aux = q.delante;
		q.delante = aux->sgte;
		delete (aux);
	}
	q.delante = NULL;
	q.atras = NULL;
}




//funcion principal
void MenuCola() {
	struct Cola q;

	q.delante = NULL;
	q.atras = NULL;

	string archivo, usuario;
	int hojas;
	int op; //opcion del menu

	system("color 0b");

	do {
		cout << "\n\t Implementacion de colas en c++\n\n";
		cout << "1.	Encolar									" << endl;
		cout << "2.	Desencolar								" << endl;
		cout << "3.	Mostrar Cola							" << endl;
		cout << "4.	Vaciar Cola								" << endl;
		cout << "5.	Salir									" << endl;

		cout << "\nIngrese opcion: ";
		 cin >> op;
		switch (op)
		{
		case 1:
			cout << "\n Nombre del archivo: "; cin >> archivo;
			cout << " USUARIO: "; cin >> usuario;
			cout << " NO. HOJAS: "; cin >> hojas;
			encolar(q, archivo, usuario, hojas);
			cout << "\n\n\tARCHIVO  " << archivo << " encolado..\n\n";
			break;

		case 2:
			desencolar(q);
			cout << "\n\n\t\t Archivo desencolado...\n\n";
			break;

		case 3:
			cout << "\n\n Mostrando Cola\n\n";
			if (q.delante != NULL) muestraCola(q);
			else cout << "\n\n\tCola Vacia...!" << endl;
			break;

		case 4:
			vaciaCola(q);
			cout << "\n\n\t\tHecho...\n\n";
			break;

		}
		cout << endl << endl;
		system("pause"); system("cls");

	} while (op != 5);
}

/* Fin Cola Dinamica*/
//************************************************************************************************************************************

/* arbol avl*/
//************************************************************************************************************************************

typedef struct node
{
	int elemento;
	node *derecha;
	node *izquierda;
	int altura;
}*nodeptr;

//Encontrara el numero menor
nodeptr encontrarmin(nodeptr p)
{
	if (p == NULL)
	{
		return p;
	}
	else
	{
		while (p->izquierda != NULL)
			p = p->izquierda;
		return p;
	}
}

//Encontrara el numero mayor
nodeptr encontrarmax(nodeptr p)
{
	if (p == NULL)
	{
		return p;
	}
	else
	{
		while (p->derecha != NULL)
			p = p->derecha;
		return p;
	}
}

//Encontrar un numero en el arbol avl
void encontrar(int x, nodeptr &p)
{
	if (p == NULL) {
		SetColor(11); gotoxy(6, 7); cout << "-------------------------";
		SetColor(7); gotoxy(6, 8); cout << " Elemento no encontrado ";
		SetColor(11); gotoxy(6, 9); cout << "-------------------------";
	}

	else {
		if (x < p->elemento)
			encontrar(x, p->izquierda);
		else
			if (x>p->elemento)
				encontrar(x, p->derecha);
			else {
				SetColor(11); gotoxy(6, 7); cout << "----------------------";
				SetColor(7); gotoxy(6, 8); cout << " Elemento Encontrado ";
				SetColor(11); gotoxy(6, 9); cout << "----------------------";
			}
	}

}

int eliminarmin(nodeptr &p)
{
	int c;
	if (p->izquierda == NULL)
	{
		c = p->elemento;
		p = p->derecha;
		return c;
	}
	else
	{
		c = eliminarmin(p->izquierda);
		return c;
	}
}

//Vaciar el arbol
void vaciar(nodeptr &p)
{
	nodeptr d;
	if (p != NULL)
	{
		vaciar(p->izquierda);
		vaciar(p->derecha);
		d = p;
		free(d);
		p = NULL;
	}
}

//Eliminar un nodo
void del(int x, nodeptr &p)
{
	nodeptr d;
	if (p == NULL) {

		system("cls");
		SetColor(11); gotoxy(6, 2); cout << "---------------------------";
		SetColor(7); gotoxy(6, 3); cout << " Elemento no encontrado! ";
		SetColor(11); gotoxy(6, 4); cout << "---------------------------";

	}
	else if (x < p->elemento)
		del(x, p->izquierda);
	else if (x > p->elemento)
		del(x, p->derecha);
	else if ((p->izquierda == NULL) && (p->derecha == NULL))
	{
		d = p;
		free(d);
		p = NULL;
		system("cls");

		SetColor(11); gotoxy(6, 2); cout << "---------------------------";
		SetColor(7); gotoxy(6, 3); cout << " Elemento Eliminado en AVL ";
		SetColor(11); gotoxy(6, 4); cout << "---------------------------";

	}
	else if (p->izquierda == NULL)
	{
		d = p;
		free(d);
		p = p->derecha;
		system("cls");
		SetColor(11); gotoxy(6, 2); cout << "---------------------------";
		SetColor(7); gotoxy(6, 3); cout << " Elemento Eliminado en AVL ";
		SetColor(11); gotoxy(6, 4); cout << "---------------------------";

	}
	else if (p->derecha == NULL)
	{
		d = p;
		p = p->izquierda;
		free(d);
		system("cls");
		SetColor(11); gotoxy(6, 2); cout << "---------------------------";
		SetColor(7); gotoxy(6, 3); cout << " Elemento Eliminado en AVL ";
		SetColor(11); gotoxy(6, 4); cout << "---------------------------";

	}
	else
		p->elemento = eliminarmin(p->derecha);
}

//Mostrar en Preorden 
void preorder(nodeptr p)
{
	if (p != NULL)
	{
		cout << p->elemento << "->";
		preorder(p->izquierda);
		preorder(p->derecha);
	}

}

//		Mostrar en Inorder 
void inorder(nodeptr p)
{
	if (p != NULL)
	{
		inorder(p->izquierda);
		cout << p->elemento << "->";
		inorder(p->derecha);
	}
}

//		Mostrar en PostOrder 
void postorder(nodeptr p)
{
	if (p != NULL)
	{
		postorder(p->izquierda);
		postorder(p->derecha);
		cout << p->elemento << "->";
	}
}

//		Funcion que trabaja la altura
int bsaltura(nodeptr p)
{
	int t;
	if (p == NULL)
		return -1;
	else
	{
		t = p->altura;
		return t;
	}
}

//Sumar nodos
int s = 0;
void sumaAVL(nodeptr p, int x)
{
	if (p == NULL) //Si esta vacio regresa al menu
		return;
	sumaAVL(p->izquierda, x + 1);
	s += p->elemento; //suma de los nodos
	sumaAVL(p->derecha, x + 1);
}


int HojasAVL(nodeptr p)
{
	if (p == NULL) {
		return 0;
	}
	if ((p->derecha == NULL) && (p->izquierda == NULL)) {
		return 1;
	}
	else {
		return HojasAVL(p->izquierda) + HojasAVL(p->derecha);
	}
}

//		R O T A C I O N E S
nodeptr srl(nodeptr &p1)
{
	nodeptr p2;
	p2 = p1->izquierda;
	p1->izquierda = p2->derecha;
	p2->derecha = p1;
	p1->altura = max(bsaltura(p1->izquierda), bsaltura(p1->derecha)) + 1;
	p2->altura = max(bsaltura(p2->izquierda), p1->altura) + 1;
	return p2;
}

nodeptr srr(nodeptr &p1)
{
	nodeptr p2;
	p2 = p1->derecha;
	p1->derecha = p2->izquierda;
	p2->izquierda = p1;
	p1->altura = max(bsaltura(p1->izquierda), bsaltura(p1->derecha)) + 1;
	p2->altura = max(p1->altura, bsaltura(p2->derecha)) + 1;
	return p2;
}

nodeptr drl(nodeptr &p1)
{
	p1->izquierda = srr(p1->izquierda);
	return srl(p1);
}

nodeptr drr(nodeptr &p1)
{
	p1->derecha = srl(p1->derecha);
	return srr(p1);
}

//Funcion que cuenta el numero de nodos que tiene el arbol
int c = 0;
void nonodes(nodeptr p, int q)
{
	if (p == NULL)//Si el arbol esta vacio, regresa al menu
		return;
	nonodes(p->derecha, q + 1); //Recorre el sub arbol derecho
	c++; //Incrementa la variable segun va recorriendo
	nonodes(p->izquierda, q + 1);//Recorre el sub arbol izquierdo

}

//Funcion que insertar nodos en el AVL
void insert(int x, nodeptr &p)
{
	if (p == NULL)
	{
		p = new node;
		p->elemento = x;
		p->izquierda = NULL;
		p->derecha = NULL;
		p->altura = 0;
		if (p == NULL) {
			//cout << "arbol vacio";
		}
	}
	else
	{
		if (x<p->elemento)
		{
			insert(x, p->izquierda);
			if ((bsaltura(p->izquierda) - bsaltura(p->derecha)) == 2)
			{
				if (x < p->izquierda->elemento)
					p = srl(p);
				else
					p = drl(p);
			}
		}
		else if (x>p->elemento)
		{
			insert(x, p->derecha);
			if ((bsaltura(p->derecha) - bsaltura(p->izquierda)) == 2)
			{
				if (x > p->derecha->elemento)
					p = srr(p);
				else
					p = drr(p);
			}
		}
		else {
			//	cout << "Ya existe el elementoo ";
		}

	}
	int m, n, d;
	m = bsaltura(p->izquierda);
	n = bsaltura(p->derecha);
	d = max(m, n);
	p->altura = d + 1;

}

//Funcion que muestra los datos en consola
void imprimir(nodeptr &p, int Y)
{
	if (p == NULL) {
		return;
	}

	X += 5;

	imprimir(p->izquierda, Y + 2);

	if (p->izquierda != NULL) {
		gotoxy(2 + X - Y, 9 + Y); SetColor(15); cout << "/";
		gotoxy(3 + X - Y, 8 + Y); SetColor(15); cout << "("; SetColor(10); cout << p->elemento; SetColor(15); cout << ")";
	}
	if (p->izquierda == NULL && p->derecha == NULL) {
		gotoxy(3 + X - Y, 8 + Y); SetColor(15); cout << "("; SetColor(10); cout << p->elemento; SetColor(15); cout << ")";
	}
	if (p->derecha != NULL) {
		gotoxy(6 + X - Y, 9 + Y); SetColor(15);  printf("%c\n", 92);
		gotoxy(3 + X - Y, 8 + Y); SetColor(15); cout << "("; SetColor(10); cout << p->elemento; SetColor(15); cout << ")";
	}

	imprimir(p->derecha, Y + 2);

}

void debeCrear() {

	SetColor(11); gotoxy(5, 2); cout << "---------------------";
	SetColor(7); gotoxy(6, 3); cout << " Debe crear arbol. ";
	SetColor(11); gotoxy(5, 4); cout << "---------------------";

}

int hojas = 0;
void MenuAVL()
{
	system("cls");
	nodeptr root = NULL, min, max;
	int choice, x;
	char ch = 's';

	system("color 00");

	do
	{
		system("cls");

		for (int i = 0; i < 17; i++) {
			SetColor(11); gotoxy(60, 11 + i); cout << "|";
			SetColor(11); gotoxy(90, 11 + i); cout << "|";
		}
		for (int i = 0; i < 31; i++) {
			SetColor(11); gotoxy(60 + i, 10); cout << "-";
			SetColor(11); gotoxy(60 + i, 12); cout << "-";
			SetColor(11); gotoxy(60 + i, 25); cout << "-";
			SetColor(11); gotoxy(60 + i, 27); cout << "-";
		}

		SetColor(7); gotoxy(62, 11); cout << "\t\tA V L";
		SetColor(7); gotoxy(62, 13); cout << "	1.  Insertar.";
		SetColor(7); gotoxy(62, 14); cout << "	2.  Buscar Minimo.";
		SetColor(7); gotoxy(62, 15); cout << "	3.  Buscar Maximo.";
		SetColor(7); gotoxy(62, 16); cout << "	4.  Buscar.";
		SetColor(7); gotoxy(62, 17); cout << "	5.  Eliminar.";
		SetColor(7); gotoxy(62, 18); cout << "	6.  Altura.";
		SetColor(7); gotoxy(62, 19); cout << "	7.  Contar Hojas.";
		SetColor(7); gotoxy(62, 20); cout << "	8.  Contar Nodos.";
		SetColor(7); gotoxy(62, 21); cout << "	9.  Sumar Nodos.";
		SetColor(7); gotoxy(62, 22); cout << "	10. Recorridos.";
		SetColor(7); gotoxy(62, 23); cout << "	11. Mostrar Arbol.";
		SetColor(7); gotoxy(62, 24); cout << "	12. Salir.";
		SetColor(7); gotoxy(62, 26); cout << "	Ingrese Opcion [    ]";
		SetColor(7); gotoxy(81, 26); cin >> choice;

		switch (choice)
		{
		case 1:
			system("cls");
			cout << "Ingrese valor de nuevo nodo: ";
			cin >> x;
			insert(x, root);
			system("pause");
			break;
		case 2:
			system("cls");

			if (root != NULL)
			{
				min = encontrarmin(root);
				cout << "Elemento menor: " << min->elemento;
			}
			system("pause");
			break;
		case 3:
			system("cls");

			if (root != NULL)
			{
				max = encontrarmax(root);
				cout << "Elemento mayor: " << max->elemento;
				
			}
			system("pause");
			break;
		case 4:
			system("cls");

			cout << "Nodo a buscar:	";
			cin >> x;
			if (root != NULL)
				encontrar (x, root);
			break;
		case 5:
			system("cls");
			cout << " Que elemento desea eliminar? ";
			cin >> x;
			del(x, root);
			system("pause");
			break;
		case 6:
			system("cls");
			if (arbol == NULL) {
				debeCrear();

			}
			system("cls");
			if (arbol == NULL) {
				debeCrear();

			}
			else
			{
				SetColor(11); gotoxy(6, 2); cout << "-----------------------------";
				SetColor(7); gotoxy(6, 3); cout << " Altura y Profundidad: " << bsaltura(root);
				SetColor(11); gotoxy(6, 4); cout << "-----------------------------";
			}
			SetColor(0); gotoxy(20, 20); system("pause");
			break;

		case 7:
			system("cls");

			if (root == NULL) {
				debeCrear();
			}
			else {

				hojas = HojasAVL(root);
				SetColor(11); gotoxy(6, 2); cout << "-----------------------------";
				SetColor(7); gotoxy(7, 3); cout << " El numero de hojas es: ";
				SetColor(7); gotoxy(32, 3); cout << HojasAVL(root);
				SetColor(11); gotoxy(6, 4); cout << "-----------------------------";

			}
			SetColor(0); gotoxy(20, 20); system("pause");
			break;

		case 8:
			system("cls");
			if (root == NULL) {
				debeCrear();
			}
			else
			{
				c = 0;
				nonodes(root, 0);
				SetColor(11); gotoxy(6, 6); cout << "-----------------------------";
				SetColor(7); gotoxy(6, 7); cout << " Numero de nodos: " << c;
				SetColor(11); gotoxy(6, 8); cout << "-----------------------------";
			}
			SetColor(0); gotoxy(20, 20); system("pause");
			break;

		case 9:	
			system("cls");

			s = 0;

			if (root == NULL) {
				debeCrear();
			}
			else
			{
				sumaAVL(root, s);

				SetColor(11); gotoxy(6, 2); cout << "------------------------";
				SetColor(7); gotoxy(7, 3); cout << " La suma es: " << s;
				SetColor(11); gotoxy(6, 4); cout << "------------------------";

			}
			SetColor(0); gotoxy(20, 20); system("pause");
			break;
		case 10:
			system("cls");
			if (root == NULL) {
				debeCrear();
			}
			else {


				for (int i = 0; i < 80; i++) {
					SetColor(11); gotoxy(5 + i, 3); cout << "-";
					SetColor(11); gotoxy(5 + i, 5); cout << "-";
					SetColor(11); gotoxy(5 + i, 7); cout << "-";
					SetColor(11); gotoxy(5 + i, 9); cout << "-";
				}

				SetColor(7); gotoxy(6, 4); cout << " Inorden: ";
				SetColor(7); gotoxy(20, 4); inorder(root);

				SetColor(7); gotoxy(6, 6); cout << " Preorden: ";
				SetColor(7); gotoxy(20, 6); preorder(root);

				SetColor(7); gotoxy(6, 8); cout << " Postorden: ";
				SetColor(7); gotoxy(20, 8); postorder(root);


			}
			SetColor(0); gotoxy(20, 20); system("pause");
			break;
		case 11:
			system("cls");
			X = 0;
			cout << "Mostrando..." << endl;
			imprimir(root, 0);
			SetColor(0); gotoxy(20, 20); system("pause");
			break;

		}

			} while (choice != 12);
	}
/* Fin arbol avl*/
//************************************************************************************************************************************


void menuPrincipal()
{
	
	int ans;

	do {
		system("cls");
		for (int i = 0; i < 26; i++) {
			SetColor(9); gotoxy(66, 10 + i); cout << "|";
			SetColor(9); gotoxy(94, 10 + i); cout << "|";
		}
		for (int i = 0; i < 29; i++) {
			SetColor(9); gotoxy(66 + i, 10); cout << "=";
			SetColor(9); gotoxy(66 + i, 12); cout << "=";
			SetColor(9); gotoxy(66 + i, 14); cout << "=";
			SetColor(9); gotoxy(66 + i, 16); cout << "=";
			SetColor(9); gotoxy(66 + i, 18); cout << "=";
			SetColor(9); gotoxy(66 + i, 20); cout << "=";
			SetColor(9); gotoxy(66 + i, 22); cout << "=";
			SetColor(9); gotoxy(66 + i, 24); cout << "=";
			SetColor(9); gotoxy(66 + i, 26); cout << "=";
			SetColor(9); gotoxy(66 + i, 28); cout << "=";
			SetColor(9); gotoxy(66 + i, 30); cout << "=";
			SetColor(9); gotoxy(66 + i, 32); cout << "=";
			SetColor(9); gotoxy(66 + i, 34); cout << "=";
			SetColor(9); gotoxy(66 + i, 36); cout << "=";

		}

		SetColor(0); gotoxy(68, 11); cout << "	UNION DE PROGRAMAS";
		SetColor(0); gotoxy(68, 13); cout << "\t\tMenu";
		SetColor(0); gotoxy(68, 15); cout << "1. Pila Dinamica."; //Luisa
		SetColor(0); gotoxy(68, 17); cout << "2. Cola Dinamica."; //Luisa
		SetColor(0); gotoxy(68, 19); cout << "3. Lista Doble Enlazada."; //Luisa 
		SetColor(0); gotoxy(68, 21); cout << "4. Floyd. "; 
		SetColor(0); gotoxy(68, 23); cout << "5. Tabla Hash."; //Luisa
		SetColor(0); gotoxy(68, 25); cout << "6. Arbol Binario (ABB).";
		SetColor(0); gotoxy(68, 27); cout << "7. Arbol Balanceado (AVL)."; //Luisa
		SetColor(0); gotoxy(68, 29); cout << "8.";
		SetColor(0); gotoxy(68, 31); cout << "9.";
		SetColor(0); gotoxy(68, 33); cout << "10.";
		SetColor(0); gotoxy(68, 35); cout << "Ingrese opcion [   ]";
		SetColor(0); gotoxy(85, 35); cin >> ans;

		switch (ans)
		{
		case 1:
			system("cls");
			MenuPilaDinamica();
			system("pause");
			break;

		case 2:
			system("cls");
			MenuCola();
			system("pause");
			break;

		case 3:
			system("cls");
			MenuListaDoble();
			system("pause");
			break;
		case 4:
			system("cls");
			menuFloyd();
			system("pause");
			break;
		case 5:
			system("cls");
			MenuHash();
			system("pause");
			break;
		case 6:
			system("cls");
			menuArbol();
			system("pause");
			break;
		case 7:
			system("cls");
			MenuAVL();
			system("pause");
			break;
		default:
			break;
		}

	} while (ans != 11);

	SetColor(0); gotoxy(25, 45); system("pause");
}

int main() {

	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	system("color F5"); //color de consola

	system("cls");
	menuPrincipal();
	system("pause");
	return 0;
}
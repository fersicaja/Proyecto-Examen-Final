// Proyecto union.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <stdio.h>
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

struct nodo {
	int nro;
	struct nodo *izq, *der;
};

typedef struct nodo *ABB;
/* es un puntero de tipo nodo que hemos llamado ABB, que ulitizaremos
para mayor facilidad de creacion de variables */

ABB crearNodo(int x)
{
	ABB nuevoNodo = new(struct nodo);
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



void verArbol(ABB arbol, int n)
{

	if (arbol == NULL)
		return;
	verArbol(arbol->der, n + 1);

	for (int i = 0; i<n; i++)
		cout << "   ";

	cout << arbol->nro << endl;

	verArbol(arbol->izq, n + 1);

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
	int opc,opcion2=0;
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
void menuPrincipal()
{
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	system("color F5"); //color de consola
	int ans;

	do {
		system("cls");
		for (int i = 0; i < 28; i++) {
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
			SetColor(9); gotoxy(66 + i, 38); cout << "=";

		}

		SetColor(0); gotoxy(68, 11); cout << "	UNION DE PROGRAMAS";
		SetColor(0); gotoxy(68, 13); cout << "Menu";
		SetColor(0); gotoxy(68, 15); cout << "1. Pila Dinamica.";
		SetColor(0); gotoxy(68, 17); cout << "2. Arbol binario.";
		SetColor(0); gotoxy(68, 19); cout << "3. Floyd.";
		SetColor(0); gotoxy(68, 21); cout << "4.";
		SetColor(0); gotoxy(68, 23); cout << "5.";
		SetColor(0); gotoxy(68, 25); cout << "6.";
		SetColor(0); gotoxy(68, 27); cout << "7.";
		SetColor(0); gotoxy(68, 29); cout << "8.";
		SetColor(0); gotoxy(68, 31); cout << "9.";
		SetColor(0); gotoxy(68, 33); cout << "10.";
		SetColor(0); gotoxy(68, 35); cout << "11.";
		SetColor(0); gotoxy(68, 37); cout << "Ingrese opcion [   ]";
		SetColor(0); gotoxy(85, 37); cin >> ans;

		switch (ans)
		{
		case 1: 
			system("cls");
			MenuPilaDinamica();
			system("pause");
			break;
		
		case 2:
			system("cls");
			menuArbol();
			system("pause");
			break;
		case 3:
			system("cls");
			menuFloyd();
			system("pause");
			break;
		
		default:
			break;
		}

	} while (ans != 11);




	SetColor(0); gotoxy(25, 45); system("pause");
}

int main() {
	system("cls");
	menuPrincipal();
	system("pause");
	return 0;
}
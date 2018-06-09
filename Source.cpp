#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <Windows.h>

using namespace std;

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





void main()
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
		SetColor(0); gotoxy(68, 17); cout << "2.";
		SetColor(0); gotoxy(68, 19); cout << "3.";
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
		case 1: {
			system("cls");
			MenuPilaDinamica();
			system("pause");
		}
		default:
			break;
		}

	} while (ans != 11);




	SetColor(0); gotoxy(25, 45); system("pause");
}


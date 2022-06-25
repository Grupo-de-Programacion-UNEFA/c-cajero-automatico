/*
   ------------------------
   Archivo Principal MAIN
   ------------------------
*/
// Llama las librerias de cabecero, funciones y variables externas
#include "modulos/funciones.h"

// Declara y define las variables externas aqui para ser usadas en otros archivos
string userActiveName = "", userActivePasswd = "";
float userActiveFounds = 0.0;

/* --------------------- Funcion Main ---------------------- */
int main(){

	int select; string opciones;

	opciones += "1) Iniciar sesion.\n";
	opciones += "2) Crear cuenta.\n";
	opciones += "3) Salir.\n";
	
	while (true) { //Menu de inicio.
		
		cout << "\t\tBienvenido al Banco Petare";
		cout << endl << endl;
		
		cout << opciones;
		cin >> select;
		
		switch (select) {
			case 1: login(); break;
			case 2: crear(); break;
			case 3: return 0;
			
			default: cout << "Numero de opcion invalido, ingrese un numero valido" << endl;
			break;
		}
	}

	return 0;
}

/*
   ------------------------
   Archivo Principal MAIN
   ------------------------
*/
// Llama las librerías de cabecero, funciones y variables externas
#include "funciones.h"

// Declara y define las variables externas aquí para ser usadas en otros archivos
string userActiveName = "MasterSex", userActivePasswd = "2684";
float userActiveFounds = 10.5;

/* --------------------- Funcion Main ---------------------- */
int main () {
	menu_user_logged();
	
	int select; string opciones;
	
	opciones += "1) Iniciar sesion.\n";
	opciones += "2) Crear cuenta.\n";
	opciones += "3) Salir.\n";
	
	while (true) {//Menu de inicio.
		
		cout << "\t\t";
		mostrar_frase_lentamente(30, "Bienvenido al Banco Petare");
		cout << endl << endl;
		
		mostrar_frase_lentamente(30, opciones);
		cin >> select;
		
		switch(select){
			
			case 1: login(); break;
			case 2: crear(); break;
			case 3: return 0;
			
			default:
			cout << "Chingada madre, escribe las opciones que te doy, puto animal." << endl;
			break;
		}
	}
	
	return 0;
}
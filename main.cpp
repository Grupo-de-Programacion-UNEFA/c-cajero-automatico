/*
   ------------------------
   Archivo Principal MAIN
   ------------------------
*/
// Llama las librerías de cabecero, funciones y variables externas
#include "modulos/funciones.h"

// Declara y define las variables externas aquí para ser usadas en otros archivos
string userActiveName = "", userActivePasswd = "";
float userActiveFounds = 0.0;

/* --------------------- Funcion Main ---------------------- */
int main(){

	int select; string opciones;

	opciones += "1) Iniciar sesion.\n";
	opciones += "2) Crear cuenta.\n";
	opciones += "3) Salir.\n";
	//system("C:\\Users\\NarkoOppa\\OneDrive\\Documentos\\Atom\\cpp\\cajero\\registro.txt");

	while(true){//Menu de inicio.

		cout<<"\t\tBienvenido al Banco Petare";
		cout<<endl<<endl;

		cout<<opciones;
		cin>>select;

		switch(select){

			case 1: login(); break;
			case 2: crear(); break;
			case 3: return 0;

			default:
			cout<<"Chingada madre, escribe las opciones que te doy, puto animal."<<endl;
			break;
		}
	}

	return 0;
}

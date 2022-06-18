/*
   ------------------------------------
   Definicion de funciones de Impresion
   ------------------------------------
*/

#include "funciones.h"
void spam_de_puntos (LongStr cantidad, Speed intervalo) {
	for (int i = 0; i < cantidad; i++) {
		cout << ".";
		this_thread::sleep_for(chrono::milliseconds(intervalo));
	}
}

void mostrar_frase_lentamente (string frase, Speed intervalo) {
	for (int i = 0; i < frase.size(); i++) {
		cout << frase[i];
		this_thread::sleep_for(chrono::milliseconds(intervalo));
	}
}

int menu_user_logged () {
	
	string frase; int select;
	
	frase += "1) Depositar dinero.\n";
	frase += "2) Sacar dinero.\n";
	frase += "3) Transferir dinero.\n";
	frase += "4) Actualizar datos.\n";
	frase += "5) Borrar cuenta.\n";
	frase += "6) Cerrar sesion.\n";
	
	while (true) {
		spam_de_puntos(longStr);
		cout << endl << "Usuario: " << userActiveName << endl << "Clave: " << userActivePasswd << endl;
		cout << "Fondos: " << userActiveFounds << endl;
		
		spam_de_puntos(longStr);
		cout << endl;
		mostrar_frase_lentamente(frase);
		cin >> select;
		
		switch (select) {
			case 1: mete_saca(true); break;	 //Depositar dinero.
			case 2: mete_saca(false); break; //Sacar dinero.
			case 3: break; 					 //Transferir dinero a otra cuenta.
			case 4: break; 					 //Cambiar datos.
			case 5: break;					 //Borrar cuenta.
			case 6: 
				userActiveName = "";
				userActivePasswd = "";
				return 0;		
			default:
				cout << "Opcion invalida, subnormal." << endl;
		}
	}
}
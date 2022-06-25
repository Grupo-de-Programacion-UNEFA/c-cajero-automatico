/*
   ------------------------------------
   Definicion de funciones de Impresion
   ------------------------------------
*/

#include "funciones.h"
int menu_user_logged () {

	string frase; int select;

	if(userActiveName == "" && userActivePasswd == "") return 0;

	frase += "1) Depositar dinero.\n";
	frase += "2) Sacar dinero.\n";
	frase += "3) Transferir dinero.\n";
	frase += "4) Actualizar datos.\n";
	frase += "5) Borrar cuenta.\n";
	frase += "6) Cerrar sesion.\n";
	
	while (true) {
		if (userActiveName == "") return 0;
		cout << "....................";
		cout << endl << "Usuario: " << userActiveName << endl << "Clave: " << userActivePasswd << endl;
		cout << "Fondos: " << userActiveFounds << endl;
		cout << "....................";
		cout << endl;
		cout << frase;
		cin >> select;
		
		switch (select) {
			case 1: db::depositarORetirar(true); break;	//Depositar dinero.
			case 2: db::depositarORetirar(false); break; //Sacar dinero.
			case 3: cout << endl << ((db::transferir()) ? "Transferencia Exitosa." : "Transferencia Cancelada.") << endl; break; //Transferir dinero a otra cuenta.
			case 4: cout << endl << ((db::actualizar()) ? "Cuenta Actualizada Exitosamente." : "Operacion Cancelada.") << endl; break; // Cambiar datos.
			case 5: cout << endl << ((db::borrar()) ? "Cuenta Borrada Exitosamente." : "Operacion Cancelada.") << endl; break; // Borrar cuenta.
			case 6: 
				userActiveName = "";
				userActivePasswd = "";
				return 0;		
			default:
				cout << "Opcion invalida." << endl;
		}
	}
	return 0;
}

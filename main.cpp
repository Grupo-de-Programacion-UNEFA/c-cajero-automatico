/*
   ------------------------
   Archivo Principal MAIN
   ------------------------
*/
// Llama las librerias de cabecero, funciones y variables externas
#include "modulos/funciones.h"

// Declara y define las variables externas aqui para ser usadas en otros archivos
float userActiveFounds = 0.0;
string userActiveName = "", userActivePasswd = "";
// Variables Constantes
const float MIN_MONTO_TRANSFERENCIA = 0.01, MIN_MONTO_DEPOSITO = 10.00, MIN_MONTO_RETIRO = 5.00;
const float MAX_MONTO_TRANSFERENCIA = 1000000.00, MAX_MONTO_DEPOSITO = 1000.00, MAX_MONTO_RETIRO = 500.00;

/* --------------------- Funcion Main ---------------------- */
int main () {

	int select;
	string frase;
	
	while (true) { //Menu de inicio.
	frase = "";
		if (userActiveName == "" && userActivePasswd == "") {
			frase += "1) Iniciar sesion.\n";
			frase += "2) Crear cuenta.\n";
			frase += "3) Salir.\n";
			frase += "> ";
			
				cout << "\t\tBienvenido al Banco Petare";
				cout << endl << endl;
				
				select = util::inputNumber(frase);
				
				switch (select) {
					case 1: sesion::login(); continue;
					case 2: sesion::crear(); break;
					case 3: return 0;			
					default: cout << "Numero de opcion invalido, ingrese un numero valido" << endl;
				}
		} else {
			frase += "1) Depositar dinero.\n";
			frase += "2) Sacar dinero.\n";
			frase += "3) Transferir dinero.\n";
			frase += "4) Actualizar datos.\n";
			frase += "5) Borrar cuenta.\n";
			frase += "6) Cerrar sesion.\n";
			frase += "> ";
			
			cout << "....................";
			cout << endl << "Usuario: " << userActiveName << endl << "Clave: " << userActivePasswd << endl;
			cout << "Fondos: " << util::formattedFloat(userActiveFounds) << endl;
			cout << "....................";
			cout << endl;
			select = util::inputNumber(frase);
			
			switch (select) {
				case 1: db::depositarORetirar(true); break;	//Depositar dinero.
				case 2: db::depositarORetirar(false); break; //Sacar dinero.
				case 3: cout << endl << ((db::transferir()) ? "Transferencia Exitosa." : "Transferencia Cancelada.") << endl; break; //Transferir dinero a otra cuenta.
				case 4: cout << endl << ((db::actualizar()) ? "Cuenta Actualizada Exitosamente." : "Operacion Cancelada.") << endl; break; // Cambiar datos.
				case 5: cout << endl << ((db::borrar()) ? "Cuenta Borrada Exitosamente." : "Operacion Cancelada.") << endl; break; // Borrar cuenta.
				case 6: 
					userActiveName = "";
					userActivePasswd = "";
					continue;		
				default: cout << "Opcion invalida." << endl;
			}
		}
	}
	return 0;
}

/*
   -------------------------------------------
   Definicion de funciones de Inicio de Sesión
   -------------------------------------------
*/

#include "funciones.h"

namespace sesion {
	int crear () {		
		cout << "........................";
		cout << "  @ Crear una Cuenta @  ";
		cout << "........................";
		cout << endl;

		string respaldo, linea, cuenta_nueva, nombre, clave, conf,coordenadas;
		float fondos;
		
		// Nombre
		while (true) {
			nombre = util::inputString("Introduzca un nombre de usuario: ");
			if (db::comprobar(1, nombre) || nombre == "-1") {
				cout << "Nombre invalido." << endl;
				continue;
			}
			break;
		}
		// Clave
		while (true) {
			clave = util::inputString("Introduzca su clave a utilizar (4 caracteres): ", false, 4);
			if (clave.size() != 4) {
				cout << "Clave invalida." << endl;
				continue;
			}
			cout << "";
			conf = util::inputString("Confirme la clave ingresada: ", false, 4);
			if (conf == clave) break;
			cout << "Clave invalida." << endl;
		}
		// Fondos
		while (true) { 
			fondos = util::inputNumber("Monto a abonar: ", true);
			if (fondos > 0) break;
			cout << "Monto invalido." << endl;
		}
		//numero de cuenta
		
			while(true){
				coordenadas = util::inputRandom();
				if(db::comprobar(4, coordenadas))continue;
			break;
			}

		ifstream file("registro.txt");
		while (getline(file, linea)) {
			respaldo += linea + "\n";	
			cout << "...";
		}
		file.close();

		respaldo += nombre + "|" + clave + "|" + util::formattedFloat(fondos)+ "|" + coordenadas +"\n";

		ofstream file2("registro.txt");
		file2 << respaldo;
		file2.close();

		cout << endl;
		return 0;
	}

	int login () {
		cout << "......................";
		cout << "  # Iniciar sesion #  ";
		cout << "......................";
		cout << endl;
		
		string nombre, linea, clave;
		
		//Nombre
		nombre = util::inputString("Nombre de usuario: ");
		if (!db::comprobar(1, nombre)) {
			cout << "Nombre invalido." << endl;
			return 0;
		}
		
		ifstream file("registro.txt");
		while (getline(file, linea)) {
			if (nombre == db::extraer(1, linea)) break;
		}
		file.close();
		
		//Clave
		clave = util::inputString("Clave: ", false, 4);
		if (clave != db::extraer(2, linea)) {
			cout << "Clave invalida." << endl;
			cout << "...................." << endl;
			return 0;
		}

		userActiveName = nombre;
		userActivePasswd = clave;
		userActiveFounds = stof(db::extraer(3, linea));
		userActiveCoordenadas = (db::extraer(4, linea));

		return 0;
	}
} // namespace sesion
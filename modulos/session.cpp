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

		string respaldo, linea, cuenta_nueva, nombre, clave, conf;
		float fondos;
		
		// Nombre
		while (true) {
			cout << "Introduzca un nombre de usuario: ";
			cin >> nombre;
			if (db::comprobar(1, nombre)) {
				cout << "Nombre invalido." << endl;
				continue;
			}
			break;
		}
		// Clave
		while (true) {
			cout << "Introduzca una clave: ";
			cin >> clave;
			if (clave.size() != 4) {
				cout << "Clave invalida." << endl;
				continue;
			}
			cout << "Confirmar clave: ";
			cin >> conf;
			if (conf == clave) break;
			cout << "Clave invalida." << endl;
		}
		// Fondos
		while (true) {
			fondos = util::inputNumber("Monto a abonar: ", true);
			if (fondos > 0) break;
			cout << "Monto invalido." << endl;
		}

		ifstream file("registro.txt");
		while (getline(file, linea)) {
			respaldo += linea + "\n";	
			cout << "...";
		}
		file.close();

		respaldo += nombre + "|" + clave + "|" + util::formattedFloat(fondos) + "\n";

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
		cout << "Nombre de usuario: ";
		cin >> nombre;
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
		cout << "Clave: ";
		cin >> clave;
		if (clave != db::extraer(2, linea)) {
			cout << "Clave invalida." << endl;
			cout << "...................." << endl;
			return 0;
		}

		userActiveName = nombre;
		userActivePasswd = clave;
		userActiveFounds = stof(db::extraer(3, linea));

		return 0;
	}
} // namespace sesion
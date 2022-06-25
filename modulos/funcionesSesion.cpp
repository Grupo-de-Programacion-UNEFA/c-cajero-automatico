/*
   -------------------------------------------
   Definicion de funciones de Inicio de Sesión
   -------------------------------------------
*/

#include "funciones.h"


int crear () {
	
	cout << "........................";
	cout << "  @ Crear una Cuenta @  ";
	cout << "........................";
	cout << endl;
	//exit(1);
	
	string respaldo, linea, cuenta_nueva, nombre, clave, conf, fondos;
	
	while (true) { //Nombre.
		cout << "Introduzca un nombre de usuario: ";
		cin >> nombre;
		if (db::comprobar(1, nombre)) {
			cout << "Nombre invalido." << endl;
			continue;
		}
		break;
	}
	while (true) { //Clave.
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
	while (true) { //Fondos
		cout << "Monto a abonar: ";
		cin >> fondos;
		if (stof(fondos) > 0) break;
		cout << "Monto invalido." << endl;
	}

	ifstream file("registro.txt");
	while (getline(file, linea)) {
		respaldo += linea + "\n";	
		cout << "...";
	}
	file.close();

	respaldo += nombre + "|" + clave + "|" + fondos + "\n";

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
	
	//Nombre.
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
	
	//Clave.
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

	menu_user_logged();

	return 0;
}

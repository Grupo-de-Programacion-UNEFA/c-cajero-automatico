/*
   -------------------------------------------
   Definicion de funciones de Inicio de Sesión
   -------------------------------------------
*/

#include "funciones.h"

int crear () {
	
	spam_de_puntos();
	mostrar_frase_lentamente("  @ Crear una Cuenta @  ", medium);
	spam_de_puntos();
	cout << endl;
	//exit(1);
	
	string respaldo, linea, cuenta_nueva, nombre, clave, conf, fondos;
	
	while (true) {//Nombre.
		cout << "Introduzca un nombre de usuario: ";
		cin >> nombre;
		if (comprobar(1, nombre)) {
			cout << "Nombre invalido." << endl;
			continue;
		}
		break;
	}
	while (true) {//Clave.
		cout << "Introduzca una clave: ";
		cin >> clave;
		cout << "Confirmar clave: ";
		cin >> conf;
		if(conf == clave)break;
		cout << "Clave invalida." << endl;
	}
	while (true) {//Fondos
		cout << "Monto a abonar: ";
		cin >> fondos;
		if(stof(fondos) > 0)break;
		cout << "Monto invalido." << endl;
	}
	
	ifstream file("registro.txt");
	while(getline(file, linea)){
		respaldo += linea + "\n";
		
		spam_de_puntos(tinyStr, medium);
	}
	file.close();
	
	respaldo += nombre + "|" + clave + "|" + fondos + "\n";
	
	//cout << endl << respaldo;exit(1);

	ofstream file2("registro.txt");
	file2 << respaldo;
	file2.close();
	
	cout << endl;
	return 0;
}

int login () {
	
	spam_de_puntos();
	mostrar_frase_lentamente("  # Iniciar sesion #  ", medium);
	spam_de_puntos();
	cout << endl;
	
	string nombre, linea, clave;
	
	//Nombre.
	cout << "Nombre de usuario: ";
	cin >> nombre;
	if (!comprobar(1, nombre)) {
		
		cout << "Nombre invalido." << endl;
		return 0;
	}
	
	//Clave.
	
	ifstream file("registro.txt");
	while (getline(file, linea)) {
		
		if(nombre == extraer(1, linea))break;
	}
	file.close();
	
	cout << "Clave: ";
	cin >> clave;
	if (clave != extraer(2, linea)) {
		
		cout << "Clave invalida." << endl;
		return 0;
	}
	
	spam_de_puntos(shortStr);
	userActiveName = nombre;
	spam_de_puntos(shortStr);
	userActivePasswd = clave;
	spam_de_puntos(shortStr);
	userActiveFounds = stof(extraer(3, linea));
	
	cout << endl << "Usuario: " << extraer(1, linea) << endl;
	cout << "Clave: " << extraer(2, linea) << endl;
	cout << extraer(3, linea) << endl;
	
	menu_user_logged();
	
	return 0;
}
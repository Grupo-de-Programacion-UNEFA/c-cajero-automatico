/*
   ------------------------
   Definicion de funciones
   ------------------------
*/

#include "funciones.h"

void spam_de_puntos (int intervalo, int cantidad) {
	for (int i = 0; i < cantidad; i++) {
		cout << ".";
		this_thread::sleep_for(chrono::milliseconds(intervalo));
	}
}

void mostrar_frase_lentamente (int intervalo, string frase) {
	for (int i = 0; i < frase.size(); i++) {
		cout << frase[i];
		this_thread::sleep_for(chrono::milliseconds(intervalo));
	}
}

string extraer(int lugar, string linea) {
	
	string nombre, clave, fondos;
	char letra;
	
	for (int i = 0; i < linea.size(); i++) {
		letra = linea[i];
		if (letra == '|') break;
		nombre += letra;
	}
	
	for (int i = nombre.size() + 1; i < linea.size(); i++) {
		letra = linea[i];
		if (letra == '|') break;
		clave += letra;
	}
	
	for (int i = nombre.size() + clave.size() + 2; i < linea.size(); i++) {
		letra = linea[i];
		if(letra == '|')break;
		fondos += letra;
	}
	
	//cout << nombre << ";" << clave << ";" << fondos;
	//exit(1);
	switch (lugar) {
		case 1: return nombre;
		case 2: return clave;
		case 3: return fondos;
	}
	return "No funciono xd.";
}

bool comprobar (int lugar, string info) {
	
	string linea;
	ifstream file("registro.txt");
	
	while (getline(file, linea)) {
		if (info == extraer(lugar, linea)) return true;
	}
	return false;
}

void mete_saca (bool meter) {
	
	string linea, respaldo; float monto;
	ifstream file("registro.txt");
	
	if (meter) {//Deposito
		spam_de_puntos(20, 20);
		mostrar_frase_lentamente(20, " +$+ Meter plata +$+ ");
		spam_de_puntos(20, 20);
		
		cout << endl << "Monto a depositar: ";
		cin >> monto;
		
		while (getline(file, linea)) {
			
			if (userActiveName == extraer(1, linea)) {
				respaldo += userActiveName + "|" + userActivePasswd + "|" + to_string(userActiveFounds + monto) + "\n";
				spam_de_puntos(20, 10);
				continue;
			}
			respaldo += linea + "\n";
		}
		file.close();
		userActiveFounds += monto;
	} else {//Retiro
		spam_de_puntos(20, 20);
		mostrar_frase_lentamente(20, " -$- Sacar plata -$- ");
		spam_de_puntos(20, 20);
		
		cout << endl << "Monto a retirar: ";
		cin >> monto;
		
		while (getline(file, linea)) {
			if (userActiveName == extraer(1, linea)) {
				respaldo += userActiveName + "|" + userActivePasswd + "|" + to_string(userActiveFounds - monto) + "\n";
				spam_de_puntos(20, 10);
				continue;
			}
			respaldo += linea + "\n";
		}
		file.close();
		userActiveFounds -= monto;
	}
	
	ofstream file2("registro.txt");
	file2 << respaldo;
	file2.close();
	
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
		spam_de_puntos(20, 50);
		cout << endl << "Usuario: " << userActiveName << endl << "Clave: " << userActivePasswd << endl;
		cout << "Fondos: " << userActiveFounds << endl;
		
		spam_de_puntos(20, 50);
		cout << endl;
		mostrar_frase_lentamente(30, frase);
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


int crear () {
	
	spam_de_puntos(50, 20);
	mostrar_frase_lentamente(50, "  @ Crear una Cuenta @  ");
	spam_de_puntos(50, 20);
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
		
		spam_de_puntos(10, 3);
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
	
	spam_de_puntos(50, 20);
	mostrar_frase_lentamente(50, "  # Iniciar sesion #  ");
	spam_de_puntos(50, 20);
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
	
	spam_de_puntos(20, 10);
	userActiveName = nombre;
	spam_de_puntos(20, 10);
	userActivePasswd = clave;
	spam_de_puntos(20, 10);
	userActiveFounds = stof(extraer(3, linea));
	
	cout << endl << "Usuario: " << extraer(1, linea) << endl;
	cout << "Clave: " << extraer(2, linea) << endl;
	cout << extraer(3, linea) << endl;
	
	menu_user_logged();
	
	return 0;
}
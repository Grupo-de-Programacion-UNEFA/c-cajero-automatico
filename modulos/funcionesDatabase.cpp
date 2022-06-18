/*
   ----------------------------------------
   Definicion de funciones de Base de Datos
   ----------------------------------------
*/

#include "funciones.h"

/* --------- Funciones de Base de datos --------- */
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
		spam_de_puntos();
		mostrar_frase_lentamente(" +$+ Meter plata +$+ ", medium);
		spam_de_puntos();
		
		cout << endl << "Monto a depositar: ";
		cin >> monto;
		
		while (getline(file, linea)) {
			
			if (userActiveName == extraer(1, linea)) {
				respaldo += userActiveName + "|" + userActivePasswd + "|" + to_string(userActiveFounds + monto) + "\n";
				spam_de_puntos(shortStr);
				continue;
			}
			respaldo += linea + "\n";
		}
		file.close();
		userActiveFounds += monto;
	} else {//Retiro
		spam_de_puntos();
		mostrar_frase_lentamente(" -$- Sacar plata -$- ", medium);
		spam_de_puntos();
		
		cout << endl << "Monto a retirar: ";
		cin >> monto;
		
		while (getline(file, linea)) {
			if (userActiveName == extraer(1, linea)) {
				respaldo += userActiveName + "|" + userActivePasswd + "|" + to_string(userActiveFounds - monto) + "\n";
				spam_de_puntos(shortStr);
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
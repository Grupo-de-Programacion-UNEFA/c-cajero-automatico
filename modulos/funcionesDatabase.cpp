/*
   ----------------------------------------
   Definicion de funciones de Base de Datos
   ----------------------------------------
*/

#include "funciones.h"

namespace db {
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

	void depositarORetirar (bool meter) {
		bool valid = false;
		string linea, respaldo; float monto;
		
		if (meter) {//Deposito
			spam_de_puntos();
			mostrar_frase_lentamente(" +$+ Meter plata +$+ ", medium);
			spam_de_puntos();
			
			while (!valid) {
				ifstream file("registro.txt");
				cout << endl << "Ingrese el monto a transferir: ";
				cin >> monto;
				while (getline(file, linea)) {
					if (userActiveName == extraer(1, linea)) {
						if (monto > 0) {
							valid = true;
						} else {
							cout << "Lo siento, el monto no es valido.\n";
						}
						break;
					}
				}
				file.close();
			}
			ifstream file("registro.txt");
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

			spam_de_puntos(shortStr);
			// Abre el segundo ciclo para validar el monto a transferir
			while (!valid) {
				ifstream file("registro.txt");
				cout << endl << "Ingrese el monto a transferir: ";
				cin >> monto;
				while (getline(file, linea)) {
					if (userActiveName == extraer(1, linea)) {
						if (monto > 0 && monto <= stof(extraer(3, linea))) {
							valid = true;
						} else {
							cout << "Lo siento, el monto disponible es insuficiente o el monto ingresado no es valido.\n";
						}
						break;
					}
				}
				file.close();
			}
			ifstream file("registro.txt");
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

	bool transferir () {
		// Se declaran las variables a usar
		bool valid = false;
		float monto;
		char yesOrNot;
		string linea, respaldo, nombreUsuario;
		// Abre el primer ciclo para validar el nombre de usuario
		while (!valid) {
			ifstream file("registro.txt");
			spam_de_puntos();
			mostrar_frase_lentamente(" +$+ Transferencias +$+ ", medium);
			spam_de_puntos();
			cout << endl << "Escriba el nombre del usuario a quien desea transferir: ";
			cin >> nombreUsuario;
			if (nombreUsuario == "-1") {file.close(); return false;}
			while (getline(file, linea)) {
				if (nombreUsuario == extraer(1, linea)) {
					valid = true;
					break;
				}
			}
			file.close();
			if (!valid) cout << "Lo siento, el nombre de usuario no existe.\n\nSi desea cancelar, ingrese '-1'.\n";
		}
		// Se reinicia el validador
		valid = false;
		spam_de_puntos(shortStr);
		// Abre el segundo ciclo para validar el monto a transferir
		while (!valid) {
			ifstream file("registro.txt");
			cout << endl << "Ingrese el monto a transferir: ";
			cin >> monto;
			if (monto == -1) {file.close(); return false;}
			while (getline(file, linea)) {
				if (userActiveName == extraer(1, linea)) {
					if (monto > 0 && monto <= stof(extraer(3, linea))) {
						valid = true;
					} else {
						cout << "Lo siento, el monto disponible es insuficiente o el monto ingresado no es valido.\n\nSi desea cancelar, ingrese '-1'.";
					}
					break;
				}
			}
			file.close();
		}
		// Se reinicia el validador
		valid = false;
		ifstream file("registro.txt");
		// Abre el ciclo para confirmar la transferencia
		while (!valid) {
			cout << "Persona a Transferir: " << nombreUsuario << endl << "Monto a Transferir: $" << to_string(monto);
			cout << "Esta seguro de que los datos son correctos? (Una vez hecha la transferencia no se puede revertir): [Y/n] ";
			cin >> yesOrNot;
			switch (tolower(yesOrNot)) {
				case 'y': valid = true; break;
				case 'n': file.close(); return false;
				default: cout << "Opcion Invalida" << endl; break;
			}
		}
		// Abre el ciclo para actualizar los cambios en el fichero
		while (getline(file, linea)) {
			// Se actualizar la data del usuarioATransferir
			if (nombreUsuario == extraer(1, linea)) {
				respaldo += nombreUsuario + "|" + extraer(2, linea) + "|" + to_string(stof(extraer(3, linea)) + monto) + "\n";
				spam_de_puntos(shortStr);
				continue;
			}
			// Se actualizar la data del userActive
			if (userActiveName == extraer(1, linea)) {
				respaldo += userActiveName + "|" + userActivePasswd + "|" + to_string(userActiveFounds - monto) + "\n";
				spam_de_puntos(shortStr);
				continue;
			}
			respaldo += linea + "\n";
		}
		file.close();
		// Se hace update en las variable globales
		userActiveFounds -= monto;
		
		ofstream file2("registro.txt");
		file2 << respaldo;
		file2.close();
		
		return true;
	}
}
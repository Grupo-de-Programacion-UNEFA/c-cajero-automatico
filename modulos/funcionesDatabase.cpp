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
			cout << ".....................";
			cout << " +$+ Meter plata +$+ ";
			cout << ".....................";
			
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
					cout << "..........";
					continue;
				}
				respaldo += linea + "\n";
			}
			file.close();
			userActiveFounds += monto;
		} else {//Retiro
			cout << ".....................";
			cout << " -$- Sacar plata -$- ";
			cout << ".....................";

			cout << "..........";
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
					cout << "..........";
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
			cout << ".....................";
			cout << " <<$<< Transferencia >>$>> ";
			cout << ".....................";
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
		cout << "..........";
		// Abre el segundo ciclo para validar el monto a transferir
		while (!valid) {
			ifstream file("registro.txt");
			cout << endl << "Ingrese el monto a transferir: ";
			cin >> monto;
			if (monto == -1) {
				file.close();
				return false;
			}
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
			cout << "..........";
			file.close();
		}
		// Se reinicia el validador
		valid = false;
		ifstream file("registro.txt");
		// Abre el ciclo para confirmar la transferencia
		while (!valid) {
			cout << "Persona a Transferir: " << nombreUsuario << endl << "Monto a Transferir: $" << to_string(monto) << endl;
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
				continue;
			}
			// Se actualizar la data del userActive
			if (userActiveName == extraer(1, linea)) {
				respaldo += userActiveName + "|" + userActivePasswd + "|" + to_string(userActiveFounds - monto) + "\n";
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
		cout << ".............................." << endl;
		return true;
	}

	bool actualizar () {
		int select;
		string linea, respaldo, nuevo_nombre, nueva_clave;
		ifstream file("registro.txt");

		cout <<"........................" << endl;
		cout <<" :: Actualizar datos :: " << endl;
		cout <<"........................" << endl;

		cout << "1) Cambiar nombre de usuario.\n";
		cout << "2) Cambiar clave.\n" << endl;
		cout << "> ";
		cin >> select;

		if (select == 1) {
			while (true) {
				cout << "Introducir nuevo nombre de usuario: ";
				cin >> nuevo_nombre;
				if (!comprobar(1, nuevo_nombre)) break;
				cout << "Nombre invalido." << endl;
			}

			while (getline(file, linea)) {

				if (userActiveName == extraer(1, linea)) {
					respaldo += nuevo_nombre + "|" + extraer(2, linea) + "|" + extraer(3, linea) + "\n";
					userActiveName = nuevo_nombre;
					continue;
				}
				respaldo += linea + "\n";
			}
		} else if (select == 2) {

			while (true) {
				cout<<"Introducir nueva clave: ";
				cin >> nueva_clave;
				if(nueva_clave.size() == 4) break;
				cout << "Clave invalida."<< endl;
			}

			while (getline(file, linea)) {
				if (userActiveName == extraer(1, linea)) {
					respaldo += extraer(1, linea) + "|" + nueva_clave + "|" + extraer(3, linea) + "\n";
					userActivePasswd = nueva_clave;
					continue;
				}
				respaldo += linea + "\n";
			}

		} else {
			cout << "Opcion invalida." << endl;
			return false;
		}
		file.close();

		ofstream file2("registro.txt");
		file2 << respaldo;
		file2.close();

		return true;
	}

	bool borrar () {

		string clave, confirm, respaldo, linea;
		ifstream file("registro.txt");

		cout << ".................... X Borrar cuenta X ....................\n";

		cout << "Clave: ";
		cin >> clave;
		cout << "Confirmar clave: ";
		cin >> confirm;

		if (clave == confirm && clave == userActivePasswd) {

			while (getline(file, linea)) {
				if (userActiveName == extraer(1, linea)) {
					cout << ".........." << endl;
					continue;
				}
				respaldo += linea + "\n";
			}
			file.close();

			ofstream file2("registro.txt");
			file2<<respaldo;
			file2.close();

			userActiveName = ""; userActivePasswd = ""; userActiveFounds = 0.0;
			return true;
		} else {
			cout << "Clave invalida." << endl;
		}
		return false;
	}
}
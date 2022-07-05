/*
   ----------------------------------------
   Definicion de funciones de Base de Datos
   ----------------------------------------
*/

#include "funciones.h"

namespace db {
	string extraer(int lugar, string linea) {
		
		string nombre, clave, fondos,coordenadas;
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

		for (int i = nombre.size() + clave.size() + fondos.size() + 3; i < linea.size(); i++) {
			letra = linea[i];
			if(letra == '|')break;
			coordenadas += letra;
		}

		switch (lugar) {
			case 1: return nombre;
			case 2: return clave;
			case 3: return fondos;
			case 4: return coordenadas;
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
		float montoDeOperacion;
		string fraseAImprimir = "", linea, respaldoDeRegistros;
		
		if (meter) { //Deposito
			
			fraseAImprimir += "............................\n";
			fraseAImprimir += " +$+ Depositar Efectivo +$+ \n";
			fraseAImprimir += "............................\n";
			fraseAImprimir += "\nLimite de Deposito: de $" + util::formattedFloat(MIN_MONTO_DEPOSITO) + " a $" + util::formattedFloat(MAX_MONTO_DEPOSITO) + "\n";
			fraseAImprimir += "\nIngrese el monto a depositar: ";
			while (true) {
				montoDeOperacion = util::inputNumber(fraseAImprimir, true);
				if (montoDeOperacion == -1) return; // Comando para cancelar la operacion.
				if (montoDeOperacion >= MIN_MONTO_DEPOSITO && montoDeOperacion <= MAX_MONTO_DEPOSITO) break; // Se vuelve true y rompe
				cout << "Lo siento, el monto no esta dentro de los limites de deposito permitidos.\n";
			}
			ifstream file("registro.txt");
			while (getline(file, linea)) {
				// Busca en cada linea hasta encontrar la del usuario
				if (userActiveName == extraer(1, linea)) {
					respaldoDeRegistros += userActiveName + "|" + userActivePasswd + "|" + util::formattedFloat(userActiveFounds + montoDeOperacion) + "\n";
					continue;
				}
				respaldoDeRegistros += linea + "\n";
			}
			file.close();
			userActiveFounds += montoDeOperacion;
		} else { // Retiro
			fraseAImprimir += ".....................\n";
			fraseAImprimir += " -$- Sacar plata -$- \n";
			fraseAImprimir += ".....................\n";
			fraseAImprimir += "\nLimite de Retiro: de $" + util::formattedFloat(MIN_MONTO_RETIRO) + " a $" + util::formattedFloat(MAX_MONTO_RETIRO) + "\n";
			fraseAImprimir += "\nIngrese el monto a retirar: ";

			// Abre el segundo ciclo para validar el monto a transferir
			while (!valid) {
				ifstream file("registro.txt");
				montoDeOperacion = util::inputNumber(fraseAImprimir, true);

				if (montoDeOperacion == -1) return; // Comando para cancelar la operacion.
				if (!(montoDeOperacion >= MIN_MONTO_RETIRO && montoDeOperacion <= MAX_MONTO_RETIRO)) {
					cout << "Lo siento, el monto no esta dentro de los limites de retiro permitidos.\n";
					continue;
				}
				while (getline(file, linea)) {
					if (userActiveName == extraer(1, linea)) {
						if (montoDeOperacion <= stof(extraer(3, linea))) {
							valid = true;
						} else {
							cout << "Lo siento, los fondos disponibles son insuficientes para el monto a retirar.\n";
						}
						break;
					}
				}
				file.close();
			}
			ifstream file("registro.txt");
			while (getline(file, linea)) {
				if (userActiveName == extraer(1, linea)) {
					respaldoDeRegistros += userActiveName + "|" + userActivePasswd + "|" + util::formattedFloat(userActiveFounds - montoDeOperacion) + "\n";
					cout << "..........";
					continue;
				}
				respaldoDeRegistros += linea + "\n";
			}
			file.close();
			userActiveFounds -= montoDeOperacion;
		}
		
		ofstream file2("registro.txt");
		file2 << respaldoDeRegistros;
		file2.close();
	}

	bool transferir () {
		// Se declaran las variables a usar
		bool valid = false;
		char yesOrNot;
		float montoDeTransferencia;
		string fraseAImprimir, linea, respaldoDeRegistros, coordenadasUsuario;
		// Abre el primer ciclo para validar el nombre de usuario
		
		fraseAImprimir += ".....................";
		fraseAImprimir += " <<$<< Transferencia >>$>> ";
		fraseAImprimir += ".....................";
		fraseAImprimir += "\nLimite de Transferencia: de $" + util::formattedFloat(MIN_MONTO_TRANSFERENCIA) + " a $" + util::formattedFloat(MAX_MONTO_TRANSFERENCIA) + "\n";
		fraseAImprimir += "\nEscriba el numero de cuenta del usuario a quien desea transferir: ";
		while (!valid) {
			ifstream file("registro.txt");

			coordenadasUsuario = util::inputString(fraseAImprimir);
			if (coordenadasUsuario == "-1") {
				file.close(); return false;
			}
			while (getline(file, linea)) {
				if (coordenadasUsuario == extraer(4, linea) && coordenadasUsuario != userActiveCoordenadas) {
					valid = true;
					break;
				}
			}
			file.close();
			if (!valid) cout << "Lo siento, el numero de cuenta del usuario no existe o no es valido.\n\nSi desea cancelar, ingrese '-1'.\n";
		}
		// Se reinicia el validador
		valid = false;
		cout << "..........\n";
		// Abre el segundo ciclo para validar el monto a transferir
		while (!valid) {
			ifstream file("registro.txt");
			montoDeTransferencia = util::inputNumber("Ingrese el monto a transferir: ", true);
			if (montoDeTransferencia == -1) {
				file.close();
				return false;
			}
			if (!(montoDeTransferencia >= MIN_MONTO_TRANSFERENCIA && montoDeTransferencia <= MAX_MONTO_TRANSFERENCIA)) {
				cout << "Lo siento, el monto no esta dentro de los limites de transferencia permitidos.\n";
				continue;
			}
			while (getline(file, linea)) {
				if (userActiveName == extraer(1, linea)) {
					if (montoDeTransferencia > 0 && montoDeTransferencia <= stof(extraer(3, linea))) {
						valid = true;
					} else {
						cout << "Lo siento, el monto disponible es insuficiente o el monto ingresado no es valido.\n\nSi desea cancelar, ingrese '-1'.";
					}
					break;
				}
			}
			cout << "..........\n";
			file.close();
		}
		// Se reinicia el validador
		valid = false;
		ifstream file("registro.txt");
		// Abre el ciclo para confirmar la transferencia
		while (!valid) {
			cout << "Persona a Transferir: " << coordenadasUsuario << endl << "Monto a Transferir: $" << util::formattedFloat(montoDeTransferencia) << endl;
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
			if (coordenadasUsuario == extraer(4, linea)) {
				respaldoDeRegistros += extraer(1, linea) + "|" + extraer(2, linea) + "|" + util::formattedFloat(stof(extraer(3, linea)) + montoDeTransferencia) + "|" + coordenadasUsuario+ "\n";
				continue;
			}
			// Se actualizar la data del userActive
			if (userActiveName == extraer(1, linea)) {
				respaldoDeRegistros += userActiveName + "|" + userActivePasswd + "|" + util::formattedFloat(userActiveFounds - montoDeTransferencia) + "|" + userActiveCoordenadas+"\n";
				continue;
			}
			respaldoDeRegistros += linea + "\n";
		}
		file.close();
		// Se hace update en las variable globales
		userActiveFounds -= montoDeTransferencia;
		
		ofstream file2("registro.txt");
		file2 << respaldoDeRegistros;
		file2.close();
		cout << ".............................." << endl;
		return true;
	}

	bool actualizar () {
		int select;
		string fraseDelMenuAImprimir, linea, respaldoDeRegistros, nuevoNombreDeUsuario, nuevaClavedeUsuario;
		ifstream file("registro.txt");

		fraseDelMenuAImprimir += "........................\n";
		fraseDelMenuAImprimir += " :: Actualizar datos :: \n";
		fraseDelMenuAImprimir += "........................\n";
		fraseDelMenuAImprimir += "1) Cambiar nombre de usuario.\n";
		fraseDelMenuAImprimir += "2) Cambiar clave.\n";
		fraseDelMenuAImprimir += "> ";
		select = util::inputNumber(fraseDelMenuAImprimir);

		if (select == 1) {
			while (true) {
				nuevoNombreDeUsuario = util::inputString("Introduzca el nuevo nombre de usuario: ");
				if (nuevoNombreDeUsuario == "-1") return false;
				if (!comprobar(1, nuevoNombreDeUsuario)) break;
				cout << "Nombre invalido. Si desea cancelar, ingrese '-1'" << endl;
			}

			while (getline(file, linea)) {

				if (userActiveName == extraer(1, linea)) {
					respaldoDeRegistros += nuevoNombreDeUsuario + "|" + extraer(2, linea) + "|" + extraer(3, linea) + "\n";
					userActiveName = nuevoNombreDeUsuario;
					continue;
				}
				respaldoDeRegistros += linea + "\n";
			}
		} else if (select == 2) {

			while (true) {
				nuevaClavedeUsuario = util::inputString("Introduzca la nueva clave: ", false, 4);
				if(nuevaClavedeUsuario.size() == 4) break;
				cout << "Clave invalida."<< endl;
			}

			while (getline(file, linea)) {
				if (userActiveName == extraer(1, linea)) {
					respaldoDeRegistros += extraer(1, linea) + "|" + nuevaClavedeUsuario + "|" + extraer(3, linea) + "\n";
					userActivePasswd = nuevaClavedeUsuario;
					continue;
				}
				respaldoDeRegistros += linea + "\n";
			}

		} else {
			cout << "Opcion invalida." << endl;
			return false;
		}
		file.close();

		ofstream file2("registro.txt");
		file2 << respaldoDeRegistros;
		file2.close();

		return true;
	}

	bool borrar () {

		string clave, confirm, respaldoDeRegistros, linea;
		ifstream file("registro.txt");

		cout << ".................... X Borrar cuenta X ....................\n";

		clave = util::inputString("Clave: ", false, 4);
		confirm = util::inputString("Confirmar clave: ", false, 4);

		if (clave == confirm && clave == userActivePasswd) {

			while (getline(file, linea)) {
				if (userActiveName == extraer(1, linea)) {
					cout << ".........." << endl;
					continue;
				}
				respaldoDeRegistros += linea + "\n";
			}
			file.close();

			ofstream file2("registro.txt");
			file2 << respaldoDeRegistros;
			file2.close();

			userActiveName = ""; userActivePasswd = ""; userActiveFounds = 0.0;
			return true;
		} else {
			cout << "Clave invalida." << endl;
		}
		return false;
	}
} // namespace db
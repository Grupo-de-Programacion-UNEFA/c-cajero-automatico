/*
   ----------------------------------------
   Definicion de funciones de Base de Datos
   ----------------------------------------
*/

#include "funciones.h"

namespace db {
	string extraer(int lugar, string linea) {

		/*------------Orden de Datos---------------
		 	nombre | clave | fondos | coordenadas
		 */
		
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
			if (info == extraer(lugar, linea)) 
			{
				file.close();
				return true;
			}
		}
		file.close();
		return false;
	}

	void depositarORetirar (bool meter) {
		bool valid = false;
		float montoDeOperacion;
		string fraseAImprimir = "", linea;
		
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
			//Se actualizan los datos.
			escribir(3, userActiveCoordenadas, to_string(userActiveFounds + montoDeOperacion), false);
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
			//Se actualizan los datos.
			escribir(3, userActiveCoordenadas, to_string(userActiveFounds - montoDeOperacion), false);
			userActiveFounds -= montoDeOperacion;
		}
	}

	bool transferir () {
		// Se declaran las variables a usar
		bool valid = false;
		char yesOrNot;
		float montoDeTransferencia, fondosUsuario;
		string fraseAImprimir, linea, coordenadasUsuario;
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
					fondosUsuario = stof(extraer(3, linea));
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
		// Abre el ciclo para confirmar la transferencia
		while (!valid) {
			cout << "Persona a Transferir: " << coordenadasUsuario << endl << "Monto a Transferir: $" << util::formattedFloat(montoDeTransferencia) << endl;
			cout << "Esta seguro de que los datos son correctos? (Una vez hecha la transferencia no se puede revertir): [Y/n] ";
			cin >> yesOrNot;
			switch (tolower(yesOrNot)) {
				case 'y': valid = true; break;
				case 'n': return false;
				default: cout << "Opcion Invalida" << endl; break;
			}
		}
		// Se actualizar la data del usuarioATransferir
		escribir(3, coordenadasUsuario, util::formattedFloat(fondosUsuario + montoDeTransferencia), false);
		// Se actualizar la data del userActive
		escribir(3, userActiveCoordenadas, util::formattedFloat(stof(extraer(3, linea)) - montoDeTransferencia), false);
		userActiveFounds = stof(extraer(3, linea)) - montoDeTransferencia;
		cout << ".............................." << endl;
		return true;
	}

	bool actualizar () {
		int select;
		string fraseDelMenuAImprimir, linea, respaldoDeRegistros, nuevoNombreDeUsuario, nuevaClavedeUsuario;

		fraseDelMenuAImprimir += "........................\n";
		fraseDelMenuAImprimir += " :: Actualizar datos :: \n";
		fraseDelMenuAImprimir += "........................\n";
		fraseDelMenuAImprimir += "1) Cambiar nombre de usuario.\n";
		fraseDelMenuAImprimir += "2) Cambiar clave.\n";
		fraseDelMenuAImprimir += "> ";
		select = util::inputNumber(fraseDelMenuAImprimir);

		if (select == 1) 
		{
			while (true) 
			{
				nuevoNombreDeUsuario = util::inputString("Introduzca el nuevo nombre de usuario: ");
				if (nuevoNombreDeUsuario == "-1") return false;
				if (!comprobar(1, nuevoNombreDeUsuario)) break;
				cout << "Nombre invalido. Si desea cancelar, ingrese '-1'" << endl;
			}
		escribir(1, userActiveCoordenadas, nuevoNombreDeUsuario, false);
		userActiveName = nuevoNombreDeUsuario;
		} else if (select == 2) 
		{
			while (true) 
			{
				nuevaClavedeUsuario = util::inputString("Introduzca la nueva clave: ", false, 4);
				if(nuevaClavedeUsuario.size() == 4) break;
				cout << "Clave invalida."<< endl;
			}
		escribir (2, userActiveCoordenadas, nuevaClavedeUsuario, false);
		userActivePasswd = nuevaClavedeUsuario;
		} else 
		{
			cout << "Opcion invalida." << endl;
			return false;
		}

		return true;
	}

	void escribir (int lugar, string coordenadas, string newInfo, bool borrar = false)  {

		ifstream file ("registro.txt");
		string linea, respaldoDeDatos = "";

		while (getline(file, linea))
		{
			if(borrar && coordenadas == extraer(4, linea)) continue;
			if(coordenadas == extraer(4, linea))
			{
				cout<<"checkpoint1."<<endl;
				switch (lugar)
				{
				case 1:
					respaldoDeDatos += newInfo + "|" + extraer(2, linea) + "|" + extraer(3, linea) + "|" + extraer(4, linea) + "\n"; break;
				case 2:
					respaldoDeDatos += extraer(1, linea) + "|" + newInfo + "|" + extraer(3, linea) + "|" + extraer(4, linea) + "\n"; break;
				case 3:
					respaldoDeDatos += extraer(1, linea) + "|" + extraer(2, linea) + "|" + newInfo + "|" + extraer(4, linea) + "\n"; break;
				case 4:
					respaldoDeDatos += extraer(1, linea) + "|" + extraer(3, linea) + "|" + extraer(3, linea) + "|" + newInfo + "\n"; break;
				default:
					cout << endl << "PROBLEMA EN LA FUNCION DE ESCRIBIR." << endl; exit (EXIT_FAILURE);
				}
				continue;
			}
			cout<<endl<<"a"<<endl;
			respaldoDeDatos += linea + "\n";
		}
		file.close();

		ofstream file2 ("registro.txt");
		file2 << respaldoDeDatos;
		file2.close();
	}

	bool borrar () {

		string clave, confirm;

		cout << ".................... X Borrar cuenta X ....................\n";

		clave = util::inputString("Clave: ", false, 4);
		confirm = util::inputString("Confirmar clave: ", false, 4);

		if (clave == confirm && clave == userActivePasswd) 
		{
			escribir (1, userActiveCoordenadas, "X", true);
			userActiveName = "";
			userActivePasswd = "";
		} else {
			cout << "Clave invalida." << endl;
		}
		return false;
	}
} // namespace db
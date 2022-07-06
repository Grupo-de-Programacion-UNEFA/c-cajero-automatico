/*
   ----------------------------------------
   Definicion de funciones de Base de Datos
   ----------------------------------------
*/

#include "funciones.h"

namespace db {
	// Recibe una linea de registro y devuelve el dato solicitado segun lo indica el parametro lugar
	string extraer (int lugar, string linea) {
		/*------------Orden de Datos---------------
		 	1      | 2     | 3      | 4
		 	nombre | clave | fondos | coordenadas
		*/
			
		int indice = 1, i = -1, longitudLinea = linea.size();
		string dato, clave, fondos,coordenadas;
		char letra;
		
		// Ejecuta un bucle para la cantidad de columnas presente
		for (indice; indice <= DB_NCOLUMNAS; indice++) {
			dato = ""; // Limpia la cadena
			for (i++; i < longitudLinea; i++) {
				// Captura la letra segun el indice, si encuentra un separador termina la ejecucion, contrario lo suma a la cadena de dato
				letra = linea[i];
				if (letra == '|') break;
				dato += letra;
			}
			if (indice == lugar) return dato;
		}
		return "";
	}

	// Comprueba en todos los registros si existe si hay un dato existente, segun el indice de columna y el dato enviado
	bool comprobar (int lugar, string info) {
		string linea;
		ifstream file(DB_LOCATION);
		
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

	void escribir (int lugar, string numeroDeCuenta, string newInfo, bool borrar)  {

		fstream file(DB_LOCATION);
		string linea, respaldoDeDatos = "";

		while (getline(file, linea)) {
			// Encuentra en el registro que coincida con el numer de cuenta buscado
			if (numeroDeCuenta == extraer(4, linea)) {
				// Si se desea borrar, lo omite
				if (borrar) continue;
				cout << "checkpoint1." << endl;
				// Hace un bucle en cada columna registrada
				for (int i = 1; i <= DB_NCOLUMNAS; i++) {
					// Si es la columna indicada, concatena el dato nuevo, de lo contrario el existente
					if (i == lugar) {
						respaldoDeDatos += newInfo;
					} else {
						respaldoDeDatos += extraer(i, linea);
					}
					// Si es el ultimo indice, concatena un salto de linea, de lo contrario el separador
					respaldoDeDatos += (i == DB_NCOLUMNAS) ? "\n" : "|";
				}
				continue;
			}
			cout << endl << "a" << endl;
			respaldoDeDatos += linea + "\n";
		}
		file << respaldoDeDatos;
		file.close();
	}
} // namespace db
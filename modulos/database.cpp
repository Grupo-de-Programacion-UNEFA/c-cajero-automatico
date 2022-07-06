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
		for (indice; indice <= 4; indice++) {
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

	void escribir (int lugar, string coordenadas, string newInfo, bool borrar = false)  {

		ifstream file ("registro.txt");
		string linea, respaldoDeDatos = "";

		while (getline(file, linea)) {
			if (borrar && coordenadas == extraer(4, linea)) continue;
			if (coordenadas == extraer(4, linea)) {
				cout << "checkpoint1." << endl;
				switch (lugar) {
				case 1:
					respaldoDeDatos += newInfo + "|" + extraer(2, linea) + "|" + extraer(3, linea) + "|" + extraer(4, linea) + "\n"; break;
				case 2:
					respaldoDeDatos += extraer(1, linea) + "|" + newInfo + "|" + extraer(3, linea) + "|" + extraer(4, linea) + "\n"; break;
				case 3:
					respaldoDeDatos += extraer(1, linea) + "|" + extraer(2, linea) + "|" + newInfo + "|" + extraer(4, linea) + "\n"; break;
				case 4:
					respaldoDeDatos += extraer(1, linea) + "|" + extraer(3, linea) + "|" + extraer(3, linea) + "|" + newInfo + "\n"; break;
				default:
					cout << endl << "ERROR EN LA FUNCION DE ESCRIBIR." << endl; exit (EXIT_FAILURE);
				}
				continue;
			}
			cout << endl << "a" << endl;
			respaldoDeDatos += linea + "\n";
		}
		file.close();

		ofstream file2 ("registro.txt");
		file2 << respaldoDeDatos;
		file2.close();
	}
} // namespace db
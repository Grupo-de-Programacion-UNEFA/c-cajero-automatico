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
					cout << endl << "PROBLEMA EN LA FUNCION DE ESCRIBIR." << endl; exit (EXIT_FAILURE);
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
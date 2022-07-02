/*
   -------------------------------------
   Definicion de funciones de Utilidades
   -------------------------------------
*/
// Llama las librerias de cabecero, funciones y variables externas
#include "funciones.h"

namespace util {
    float inputNumber (string textoARepetir, bool decimal) {
		string input = "";
		while (true) {
            cout << textoARepetir;
			cin >> input;
			input = util::formattedFloat(input);
			try	{
				// Lo convierte a float, luego a string formateado y por último
                if (decimal) return stof(input);
                return stoi(input);
			} catch (...) {
				cout << "Numero ingresado invalido." << endl;
				continue;
			}
		}
	}
	string formattedFloat (float num) {
		string str = "";
		str = to_string(num);
		return util::formattedFloat(str);
	}
	string formattedFloat (string str) {
		int pos;
		pos = str.find('.');
		if (pos == -1) return str;
		return str.substr(0, pos) + str.substr(pos, 3);
	}
	string inputString (string textoARepetir, bool espaciosEnBlanco, unsigned int longitudDeseada) {
		string input = "";
		while (true) {
			// Imprime el texto en cada vuelta para que no se pierda
            cout << textoARepetir;
			if (espaciosEnBlanco) {
				// Limpia los datos para que no se adulteren
				cin.ignore();
				// Captura la línea completa
				getline(cin, input);
			} else {
				cin >> input;
			}
			try	{
				// Valida si tiene carácteres no permitidos '|', '\', ',', '.' o espacios en blanco si lo dice el argumento 
                if (input.find('|') != -1 || input.find('\\') != -1 || input.find(',') != -1 || input.find('.') != -1 || (!espaciosEnBlanco && input.find(' ') != -1)) throw 1;
				if (longitudDeseada > 0 && input.size() != longitudDeseada) throw 2;
				return input;
			} catch (int codigoError) {
				string mensajeError = "";
				switch (codigoError) {
					case 1:
						mensajeError = "Entrada invalida, debe ingresar sin usar "; 
						if (espaciosEnBlanco) mensajeError += "espacios en blanco ni ";						
						mensajeError += "los caracteres especiales '|', '\\', ',' o '.'";
						break;
					case 2:
						mensajeError = "Entrada valida, el dato debe tener (" + to_string(longitudDeseada) + ") caracteres de longitud"; break;
				}
				cout << mensajeError << endl;
				continue;
			}
		}
	}
} // namespace util

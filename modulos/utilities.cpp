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
} // namespace util

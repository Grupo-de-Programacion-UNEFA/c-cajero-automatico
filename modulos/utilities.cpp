/*
   -------------------------------------
   Definicion de funciones de Utilidades
   -------------------------------------
*/
// Llama las librerias de cabecero, funciones y variables externas
#include "funciones.h"

namespace util {
    float inputNumber (string textoARepetir, bool decimal) {
		string input;
		while (true) {
            cout << textoARepetir;
			cin >> input;
			try	{
                if (decimal) return stof(input);
                return stoi(input);
			} catch(...) {
				cout << "Numero ingresado invalido." << endl;
				continue;
			}
		}
	}
} // namespace util

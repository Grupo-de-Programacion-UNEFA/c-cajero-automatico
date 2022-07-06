/*
   ------------------------
   Declaracion de funciones
   ------------------------
*/

#pragma once // directiva que indica que se compile una sola vez

// Librerias de cabecero a utilizar

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cctype>
#include <stdlib.h>
#include <random>

using namespace std;

// Declara las variables globales como externas a este archivo (es decir que son definidas o usadas en otra parte)
extern float userActiveFounds;
extern string userActiveName, userActivePasswd,userActiveCoordenadas;
// Variables Constantes
extern const float MIN_MONTO_TRANSFERENCIA, MIN_MONTO_DEPOSITO, MIN_MONTO_RETIRO;
extern const float MAX_MONTO_TRANSFERENCIA, MAX_MONTO_DEPOSITO, MAX_MONTO_RETIRO;

namespace action {
   void depositarORetirar (bool meter);
   bool transferir ();
   bool actualizar ();
   bool borrar ();
} // namespace action
namespace db {
   string extraer (int lugar, string linea);
   bool comprobar (int lugar, string info);
   void escribir (int lugar, string coordenadas, string newInfo, bool borrar);
} // namespace db
namespace sesion {
   int crear ();
   int login ();
} // namespace sesion
namespace util {
   float inputNumber (string textoARepetir, bool decimal = false);
   string formattedFloat (float num);
   string formattedFloat (string str);
   string inputString (string textoARepetir, bool espaciosEnBlanco = false, unsigned int longitudDeseada = 0);
   string inputRandom();
} // namespace util

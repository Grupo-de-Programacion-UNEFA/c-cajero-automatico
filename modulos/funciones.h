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

using namespace std;

// Declara las variables globales como externas a este archivo (es decir que son definidas o usadas en otra parte)
extern float userActiveFounds;
extern string userActiveName, userActivePasswd;

namespace db {
   string extraer (int lugar, string linea);
   bool comprobar (int lugar, string info);
   void depositarORetirar (bool meter);
   bool transferir ();
   bool actualizar ();
   bool borrar ();
} // namespace db
namespace sesion {
   int crear ();
   int login ();
} // namespace sesion
namespace print {
   int menu_user_logged ();
} // namespace print
namespace util {
   float inputNumber (string textoARepetir, bool decimal = false);
   string formattedFloat (float num);
   string formattedFloat (string str);
} // namespace util

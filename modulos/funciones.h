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
extern string userActiveName, userActivePasswd;
extern float userActiveFounds;

namespace db {
   string extraer(int lugar, string linea);
   bool comprobar (int lugar, string info);
   void depositarORetirar (bool meter);
   bool transferir ();
   bool actualizar ();
   bool borrar ();
}

int menu_user_logged();
int crear ();
int login ();
int borrar();
int actualizar();

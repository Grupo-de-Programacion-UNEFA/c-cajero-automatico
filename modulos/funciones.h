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
#include <stdlib.h>
#include <thread>
#include <chrono>

using namespace std;

enum Speed {fast = 10, medium = 20, low = 50};
enum LongStr {tinyStr = 3, shortStr = 10, normalStr = 20, longStr = 50};

// Declara las variables globales como externas a este archivo (es decir que son definidas o usadas en otra parte)
extern string userActiveName, userActivePasswd;
extern float userActiveFounds;

void spam_de_puntos (LongStr cantidad = normalStr, Speed intervalo = fast);
void mostrar_frase_lentamente (string frase, Speed intervalo = fast);

namespace db{
   string extraer(int lugar, string linea);
   bool comprobar (int lugar, string info);
   void depositarORetirar (bool meter);
}

int menu_user_logged();
int crear ();
int login ();
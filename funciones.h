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

// Declara las variables globales como externas a este archivo (es decir que son definidas o usadas en otra parte)
extern string userActiveName, userActivePasswd;
extern float userActiveFounds;


void spam_de_puntos (int intervalo, int cantidad);
void mostrar_frase_lentamente (int intervalo, string frase);

string extraer(int lugar, string linea);
bool comprobar (int lugar, string info);

void mete_saca (bool meter);
int menu_user_logged();
int crear ();
int login ();
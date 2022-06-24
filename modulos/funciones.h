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

string name = "MasterSex", pass = "2684"; float founds = 10.5;

int borrar(); int actualizar();


string extraer(int lugar, string linea);
bool comprobar (int lugar, string info);
int mete_saca(bool meter);
int transferir ();

int menu_user_logged();
int crear ();
int login ();
int borrar();
int actualizar();

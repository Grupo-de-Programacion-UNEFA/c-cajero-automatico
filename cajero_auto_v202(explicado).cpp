/*Es la 3ra vez que hago esta mamada, no creo que sirva pero
hay que chambear.

Actualizacion: SI SIRVIO XDXDXD.

No usar vectores, 
Verificar la extracion de datos(3).*/
#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<stdlib.h>

//Para hacer cosas nice xd.
#include<thread>
#include<chrono>
using namespace std;
/*-----------------Administracion de Datos------------------*/

string name, pass;

void spam_de_puntos(int intervalo, int cantidad){
	
	for(int i = 0; i < cantidad; i++){
		
		cout<<".";
		this_thread::sleep_for(chrono::milliseconds(intervalo));
	}
}
void mostrar_frase_lentamente(int intervalo, string frase){
	
	for(int i = 0; i < frase.size(); i++){
		
		cout<<frase[i];
		this_thread::sleep_for(chrono::milliseconds(intervalo));
	}
}

int menu_user_logged(){
	
	string frase; int select;
	
	frase += "1) Depositar dinero.\n";
	frase += "2) Sacar dinero.\n";
	frase += "3) Transferir dinero.\n";
	frase += "4) Actualizar datos.\n";
	frase += "5) Borrar cuenta.\n";
	frase += "6) Cerrar sesion.\n";
	
	while(true){
		
		spam_de_puntos(30, 50);
		cout<<endl;
		mostrar_frase_lentamente(30, frase);
		cin>>select;
		
		switch(select){
			
			case 1://Depositar dinero.
			case 2://Sacar dinero.
			case 3://Transferir dinero a otra cuenta.
			case 4://Cambiar datos.
			case 5://Borrar cuenta.
			case 6: 
				name = "";
				pass = "";
				return 0;
			
			default:
				cout<<"Opcion invalida, subnormal."<<endl;
		}
	}
}


string extraer(int lugar, string linea){
	
	string nombre, clave, fondos;char letra;
	
	for(int i = 0; i < linea.size(); i++){
		
		letra = linea[i];
		if(letra == '|')break;
		nombre += letra;
	}
	
	for(int i = nombre.size() + 1; i < linea.size(); i++){
		
		letra = linea[i];
		if(letra == '|')break;
		clave += letra;
	}
	
	for(int i = nombre.size() + clave.size() + 2;i < linea.size(); i++){
		
		letra = linea[i];
		if(letra == '|')break;
		fondos += letra;
	}
	
//cout<<nombre<<";"<<clave<<";"<<fondos;
//exit(1);
	switch(lugar){
		
		case 1: return nombre;
		case 2: return clave;
		case 3: return fondos;
		
		default: return "No funciono xd.";
	}
	return 0;
}

bool comprobar(int lugar, string info){
	
	string linea;
	ifstream file("registro.txt");
	
	while(getline(file, linea)){
		
		if(info == extraer(lugar, linea))return true;
	}
	
	return false;
}


int crear(){
	
	spam_de_puntos(50, 20);
	mostrar_frase_lentamente(50, "  @ Crear una Cuenta @  ");
	spam_de_puntos(50, 20);
	cout<<endl;
//exit(1);
	
	string respaldo, linea, cuenta_nueva, nombre, clave, conf, fondos;
	
	while(true){//Nombre.
		
		cout<<"Introduzca un nombre de usuario: ";
		cin>>nombre;
		if(comprobar(1, nombre)){
			
			cout<<"Nombre invalido."<<endl;
			continue;
		}
		break;
	}
	while(true){//Clave.
		
		cout<<"Introduzca una clave: ";
		cin>>clave;
		cout<<"Confirmar clave: ";
		cin>>conf;
		if(conf == clave)break;
		cout<<"Clave invalida."<<endl;
	}
	while(true){//Fondos
		
		cout<<"Monto a abonar: ";
		cin>>fondos;
		if(stof(fondos) > 0)break;
		cout<<"Monto invalido."<<endl;
	}
	
	ifstream file("registro.txt");
	while(getline(file, linea)){
		
		respaldo += linea + "\n";
		
		spam_de_puntos(10, 3);
	}
	file.close();
	
	respaldo += nombre + "|" + clave + "|" + fondos + "\n";
	
//cout<<endl<<respaldo;exit(1);

	ofstream file2("registro.txt");
	file2<<respaldo;
	file2.close();
	
	cout<<endl;
	return 0;
}

int login(){
	
	spam_de_puntos(50, 20);
	mostrar_frase_lentamente(50, "  # Iniciar sesion #  ");
	spam_de_puntos(50, 20);
	cout<<endl;
	
	string nombre, linea, clave;
	
//Nombre.
	cout<<"Nombre de usuario: ";
	cin>>nombre;
	if(!comprobar(1, nombre)){
		
		cout<<"Nombre invalido."<<endl;
		return 0;
	}
	
//Clave.
	
	ifstream file("registro.txt");
	while(getline(file, linea)){
		
		if(nombre == extraer(1, linea))break;
	}
	file.close();
	
	cout<<"Clave: ";
	cin>>clave;
	if(clave != extraer(2, linea)){
		
		cout<<"Clave invalida."<<endl;
		return 0;
	}
	
	spam_de_puntos(30, 10);
	name = nombre;
	spam_de_puntos(30, 10);
	pass = clave;
	
	cout<<endl<<"Usuario: "<<extraer(1, linea)<<endl;
	cout<<"Clave: "<<extraer(2, linea)<<endl;
	cout<<"Fondos: "<<extraer(3, linea)<<endl;
	
	menu_user_logged();
	
	return 0;
}

int main(){
	
	int select; string opciones;
	
	opciones += "1) Iniciar sesion.\n";
	opciones += "2) Crear cuenta.\n";
	opciones += "3) Salir.\n";
	
	while(true){//Menu de inicio.
		
		cout<<"\t\t";
		mostrar_frase_lentamente(30, "Bienvenido al Banco Petare");
		cout<<endl<<endl;
		
		mostrar_frase_lentamente(30, opciones);
		cin>>select;
		
		switch(select){
			
			case 1: login(); break;
			case 2: crear(); break;
			case 3: return 0;
			
			default:
			cout<<"Chingada madre, escribe las opciones que te doy, puto animal."<<endl;
			break;
		}
	}
	
	int x;
	cin>>x;
	cout<<extraer(x, "Niver|696|152.215")<<endl;
	
	string s = extraer(3, "n1|0|0.9");
	float y = stof(s);
	cout<<abs(y - 1);
	
	return 0;
}

/*Es la 3ra vez que hago esta mamada, no creo que sirva pero
hay que chambear.

No usar vectores, */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;
//Variables globales.
string username;int pass;float founds;

/*Lee un elemento en especifico: 
dato es el numero de elemento;
liena es el texto de donde se sacara el elemento.*/
string extraer(int dato,string linea){
	//Mas variables piteras.
	char letra;string parte;int part=1;
	//Pasar por cada letra de la linea.
	for(int i=0;i<linea.size();i++){
		//Copiar la letra en la posicion i.
		letra=linea[i];
		//Comprobar fin del primer elemento.
		if(letra=='|'){
			switch(dato){
				case 1://Si se solicito el 1er dato.
					return parte;
				case 2://Si se solicito el 2do.
					if(part==2)return parte;//Se comprueba si ya se pasi el 2do elemento.
					part++;parte="";break;
				case 3://Si se solicito el 3ero.
					if(part==3)return parte;//Se comprueba si ya se paso el 3er elemento.
					part++,parte="";break;
				default:
					cout<<"Dato errado|funcion:extraer";exit(1);
			}
			continue;
		}
		parte+=letra;//Se copia el dato letra por letra.
	}
	return 0;
}

/*Dice que leer: 
dato es el numero de elemento;
name es el elemento a comparar*/
bool comprobar(int dato,string nombre){
	string linea,name;
	ifstream file("registro.txt");
	while(getline(file,linea)){
		name=extraer(dato,linea);
	//	cout<<name<<"!comprobando"<<endl;
		if(nombre==name){
			return true;
		}
	}
	return false;
}
//Crea una cuenta nueva.
int crear(){
	//Crear pura variable pitera.
	string linea, texto, nombre;int clave=000,contra;float rial=0.1;
	
	//Ponerle datos a la monda.
	
	//nombre
	while(true){
		cout<<"Introduzca un nombre de usuario: ";
		cin>>nombre;
	//Se comprueba que el nombre ingresado no se repita
		if(comprobar(1,nombre)){
			cout<<"Nombre invalido."<<endl;
		}else{
			cout<<"Nombre valido."<<endl;break;
		}
	}
	//Clave
	while(true){
		cout<<"Introduzca una clave: ";
		cin>>clave;
		cout<<"Confirmar la clave: ";
		cin>>contra;
		if(contra==clave)break;
		cout<<"Clave invalida."<<endl;
	}
	//Monto inicial
	cout<<"Con cuanto dinero dese aperturar su cuenta?\nMonto: ";
	cin>>rial;
	if(rial==0)cout<<"Pss...Este lo que es un pelabolas."<<endl;
	
	//Leer archivo.
	
	ifstream file1("registro.txt");
	//Se crea respaldo del archivo.
	while(getline(file1,linea)){
		texto+=linea+"\n";
	}
	//Cerrar archivo.
	file1.close();
	
	//Escribir archivo.
	
	ofstream file2("registro.txt");
	//Anadirle mierda al archivo.
	file2<<texto<<nombre<<"|"<<clave<<"|"<<rial<<"\n";
	//Cerrar archivo.
	file2.close();
	
	return 0;
}

int login(){
	string nombre,clavechar;int clave;
	cout<<"Nombre de usuario: ";
	cin>>nombre;
	if(!comprobar(1,nombre)){
		cout<<"Nombre no encontrado."<<endl;return 0;
	}
	while(true){
		cout<<"Clave: ";
		cin>>clave;
		clavechar=to_string(clave);
		if(comprobar(2,clavechar))break;
		cout<<"Clave invalida. Intente nuevamente"<<endl;
	}
	username=nombre;pass=clave;
	//cout<<"HOLAAAAAAAAAAAAA"<<endl;
	return 0;
}

int borrar(){
	string linea,texto,name;int con1,con2,i=0;
	
	cout<<"Introduzca la clave: ";
	cin>>con1;
	cout<<"Confirme la clave: ";
	cin>>con2;
	if(con1==con2&&con1==pass&&con2==pass){
	}else{
		cout<<"Clave invalida."<<endl;
		return 0;
	}
	
	ifstream file("registro.txt");
	while(getline(file,linea)){
		name=extraer(1,linea);
		if(username==name&&i==0){
			i++;
		}else{
			texto+=linea+"\n";
		}
	}
	file.close();
	
	ofstream file2("registro.txt");
	file2<<texto;
	file2.close();
	return 0;
}

int main(){
	crear();
	login();
	cout<<"\tNombre de usuario: "<<username<<endl<<"\tClave: "<<to_string(pass)<<endl;
	borrar();
	return 0;
}
/*
   ----------------------------------------
   Definicion de funciones de Base de Datos
   ----------------------------------------
*/

#include "funciones.h"

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


int mete_saca(bool meter){

	string linea, respaldo, clave; float monto;
	ifstream file("registro.txt");

	if(meter){//Deposito

		cout<<"....................";
		cout<<" +$+ Meter plata +$+ ";
		cout<<"....................";

		cout<<endl<<"Monto a depositar: ";
		cin>>monto;

		while(getline(file, linea)){

			if(name == extraer(1, linea)){

				respaldo += name + "|" + pass + "|" + to_string(founds + abs(monto)) + "\n";
				cout<<"..........";
				continue;
			}
			respaldo += linea + "\n";
		}
		file.close();
		founds += abs(monto);
	}

	if(!meter){//Retiro

		cout<<"....................";
		cout<<" -$- Sacar plata -$- ";
		cout<<"....................";

		while(true){

			cout<<endl<<"Monto a retirar: ";
			cin>>monto;
			if(abs(monto) > founds){

				cout<<"Monto invalido.";
				continue;
			}
			break;
		}

		while(getline(file, linea)){

			if(name == extraer(1, linea)){

				respaldo += name + "|" + pass + "|" + to_string(founds - abs(monto)) + "\n";
				cout<<"..........";
				continue;
			}
			respaldo += linea + "\n";
		}
		file.close();
		founds -= abs(monto);
	}

	cout<<endl<<"Clave: ";
	cin>>clave;
	if(clave != pass) {

		cout<<"Clave invalida."<<endl;
		return 0;
	}

	ofstream file2("registro.txt");
	file2<<respaldo;
	file2.close();

	return 0;
}

int transferir(){

	string cuenta_destino, linea, respaldo, clave; float monto;

	cout<<"....................";
	cout<<" <<$<< Transferencia >>$>> ";
	cout<<"...................."<<endl;

	while(true){
		cout<<"Introducir nombre de usuario de la cuenta destino: ";
		cin>>cuenta_destino;
		if(comprobar(1, cuenta_destino)) break;
		cout<<"Nombre de usuario invalido."<<endl;
	}

	while(true){

		cout<<"Monto a transferir: ";
		cin>>monto;
		if(abs(monto) <= founds) break;
		cout<<"Cantidad invalida."<<endl;
	}

	ifstream file("registro.txt");

	while(getline(file, linea)){

		if(cuenta_destino == extraer(1, linea)){

			respaldo += extraer(1, linea) + "|" + extraer(2, linea) + "|" + to_string(stof(extraer(3, linea)) + abs(monto)) + "\n";
			continue;
		}
		if(name == extraer(1, linea)){

			respaldo += extraer(1, linea) + "|" + extraer(2, linea) + "|" + to_string(stof(extraer(3, linea)) - abs(monto)) + "\n";
			continue;
		}

		respaldo += linea + "\n";
	}
	file.close();

	cout<<"Clave: ";
	cin>>clave;
	if(clave != pass) {

		cout<<"Clave invalida."<<endl;
		return 0;
	}

	ofstream file2("registro.txt");
	file2<<respaldo;
	file2.close();

	founds -= abs(monto);

	return 0;
}

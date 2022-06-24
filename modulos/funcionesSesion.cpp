/*
   -------------------------------------------
   Definicion de funciones de Inicio de Sesión
   -------------------------------------------
*/

#include "funciones.h"
actualizar(){

	int select; string linea, respaldo, nuevo_nombre, nueva_clave;
	ifstream file("registro.txt");

	cout<<"....................";
	cout<<" :: Actualizar datos :: ";
	cout<<"...................."<<endl;

	cout<<"1) Cambiar nombre de usuario.\n2) Cambiar clave."<<endl;
	cin>>select;

	if(select == 1){

		while(true){

			cout<<"Introducir nuevo nombre de usuario: ";
			cin>>nuevo_nombre;
			if(!comprobar(1, nuevo_nombre)) break;
			cout<<"Nombre invalido."<<endl;
		}

		while(getline(file, linea)){

			if(name == extraer(1, linea)){

				respaldo += nuevo_nombre + "|" + extraer(2, linea) + "|" + extraer(3, linea) + "\n";
				name = nuevo_nombre;
				continue;
			}
			respaldo += linea + "\n";
		}

	}else if(select == 2){

		while(true){

			cout<<"Introducir nueva clave: ";
			cin>>nueva_clave;
			if(nueva_clave.size() == 4) break;
			cout<<"Clave invalida."<<endl;
		}

		while(getline(file, linea)){

			if(name == extraer(1, linea)){

				respaldo += extraer(1, linea) + "|" + nueva_clave + "|" + extraer(3, linea) + "\n";
				pass = nueva_clave;
				continue;
			}
			respaldo += linea + "\n";
		}

	}else{
		cout<<"Opcion invalida."<<endl;
		return 0;
	}
	file.close();

	ofstream file2("registro.txt");
	file2<<respaldo;
	file2.close();

	return 0;
}

borrar(){

	string clave, confirm, respaldo, linea;
	ifstream file("registro.txt");

	cout<<".................... X Borrar cuenta X ....................\n";

	cout<<"Clave: ";
	cin>>clave;
	cout<<"Confirmar clave: ";
	cin>>confirm;

	if(clave == confirm && clave == pass){

		while(getline(file, linea)){

			if(name == extraer(1, linea)){

				cout<<"..........";
				continue;
			}
			respaldo += linea + "\n";
		}
		file.close();

		ofstream file2("registro.txt");
		file2<<respaldo;
		file2.close();

		name = "null"; pass = "null"; founds = 0.0;
	}else{

		cout<<"Clave invalida."<<endl;
	}

	return 0;
}

int crear(){

	cout<<"....................";
	cout<<"  @ Crear una Cuenta @  ";
	cout<<"....................";
	cout<<endl;
//exit(1);

	string respaldo, linea, cuenta_nueva, nombre, clave, sclav, conf, fondos;

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

		cout<<"Introduzca una clave de 4 digitos: ";
		cin>>clave;
		if(clave.size() != 4){

			cout<<"Clave invalida."<<endl;
			continue;
		}
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

		cout<<"...";
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

	cout<<"....................";
	cout<<"  # Iniciar sesion #  ";
	cout<<"....................";
	cout<<endl;

	string nombre, linea, clave;

//Nombre.
	cout<<"Nombre de usuario: ";
	cin>>nombre;
	if(!comprobar(1, nombre)){

		cout<<"Nombre invalido."<<endl;
		cout<<"...................."<<endl;
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
		cout<<"...................."<<endl;
		return 0;
	}

	cout<<"..........";
	name = nombre;
	cout<<"..........";
	pass = clave;
	cout<<"..........";
	founds = stof(extraer(3, linea));

	//cout<<endl<<"Usuario: "<<extraer(1, linea)<<endl;
	//cout<<"Clave: "<<extraer(2, linea)<<endl;
	//cout<<"Fondos: "<<extraer(3, linea)<<endl;

	menu_user_logged();

	return 0;
}

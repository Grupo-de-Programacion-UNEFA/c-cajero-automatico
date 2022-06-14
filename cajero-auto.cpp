#include <iostream>
#include <vector>
#include <string>
using namespace std;
//Vectores globales.
vector<string> cuentas={"0","2"};
vector<int> pass={0,1};

void agrandar(){
	cout<<"\nagrandar.\n";
	cuentas.resize(cuentas.size()+1);
	pass.resize(cuentas.size());
}

int crear(){
	int place,con1,con2;string name;
	//Se comprueba que no hayan espacios vacios.
	for(int i=0;i<=cuentas.size();i++){
		//se comprueba que el espacio i este vacio.
		if(cuentas[i].empty()==true){
			place=i;cout<<"Vacio\n";break;
		}
		//Se comprueba si es el ultimo ciclo antes de terminar el bucle.
		if(i==cuentas.size()){
			agrandar();place=cuentas.size()-1;
		}
	}
	//Nombre de usuario
	while(true){
	bool fin=false;
	cout<<"Introduzca un nombre de usuario: ";
	cin>>name;
	//Se comprueba que el nombre no se repita.
	for(int i=0;i<cuentas.size();i++){
		if(name==cuentas[i]){
			fin=false;
			cout<<"Nombre de usuario invalido."<<endl;break;
		}else{
			fin=true;
		}
	}
	if(fin)break;
	}
	//Contrasena
	while(true){
		cout<<"Introduzca una contrasena: ";
		cin>>con1;
		cout<<"Introduzca la contrasena nuevamente: ";
		cin>>con2;
		if(con1!=con2){
			cout<<"contrasena invalida."<<endl;
		}else{
			break;
		}
	}
	//Registro de datos.
	cuentas[place]=name;pass[place]=con1;
	cout<<"Cuenta creada exitosamente.\n";
	return 0;
}

int login(){
	string name;int slot=-1;int contra;
	cout<<"Nombre de usuario: ";
	//getline(cin, name);
	cin>>name;
	//Se comprueba que el nombre este registrado.
	for(int i=0;i<cuentas.size();i++){
		if(name==cuentas[i]){
			slot=i;;break;//Se registra el espacio y se termina el bucle.
		}
	}
	//Se comprueba que se haya encontrado el nombre en el registro.
	if(slot==-1){
		cout<<"NANI?!1";return 0;
	}
	cout<<"Contrasena: ";
	cin>>contra;
	//Se comprueba que contra sea igual a la contrasena del registro.
	if(contra==pass[slot]){
	cout<<"...";return 0;//"..." son un placeholder.
	}
	cout<<"NANI?!";
	return 0;
}
//es para comprobar los datos de los vectores.
void mayonesa(){
	/*for(int i=0;i<cuentas.size();i++){
		cout<<cuentas[i]<<"-"<<pass[i]<<endl;
	}*/
	cout<<cuentas.size()<<endl;
}

int main(){
	mayonesa();
	login();
	crear();
	mayonesa();
	login();
	crear();
	mayonesa();
	login();
	return 0;
}
/*Es la 3ra vez que hago esta mamada, no creo que sirva pero
hay que chambear.

Actualizacion: SI SIRVIO XDXDXD.

No usar vectores, 
Verificar la extracion de datos(3).*/
#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <stdlib.h>
using namespace std;
/*-----------------Administracion de Datos------------------*/
//////////////////////////NIVER///////////////////////////////

//Variables globales.
string username;int pass;

/*Lee una linea en especifico: 
dato es la posicion de la info a extraer;
liena es el texto de donde se sacara la info.*/
string extraer(int dato,string linea){
	cout<<"\tExtraer: "<<linea<<endl;
	//	Mas variables piteras.
	char letra;string info_a_devolver;int parte=1;
	//Pasar por cada letra de la linea.
	for(int i=0;i<linea.size();i++){
		//		Copiar la letra en la posicion i.
		letra=linea[i];
		// Comprobar fin del primer elemento.
		if(letra=='|'){
			switch(dato){
				case 1://Si se solicito el 1er dato.
					return info_a_devolver;
					
				case 2://Si se solicito el 2do.
					if(parte==2)return info_a_devolver;//Se comprueba si ya se pasi el 2do elemento.
					parte++;//Indica en que parte de la linea se encuentra.
					info_a_devolver="";//Borra los datos en el string.
					break;//Rompe el bucle.
					
				case 3://Si se solicito el 3ero.
					if(parte==2)return info_a_devolver;//Se comprueba si ya se paso el 3er elemento.
					parte++,info_a_devolver="";break;
					
				default:
					cout<<"Dato errado|funcion:extraer";exit(1);
			}
			//cout<<"|"<<parte<<"|"<<endl;
			continue;//Termina el ciclo y empieza otro.
		}
		if(parte==2)cout<<letra;
		info_a_devolver+=letra;//Se copia el dato letra por letra.
	}
	return "Algo salio mal, lmao.";
}

/*Comprueba si esta registrado un dato: 
dato es la posicion de la info;
nombre es la info que se buscara en el registro.*/
bool comprobar(int dato,string nombre){
	string linea,name;
	ifstream file("registro.txt");
	/*Explicacion larga de como funciona este bucle:
	la instruccion "getline" saca una linea completa(hasta
	el 1er salto de linea) de "file" y la almacena en "linea".
	La instruccion funciona con un iterador interno por lo cual
	le permite navegar por todo el documento(desde la 1er linea
	hasta la ultima). Cada vez que se inicia un ciclo nuevo(una nueva
	repeticion) la instruccion pasa a la siguiente linea y vuelve
	a copiarla y pegarla en el string indicado.*/
	while(getline(file,linea)){
		//Comprueba si la info solicitada se encuentra en "linea".
		name=extraer(dato,linea);
		//cout<<name<<"!comprobando"<<endl;
		if(nombre==name){//Si es cierto devuelve verdedaro.
			return true;
		}
	}
	return false;//Si no se encuentra nada, significa que no existe en el registro.
}

/*Crea una cuenta nueva:
crea un respando de la info guardada en registro.txt;
remplaza el .txt por un nuevo archivo con la info respaldada
previamente mas informacion nueva*/
int crear(){
	cout<<"\t@CREAR CUENTA@"<<endl;
	//	Crear pura variable pitera.
	string linea, texto, nombre;int clave=000,contra;float rial=0.1;
	
		//Ponerle datos a la monda.
	
	//nombre
	while(true){
		cout<<"Introduzca un nombre de usuario: ";
		cin>>nombre;
	//	Se comprueba que el nombre ingresado no se repita.
	//		Llama a la funcion comprobar cada vez que comprueba el parametro.
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
	//		Comprueba si la clave y su confirmacion coinciden.	
		if(contra==clave)break;//Si coinciden termina el bucle.
		cout<<"Clave invalida."<<endl;
	}
	
	//Monto inicial
	cout<<"Con cuanto dinero dese aperturar su cuenta?\nMonto: ";
	cin>>rial;
	//	Una broma cibernetica xDxDxD.
	if(rial==0)cout<<"Pss...Este lo que es un pelabolas."<<endl;
	
	//Leer archivo.
	
	ifstream file1("registro.txt");
	//	Se crea respaldo del archivo.
	while(getline(file1,linea)){
		texto+=linea+"\n";
	}
	//	Cerrar archivo.
	file1.close();
	
	//Escribir archivo.
	
	ofstream file2("registro.txt");
	//	Anadirle INFO al archivo.
	file2<<texto<<nombre<<"|"<<clave<<"|"<<rial<<"\n";
	//	Cerrar archivo.
	file2.close();
	
	return 0;
}

/*Iniciar sesion:
crompeuba que los valores ingreados esten registrados;
asigna los valores a variables globales.*/
int login(){
	cout<<"\t #INICIAR SESION#\n";
	//	Pinche variable.
	string nombre,clavechar;int clave;
	//Nombre
	cout<<"Nombre de usuario: ";
	cin>>nombre;
	//	Comprueba si el nombre NO se encuentra guardado en el registro.
	if(!comprobar(1,nombre)){
		cout<<"Nombre no encontrado."<<endl;return 0;
	}
	//Clave
	//	Permite equivocarse al momento de introducir la clave.
	while(true){
		cout<<"Clave: ";
		cin>>clave;
		clavechar=to_string(clave);//Transforma la clave a tipo string.
	//		Comprueba si la clave introducida coincide con la clave asociada al nombre de usuario que se encuentra duardado.
		if(comprobar(2,clavechar))break;
		cout<<"Clave invalida. Intente nuevamente"<<endl;
	}
	//Se asignan los valores ingresados a las variables globales.
	username=nombre;pass=clave;
	return 0;
}

/*Borra una cuenta:
Crea un respaldo de la info guardada en registro.txt,
omitiendo la cuenta activa(o sea, la correspondiente
a la sesion iniciada).

OJO: solo funciona si previamente se inicio sesion,
asi que no se debe llamar hasta que no lo hagan, sino
solo Dios sabe que puede ocurrir xD.*/
int borrar(){
	cout<<"\t!!BORRAR CUENTA!!\n";
	//	Variable pitera.
	string linea,texto,name;int con1,con2,i=0;
	
	cout<<"Introduzca la clave: ";
	cin>>con1;
	cout<<"Confirme la clave: ";
	cin>>con2;
	//	Comprueba si las claves introducidas coinciden con la clave del usuario activo.
	if(con1==con2&&con1==pass&&con2==pass){
	} else {
		cout<<"Clave invalida."<<endl;
		return 0;//Si se equivoca se termina la funcion.
	}
	//Actualizacion de datos.

	//	Se abre el archivo registro.txt solo para lectura.
	ifstream file("registro.txt");
	//	Extrae linea por linea desde registro.txt
	while(getline(file,linea)){
	//		Comprueba si el nombre de usuario en la linea coincide con el del usuario activo.
		name=extraer(1,linea);
	//		Si coincide NO CREA respaldo de esa linea en especifico.
		if(username==name&&i==0){
	//			Se asegura que ya no se pueda OBMITIR el respaldo de otra linea hasta que termine la funcion.
			i++;
		}else{
			texto+=linea+"\n";//Se crea respaldo de la linea.
		}
	}
	//	Se cierra el archivo.
	file.close();
	
	//Escribir codigo.

	//	Se remplaza el archivo registro.txt por uno con el mismo nombre xd.
	ofstream file2("registro.txt");
	//	Se guarda el respaldo en el nuevo archivo.
	file2<<texto;
	//	Se cierra el archivo.
	file2.close();
	return 0;
}

/*------------------Transacciones-------------------------------*/
////////////////////////SANTIAGO/////////////////////////////////

/*Actualiza los fondos:
Actualiza los fondos del usuario correspondiente
a la linea(solo puede añadir plata xddd)*/
string actualizar_fondos(string linea,float monto){
		cout<<"Procesando..."<<endl;
	//	Variable pitera.
	string nueva_linea;float monto1;
	//	Crea respaldo del nombre que esta en la linea.
	nueva_linea+=extraer(1,linea);nueva_linea+="|";
	//	Crea respaldo de la clave que esta en la linea.
	nueva_linea+=extraer(2,linea);nueva_linea+="|";
	cout<<".";
	//	Actualiza los fondos del usuario correspondiente a la linea.
	nueva_linea+=to_string(stof(extraer(3,linea))+monto);
	cout<<"...";
	//	Inserta un salto de linea al final de la linea(badan butz).
	nueva_linea+="\n";
	cout<<"done..."<<endl;
	//exit(1);
	//	Devuelve la linea con los fondos actualizados.
	return nueva_linea;
}
	/*Tranferencia:
	Actualiza los fondos de las cuentas.
	Actualiza registro.txt con los fondos nuevos

	OJO: hay una vaina pendiente por acá, no sexD.*/
int transferir(){
	cout<<"Preparando tranferencia..."<<endl;
	//	Variable pitera.
	string cuenta_destino,linea,texto;int clave;float monto;
	cout<<"Nombre de la cuenta final: ";
	cin>>cuenta_destino;
	//	Comprueba si la cuenta destino, NO existe en el registro.
	if(!comprobar(1,cuenta_destino))return 0;
	cout<<"Monto a tranferir: ";
	cin>>monto;
	
	/*Vaina pendiente:
	Hay que hacer una comprobacion de fondos para evitar que 
	se deposite mas dinero del que se tiene registrado*/
	
	cout<<"Clave: ";
	cin>>clave;
	//	Comprueba si la clave introducida NO coincide con la clave del usuario activo,
	if(clave!=pass)return 0;
	
	//Actualizacion de cuentas.

	//	Se abre registro.txt, solo para lectura.
	ifstream file("registro.txt");
	//	Se extrae una linea de registro.txt
	while(getline(file,linea)){
	//		Comprueba si la linea correponde a la del usuario con el nombre de cuenta_destino.
		if(cuenta_destino==extraer(1,linea)){
	//			Se llama a trans y se almacena lo que devuelve.
			texto+=actualizar_fondos(linea,monto);
	//			Finaliza el ciclo e inicia uno nuevo.
			continue;
		}
	//		Comepruba si la linea corresponde al usuario activo.
		if(username==extraer(1,linea)){
	//			Se actualizan los datos del usuario activo(se restan sus fondos actuales con el monto).
	cout<<"|"<<extraer(3,linea)<<"|"<<monto-stof(extraer(3,linea));exit(1);
			texto+=username+"|"+to_string(pass)+"|"+to_string(monto-stof(extraer(3,linea)))+"\n";
	//		Comepruba si la linea corresponde al usuario activo.
			continue;
		}
	//		Se crea un respaldo de la linea.
		texto+=linea+"\n";
		
	}
	//	Se cierra el archivo.
	file.close();
	
	//Actualizacion de los datos guardados.

	//	Se remplaza regitro.txt por un archivo con el mismo nombre.
	ofstream file2("registro.txt");
	//	Se guarda "texto" en registro.txt
	file2<<texto;
	//	Se cierra el archivo.
	file2.close();
	
	return 0;
}

/*---------------------------Menus--------------------------------*/
/*---(o menuses, realmente no se como se el plural de menu xd).---*/

int main(){
	crear();
	login();
	cout<<"\tNombre de usuario: "<<username<<endl<<"\tClave: "<<to_string(pass)<<endl;
	transferir();
	//borrar();
	return 0;
}
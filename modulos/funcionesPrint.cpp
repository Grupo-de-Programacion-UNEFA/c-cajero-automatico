/*
   ------------------------------------
   Definicion de funciones de Impresion
   ------------------------------------
*/

#include "funciones.h"
int menu_user_logged(){

	string frase; int select;

	if(name == "null" && pass == "null") return 0;

	frase += "1) Depositar dinero.\n";
	frase += "2) Sacar dinero.\n";
	frase += "3) Transferir dinero.\n";
	frase += "4) Actualizar datos.\n";
	frase += "5) Borrar cuenta.\n";
	frase += "6) Cerrar sesion.\n";

	while(true){

		cout<<"....................";
		cout<<endl<<"Usuario: "<<name<<endl<<"Clave: "<<pass<<endl;
		cout<<"Fondos: "<<founds<<endl;

		cout<<"....................";
		cout<<endl;
		cout<<frase;
		cin>>select;

		switch(select){

			case 1://Depositar dinero.
				mete_saca(true); break;

			case 2://Sacar dinero.
				mete_saca(false); break;

			case 3://Transferir dinero a otra cuenta.
				transferir(); break;

			case 4://Cambiar datos.
				actualizar(); break;

			case 5://Borrar cuenta.
				borrar(); return 0;

			case 6:
				name = "";
				pass = "";
				return 0;

			default:
				cout<<"Opcion invalida, subnormal."<<endl;
		}
	}
}

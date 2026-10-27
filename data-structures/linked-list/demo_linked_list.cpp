#include <iostream>

using namespace std;

#include "LinkedList.h"

int main() {
	cout << "Pruebas para lista encadenada" << endl;
	cout << "----------" << endl;
	LinkedList<string> lista;
	lista.addLast("HOLA");
	lista.addLast("CRAYOLA");
	lista.addFirst("AQUI");
	lista.addLast("ESTOY");
	lista.print(); // AQUI HOLA CRAYOLA ESTOY
	cout << "----------" << endl;
	lista.add("MTY", 1);
	lista.print(); // AQUI MTY HOLA CRAYOLA ESTOY
	cout << "----------" << endl;
	lista.del(2);
	lista.print(); // AQUI MTY CRAYOLA ESTOY
	cout << "----------" << endl;
	cout << "Size = " << lista.getSize() << endl; // Size = 4
	cout << "----------" << endl;
	lista.deleteFirst();
	lista.print(); // MTY CRAYOLA ESTOY
	cout << "----------" << endl;
	lista.addFirst("TC1031");
	lista.deleteLast();
	lista.print(); // TC1031 MTY CRAYOLA
	cout << "----------" << endl;
	lista.addLast("ESTRUCTURA");
	lista.addLast("DATOS");
	cout << "Dato en pos 2 es " << lista.get(2) << endl; // Dato en pos 2 es CRAYOLA
	cout << "----------" << endl;
	cout << "Dato en pos 2 era " << lista.set("LUNA", 2) << endl; // Dato en pos 2 era CRAYOLA
	cout << "----------" << endl;
	lista.print(); // TC1031 MTY LUNA ESTRUCTURA DATOS
	cout << "----------" << endl;
	lista.change(1, 3);
	lista.print(); // TC1031 ESTRUCTURA LUNA MTY DATOS
	cout << "----------" << endl;
	lista.deleteAll();
	lista.addLast("UNO");
	lista.addLast("DOS");
	lista.print(); // UNO DOS
	cout << "----------" << endl;

	// Actividad 2.1
	cout << "Pruebas para actividad 2.1" << endl;
	cout << "----------" << endl;
	lista.addLast("TRES");
	lista.addLast("CUATRO");
	lista.reverse();
	lista.print(); // CUATRO TRES DOS UNO
	cout << "----------" << endl;
	lista.shift(2);
	lista.print(); // DOS UNO CUATRO TRES
	cout << "----------" << endl;
	lista.shift(-3);
	lista.print(); // TRES DOS UNO CUATRO
	cout << "----------" << endl;
	LinkedList<string> lista2;
	lista2.addLast("TRES");
	lista2.addLast("DOS");
	lista2.addLast("UNO");
	lista2.addLast("CUATRO");
	if (lista == lista2) // IGUALES
		cout << "IGUALES" << endl;
	else
		cout << "DISTINTAS" << endl;
	cout << "----------" << endl;
	lista2.set("CINCO", 3);
	if (lista == lista2) // DISTINTAS
		cout << "IGUALES" << endl;
	else
		cout << "DISTINTAS" << endl;
	cout << "----------" << endl;

	// Actividad 2.2
	cout << "Pruebas para actividad 2.2" << endl;
	cout << "----------" << endl;
	LinkedList<string> lista3(lista2);
	lista3.deleteFirst();
	lista2.print(); // TRES DOS UNO CINCO
	cout << "----------" << endl;
	lista3.print(); // DOS UNO CINCO
	cout << "----------" << endl;
	LinkedList<string> lista4;
	lista4 = lista3;
	lista4.deleteFirst();
	lista3.print(); // DOS UNO CINCO
	cout << "----------" << endl;
	lista4.print(); // UNO CINCO
	cout << "----------" << endl;
	lista4 += lista3;
	lista4.print(); // UNO CINCO DOS UNO CINCO

	return 0;
}
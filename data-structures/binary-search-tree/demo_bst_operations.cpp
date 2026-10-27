// Aplicación de prueba de los métodos de la actividad 3.2
#include <iostream>

using namespace std;

#include "BST.h"

int main()
{
    BST miArbol;

    cout << "El arbol tiene: " << miArbol.getSize() << " nodos" << endl; // El arbol tiene: 0 nodos
    cout << "Ancho mayor del BST: " << miArbol.maxWidth() << endl;       // Ancho mayor del BST: 0
    miArbol.add(8);
    miArbol.add(15);
    miArbol.add(21);
    cout << "Ancho mayor del BST: " << miArbol.maxWidth() << endl; // Ancho mayor del BST: 1
    miArbol.add(40);
    miArbol.add(7);
    miArbol.add(18);
    miArbol.add(9);
    miArbol.add(5);
    miArbol.add(2);
    miArbol.add(1);
    miArbol.add(4);
    miArbol.add(11);
    miArbol.add(6);
    cout << "El arbol tiene: " << miArbol.getSize() << " nodos" << endl; // El arbol tiene: 13 nodos
    cout << "Ancho mayor del BST: " << miArbol.maxWidth() << endl;    // Ancho mayor del BST: 5
    miArbol.print(preorder);      // Recorrido en preorden: 8 7 5 2 1 4 6 15 9 11 21 18 40
    miArbol.print(inorder);       // Recorrido en inorden: 1 2 4 5 6 7 8 9 11 15 18 21 40
    miArbol.print(postorder);     // Recorrido en postorden: 1 4 2 6 5 7 11 9 18 40 21 15 8
    cout << "Pariente mas cercano de 1 y 6: " << miArbol.nearestRelative(1, 6) << endl;     // Pariente mas cercano de 1 y 6: 5
    cout << "Pariente mas cercano de 11 y 40: " << miArbol.nearestRelative(11, 40) << endl; // Pariente mas cercano de 11 y 40: 15
    cout << "Pariente mas cercano de 11 y 8: " << miArbol.nearestRelative(11, 8) << endl;   // Pariente mas cercano de 11 y 8: 8
    cout << "Pariente mas cercano de 21 y 21: " << miArbol.nearestRelative(21, 21) << endl;   // Pariente mas cercano de 21 y 21: 21
    BST arbol2(miArbol);
    arbol2.print(preorder);      // Recorrido en preorden: 8 7 5 2 1 4 6 15 9 11 21 18 40
    if (miArbol == arbol2)
        cout << "ARBOLES IGUALES" << endl;
    else
        cout << "ARBOLES DIFERENTES" << endl; // ARBOLES IGUALES
    arbol2.remove(9);
    if (miArbol == arbol2)
        cout << "ARBOLES IGUALES" << endl;
    else
        cout << "ARBOLES DIFERENTES" << endl; // ARBOLES DIFERENTES
    miArbol.remove(9);
    if (miArbol == arbol2)
        cout << "ARBOLES IGUALES" << endl;
    else
        cout << "ARBOLES DIFERENTES" << endl; // ARBOLES IGUALES

    return 0;
}
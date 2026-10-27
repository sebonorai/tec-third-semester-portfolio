// Aplicación de prueba de los métodos de la actividad 3.1
#include <iostream>

using namespace std;

#include "BST.h"

int main()
{
    BST miArbol;

    cout << "El arbol tiene: " << miArbol.getSize() << " nodos" << endl; // El arbol tiene: 0 nodos
    cout << "Altura del BST: " << miArbol.height() << endl;           // Altura del BST: 0
    miArbol.add(8);
    miArbol.add(15);
    miArbol.add(21);
    cout << "Altura del BST: " << miArbol.height() << endl; // Altura del BST: 3
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
    cout << "Altura del BST: " << miArbol.height() << endl;           // Altura del BST: 5
    miArbol.print(preorder);      // Recorrido en preorden: 8 7 5 2 1 4 6 15 9 11 21 18 40
    miArbol.print(inorder);       // Recorrido en entreorden: 1 2 4 5 6 7 8 9 11 15 18 21 40
    miArbol.print(postorder);     // Recorrido en postorden: 1 4 2 6 5 7 11 9 18 40 21 15 8
    miArbol.print(levelbylevel);  // Recorrido nivel x nivel: 8 7 15 5 9 21 2 6 11 18 40 1 4
    cout << "Ancestros de 100: ";
    miArbol.ancestors(100);       // Ancestros de 100: DATO INEXISTENTE
    cout << "Ancestros de 8: ";
    miArbol.ancestors(8);         // Ancestros de 8: SIN ANCESTROS
    cout << "Ancestros de 4: ";
    miArbol.ancestors(4);         // Ancestros de 4: 2 5 7 8
    cout << "Ancestros de 11: ";
    miArbol.ancestors(11);        // Ancestros de 11: 9 15 8
    cout << "Nivel de 100: " << miArbol.whatLevelAmI(100) << endl; // Nivel del 100: -1
    cout << "Nivel de 8: " << miArbol.whatLevelAmI(8) << endl; // Nivel del 8: 0
    cout << "Nivel de 9: " << miArbol.whatLevelAmI(9) << endl; // Nivel del 9: 2
    cout << "Nivel de 4: " << miArbol.whatLevelAmI(4) << endl; // Nivel del 4: 4
 
    return 0;
}
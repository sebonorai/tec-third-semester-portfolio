// Implementa el ADT BST para arboles binarios de busqueda
// Nombre: Sebastian Noriega Olavarrieta
// Fecha: 22/10/2026 (Actividad 3.2: se agregan maxWidth, nearestRelative, constructor de copia, operator== y remove)
// En la documentación: n es el número de nodos y h es la altura del árbol
// (h es cercana a log n si el árbol está balanceado y llega a n si es una cadena).

#ifndef BST_H
#define BST_H

#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include "NodeT.h"
using namespace std;

enum Traversal { preorder, inorder, postorder, levelbylevel };

class BST{
    public:
        BST(); // Constructor que inicializa el arbol con root en nullptr y size en 0
        BST(const BST &other); // Constructor de copia: crea un clon del arbol recibido, en datos y en forma
        ~BST(); // Destructor que libera la memoria de todos los nodos del arbol
        bool search(int data) const; // Busca un valor en el arbol y devuelve true si lo encuentra, false en caso contrario
        void add(int data); // Agrega un nuevo nodo con el valor especificado al arbol
        void remove(int data); // Elimina el nodo con el valor especificado del arbol
        bool isEmpty() const; // Devuelve true si el arbol esta vacio, false en caso contrario
        int getSize() const; // Devuelve el numero de nodos en el arbol
        void print() const; // Imprime el arbol
        int height() const; // Devuelve la altura del arbol
        int whatLevelAmI(int data) const; // Devuelve el nivel del nodo con el valor especificado, o -1 si no se encuentra en el arbol
        void print(Traversal type) const; // Imprime el arbol en el orden especificado (preorder, inorder, postorder, levelbylevel)
        void ancestors(int data) const; // Imprime los ancestros de un dato, o un mensaje si no existe o es la raiz
        int maxWidth() const; // Devuelve el numero de nodos del nivel que tiene mas nodos
        int nearestRelative(int a, int b) const; // Devuelve el ancestro comun mas cercano de dos datos
        bool operator==(const BST &other) const; // Compara dos arboles, tanto en datos como en forma
        
    private:
        NodeT *root;
        int size;
        // metodos auxiliares
        void deleteTree(NodeT *tree); // Elimina todos los nodos del arbol a partir del nodo especificado
        void printTree(NodeT *tree) const; // Imprime el arbol a partir del nodo especificado
        int heightTree(NodeT *tree) const; // Devuelve la altura del arbol a partir del nodo especificado
        void preOrder(NodeT *tree) const; // Recorre el arbol en preorden a partir del nodo especificado
        void inOrder(NodeT *tree) const; // Recorre el arbol en inorden a partir del nodo especificado
        void postOrder(NodeT *tree) const; // Recorre el arbol en postorden a partir del nodo especificado
        void levelByLevel() const; // Recorre el arbol nivel por nivel
        NodeT* copyTree(NodeT *tree) const; // Crea una copia de todos los nodos a partir del nodo especificado
        bool equalTrees(NodeT *a, NodeT *b) const; // Compara dos subarboles en datos y en forma

};

/*
 * Constructor
 * Descripción: Crea un árbol vacío.
 * Entrada: Nada.
 * Salida: Nada.
 * Precondición: Ninguna.
 * Postcondición: root es nullptr y size es 0.
 * Complejidad: O(1), solo asigna dos variables.
 */
BST::BST(){
    root = nullptr;
    size = 0;
}
/*
 * Constructor de copia
 * Descripción: Construye un árbol que es un clon del árbol recibido, tanto en datos como en forma. Los nodos son nuevos (copia profunda), así que modificar uno no afecta al otro.
 * Entrada: El BST del que se copiarán los datos.
 * Salida: Nada.
 * Precondición: El BST recibido está instanciado. Puede estar vacío.
 * Postcondición: El nuevo árbol tiene los mismos datos, la misma forma y el mismo size que el recibido; el recibido no cambia.
 * Complejidad: O(n), copyTree visita cada nodo una vez y crea un nodo nuevo por cada uno.
 */
BST::BST(const BST &other){
    root = copyTree(other.root);
    size = other.size;
}
/*
 * Destructor
 * Descripción: Libera la memoria de todos los nodos del árbol.
 * Entrada: Nada.
 * Salida: Nada.
 * Precondición: Ninguna.
 * Postcondición: No quedan nodos en memoria.
 * Complejidad: O(n), deleteTree visita cada nodo una vez.
 */
BST::~BST(){
    deleteTree(root);
}
/*
 * search
 * Descripción: Busca un dato en el árbol bajando por una sola rama.
 * Entrada: El dato a buscar.
 * Salida: true si el dato está en el árbol, false si no.
 * Precondición: El BST está instanciado. Puede estar vacío.
 * Postcondición: El árbol no cambia.
 * Complejidad: O(h), en cada paso baja un nivel. Mejor caso O(1) (el dato es la raíz); peor caso O(n) si el árbol es una cadena.
 */
bool BST::search(int data) const{
    if (root == nullptr) {
        return false;
    }
    else{
        NodeT *aux = root;
        while (aux != nullptr){
            if (data == aux->getData()){
                return true;
            }
            aux = (data < aux->getData()) ? aux->getLeft() : aux->getRight();
            
        }
        return false;
    }
}

/*
 * add
 * Descripción: Agrega un dato al árbol como hoja, respetando que los menores van a la izquierda y los mayores a la derecha. Si el dato ya existe, no lo agrega.
 * Entrada: El dato a agregar.
 * Salida: Nada.
 * Precondición: El BST está instanciado. Puede estar vacío.
 * Postcondición: Si el dato no existía, queda en el árbol y size aumenta en 1; si ya existía, el árbol no cambia.
 * Complejidad: O(h), search y el recorrido hasta el hueco bajan por una sola rama.
 */
void BST::add(int data){
    if (search(data)) {
        return; // ya existe, no se agrega
    }
    NodeT *nuevo = new NodeT(data);
    if (root == nullptr) {
        root = nuevo;
    }
    else {
        NodeT *aux = root;
        while (true) {
            if (data < aux->getData()) {
                if (aux->getLeft() == nullptr) {
                    aux->setLeft(nuevo);
                    break;
                } else {
                    aux = aux->getLeft();
                }
            } else {
                if (aux->getRight() == nullptr) {
                    aux->setRight(nuevo);
                    break;
                } else {
                    aux = aux->getRight();
                }
            }
        }
    }
    size++;
}
/*
 * remove
 * Descripción: Elimina un dato del árbol. Si el nodo es hoja o tiene un solo hijo, el padre se conecta directo con ese hijo. Si tiene dos hijos, se copia en él el sucesor (el menor del subárbol derecho) y se elimina el nodo del sucesor. Si el dato no existe no hace nada.
 * Entrada: El dato a eliminar.
 * Salida: Nada.
 * Precondición: El BST está instanciado. Puede estar vacío.
 * Postcondición: Si el dato existía, ya no está en el árbol, size disminuye en 1 y el árbol sigue siendo un BST; si no existía, el árbol no cambia.
 * Complejidad: O(h), una bajada para encontrar el nodo y, si tiene dos hijos, otra bajada para encontrar el sucesor. Peor caso O(n) si el árbol es una cadena.
 */
void BST::remove(int data){
    NodeT *padre = nullptr;
    NodeT *actual = root;
    while (actual != nullptr && actual->getData() != data) {   // busca el nodo y recuerda a su padre
        padre = actual;
        actual = (data < actual->getData()) ? actual->getLeft() : actual->getRight();
    }
    if (actual == nullptr) {
        return; // el dato no existe
    }
    if (actual->getLeft() != nullptr && actual->getRight() != nullptr) {
        // Dos hijos: busca el sucesor (el menor de la derecha)
        NodeT *padreSucesor = actual;
        NodeT *sucesor = actual->getRight();
        while (sucesor->getLeft() != nullptr) {
            padreSucesor = sucesor;
            sucesor = sucesor->getLeft();
        }
        actual->setData(sucesor->getData()); // el dato del sucesor sustituye al eliminado
        padre = padreSucesor;                // ahora se elimina el nodo del sucesor
        actual = sucesor;                    // (tiene a lo mucho un hijo derecho)
    }
    NodeT *hijo = (actual->getLeft() != nullptr) ? actual->getLeft() : actual->getRight();
    if (padre == nullptr) {
        root = hijo;                 // se eliminó la raíz
    } else if (padre->getLeft() == actual) {
        padre->setLeft(hijo);
    } else {
        padre->setRight(hijo);
    }
    delete actual;
    size--;
}
/*
 * isEmpty
 * Descripción: Indica si el árbol no tiene nodos.
 * Entrada: Nada.
 * Salida: true si está vacío, false si no.
 * Precondición: El BST está instanciado.
 * Postcondición: El árbol no cambia.
 * Complejidad: O(1), solo compara size con 0.
 */
bool BST::isEmpty() const {
    return size == 0;
}
/*
 * getSize
 * Descripción: Obtiene la cantidad de nodos del árbol.
 * Entrada: Nada.
 * Salida: El número de nodos.
 * Precondición: El BST está instanciado.
 * Postcondición: El árbol no cambia.
 * Complejidad: O(1), regresa el atributo size.
 */
int BST::getSize() const{
    return size;
}
/*
 * print (sin parámetros)
 * Descripción: Imprime el árbol en preorden, un dato por línea, o un mensaje si está vacío.
 * Entrada: Nada.
 * Salida: Nada (imprime en pantalla).
 * Precondición: El BST está instanciado. Puede estar vacío.
 * Postcondición: El árbol no cambia.
 * Complejidad: O(n), printTree visita cada nodo una vez.
 */
void BST::print() const{
    if (root == nullptr){
        cout << "El arbol esta vacio" << endl;
    }
    else{
        printTree(root);
    }
}

/*
 * whatLevelAmI
 * Descripción: Calcula en qué nivel está un dato. La raíz es el nivel 0.
 * Entrada: El dato del que se quiere conocer el nivel.
 * Salida: El nivel del dato, o -1 si no está en el árbol.
 * Precondición: El BST está instanciado. Puede estar vacío.
 * Postcondición: El árbol no cambia.
 * Complejidad: O(h), baja por una sola rama contando niveles. Peor caso O(n) si el árbol es una cadena.
 */
int BST::whatLevelAmI(int data) const {
    NodeT *aux = root;
    int nivel = 0;  
    while (aux != nullptr) {
        if (data == aux->getData()) {
            return nivel; 
        }
        aux = (data < aux->getData()) ? aux->getLeft() : aux->getRight();
        nivel++;  
    }
    return -1;   
}

/* funciones auxiliares */
/*
 * deleteTree (auxiliar)
 * Descripción: Elimina todos los nodos a partir del nodo indicado, hijos primero y luego el nodo (recorrido postorden).
 * Entrada: El nodo desde el cual se elimina.
 * Salida: Nada.
 * Precondición: Ninguna, si el nodo es nullptr no hace nada.
 * Postcondición: Todos los nodos de ese subárbol quedan liberados.
 * Complejidad: O(n), visita cada nodo una vez.
 */
void BST::deleteTree(NodeT *tree){
    if(tree == nullptr){
        return;
    }
    deleteTree(tree->getLeft());
    deleteTree(tree->getRight());
    delete tree;
}

/*
 * printTree (auxiliar)
 * Descripción: Imprime un dato por línea a partir del nodo indicado, en preorden.
 * Entrada: El nodo desde el cual se imprime.
 * Salida: Nada (imprime en pantalla).
 * Precondición: Ninguna, si el nodo es nullptr no hace nada.
 * Postcondición: El árbol no cambia.
 * Complejidad: O(n), visita cada nodo una vez.
 */
void BST::printTree(NodeT *tree) const{
    if(tree == nullptr){
        return;
    }
    cout << " " << tree->getData() << endl;
    printTree(tree->getLeft());
    printTree(tree->getRight());

}

/*
 * height
 * Descripción: Calcula la altura del árbol, es decir, el número de niveles.
 * Entrada: Nada.
 * Salida: Un entero con la altura (0 si el árbol está vacío).
 * Precondición: El BST está instanciado. Puede estar vacío.
 * Postcondición: El árbol no cambia.
 * Complejidad: O(n), heightTree visita cada nodo una vez.
 */
int BST::height() const {
    return heightTree(root);
}

/*
 * heightTree (auxiliar)
 * Descripción: Calcula la altura del subárbol que empieza en el nodo indicado: 1 más la altura del hijo más alto. Un subárbol vacío vale 0.
 * Entrada: El nodo raíz del subárbol.
 * Salida: La altura del subárbol.
 * Precondición: Ninguna, si el nodo es nullptr regresa 0.
 * Postcondición: El árbol no cambia.
 * Complejidad: O(n), una llamada recursiva por cada nodo.
 */
int BST::heightTree(NodeT *tree) const {
    if (tree == nullptr) {
        return 0;
    }
    int izq = heightTree(tree->getLeft()); 
    int der = heightTree(tree->getRight()); 
    return max(izq, der) + 1;  
}

/*
 * print (con recorrido)
 * Descripción: Imprime todos los datos del árbol en el orden que indique el parámetro: preorden, entreorden, postorden o nivel por nivel.
 * Entrada: Un valor del enumerado Traversal.
 * Salida: Nada (imprime en pantalla).
 * Precondición: El BST está instanciado. Puede estar vacío.
 * Postcondición: El árbol no cambia.
 * Complejidad: O(n), llama a un solo recorrido que visita cada nodo una vez.
 */
void BST::print(Traversal type) const {
    switch (type) {
        case preorder:
            cout << "Recorrido en preorden: ";
            preOrder(root);
            cout << endl;
            break;
        case inorder:
            cout << "Recorrido en entreorden: ";
            inOrder(root);
            cout << endl;
            break;
        case postorder:
            cout << "Recorrido en postorden: ";
            postOrder(root);
            cout << endl;
            break;
        case levelbylevel:
             cout << "Recorrido nivel x nivel: ";
             levelByLevel(); // 1. llama a levelByLevel()
             cout << endl; // 2. imprime endl
             break;
        default:
            break; 
    }
}

/*
 * preOrder (auxiliar)
 * Descripción: Recorre el subárbol en preorden: primero el nodo, luego el hijo izquierdo y luego el derecho.
 * Entrada: El nodo desde el cual se recorre.
 * Salida: Nada (imprime en pantalla).
 * Precondición: Ninguna, si el nodo es nullptr no hace nada.
 * Postcondición: El árbol no cambia.
 * Complejidad: O(n), visita cada nodo una vez.
 */
void BST::preOrder(NodeT *tree) const {
    if (tree == nullptr) {
        return;
    }
    cout << tree->getData() << " "; // 1. imprime el dato seguido de un espacio (sin endl)
    preOrder(tree->getLeft());     // 2. llama a preOrder con el hijo izquierdo
    preOrder(tree->getRight());    // 3. llama a preOrder con el hijo derecho
}

/*
 * inOrder (auxiliar)
 * Descripción: Recorre el subárbol en entreorden: hijo izquierdo, luego el nodo y luego el derecho. Imprime los datos de menor a mayor.
 * Entrada: El nodo desde el cual se recorre.
 * Salida: Nada (imprime en pantalla).
 * Precondición: Ninguna, si el nodo es nullptr no hace nada.
 * Postcondición: El árbol no cambia.
 * Complejidad: O(n), visita cada nodo una vez.
 */
void BST::inOrder(NodeT *tree) const {
    if (tree == nullptr) {
        return;
    }
    inOrder(tree->getLeft());      // 1. llama a inOrder con el hijo izquierdo
    cout << tree->getData() << " "; // 2. imprime el dato seguido de un espacio (sin endl)
    inOrder(tree->getRight());     // 3. llama a inOrder con el hijo derecho
}

/*
 * postOrder (auxiliar)
 * Descripción: Recorre el subárbol en postorden: hijo izquierdo, hijo derecho y al final el nodo.
 * Entrada: El nodo desde el cual se recorre.
 * Salida: Nada (imprime en pantalla).
 * Precondición: Ninguna, si el nodo es nullptr no hace nada.
 * Postcondición: El árbol no cambia.
 * Complejidad: O(n), visita cada nodo una vez.
 */
void BST::postOrder(NodeT *tree) const {
    if (tree == nullptr) {
        return;
    }
    postOrder(tree->getLeft());     // 1. llama a postOrder con el hijo izquierdo
    postOrder(tree->getRight());    // 2. llama a postOrder con el hijo derecho
    cout << tree->getData() << " "; // 3. imprime el dato seguido de un espacio (sin endl)
}

/*
 * levelByLevel (auxiliar)
 * Descripción: Recorre el árbol nivel por nivel, de arriba hacia abajo y de izquierda a derecha, usando una fila (queue).
 * Entrada: Nada.
 * Salida: Nada (imprime en pantalla).
 * Precondición: El BST está instanciado. Puede estar vacío.
 * Postcondición: El árbol no cambia.
 * Complejidad: O(n), cada nodo entra y sale de la fila una vez.
 */
void BST::levelByLevel() const {
    if (root == nullptr) {
        return;
    }
    queue<NodeT*> fila;
    fila.push(root);
    while (!fila.empty()) {
        NodeT *actual = fila.front();   // miro al primero de la fila
        fila.pop();                     // lo saco
        cout << actual->getData() << " ";
        if (actual->getLeft() != nullptr) {
            fila.push(actual->getLeft());
        }
        if (actual->getRight() != nullptr) {
            fila.push(actual->getRight());
        }
    }
}

/*
 * ancestors
 * Descripción: Imprime los ancestros de un dato, del más cercano (su padre) al más lejano (la raíz). Si el dato no existe imprime DATO INEXISTENTE y si es la raíz imprime SIN ANCESTROS.
 * Entrada: El dato del que se quieren conocer los ancestros.
 * Salida: Nada (imprime en pantalla).
 * Precondición: El BST está instanciado. Puede estar vacío.
 * Postcondición: El árbol no cambia.
 * Complejidad: O(h), search baja una rama, luego se baja otra vez guardando los ancestros en una pila y se vacía la pila. Peor caso O(n) si el árbol es una cadena.
 */
void BST::ancestors(int data) const {
    if (!search(data)) {
        cout << "DATO INEXISTENTE" << endl;
        return;
    }
    if (data == root->getData()) {
        cout << "SIN ANCESTROS" << endl;
        return;
    }
    stack<int> pila;
    NodeT *aux = root;
    while (aux->getData() != data) {
        pila.push(aux->getData());
        aux = (data < aux->getData()) ? aux->getLeft() : aux->getRight();
    }
    while (!pila.empty()) {
        cout << pila.top() << " ";
        pila.pop();
    }
    cout << endl;
}

/*
 * maxWidth
 * Descripción: Calcula la anchura máxima del árbol, es decir, el mayor número de nodos que hay en un mismo nivel. Recorre el árbol nivel por nivel con una fila (queue) y en cada nivel cuenta cuántos nodos hay.
 * Entrada: Nada.
 * Salida: Un entero con la máxima anchura (0 si el árbol está vacío).
 * Precondición: El BST está instanciado. Puede estar vacío.
 * Postcondición: El árbol no cambia.
 * Complejidad: O(n), cada nodo entra y sale de la fila una vez. Espacio extra O(n) en el peor caso (la fila).
 */
int BST::maxWidth() const {
    if (root == nullptr) {
        return 0;
    }
    int maximo = 0;
    queue<NodeT*> fila;
    fila.push(root);
    while (!fila.empty()) {
        int enNivel = fila.size();      // cuántos nodos tiene el nivel actual
        maximo = max(maximo, enNivel);
        for (int i = 0; i < enNivel; i++) {   // se procesa todo el nivel y se meten sus hijos
            NodeT *actual = fila.front();
            fila.pop();
            if (actual->getLeft() != nullptr) {
                fila.push(actual->getLeft());
            }
            if (actual->getRight() != nullptr) {
                fila.push(actual->getRight());
            }
        }
    }
    return maximo;
}

/*
 * nearestRelative
 * Descripción: Regresa el ancestro común más cercano de dos datos. Baja desde la raíz: mientras los dos datos sean menores que el nodo actual se va a la izquierda, mientras los dos sean mayores se va a la derecha; el primer nodo donde se separan (o donde uno de ellos es el nodo) es la respuesta. Un dato cuenta como ancestro de sí mismo.
 * Entrada: Los dos datos a los que se les busca el ancestro.
 * Salida: El ancestro común más cercano, o -1 si alguno de los datos no está en el árbol.
 * Precondición: El BST está instanciado y los dos datos están en el árbol.
 * Postcondición: El árbol no cambia.
 * Complejidad: O(h), dos search y una sola bajada por el árbol. Peor caso O(n) si el árbol es una cadena.
 */
int BST::nearestRelative(int a, int b) const {
    if (!search(a) || !search(b)) {
        return -1; // protección: no cumple la precondición
    }
    NodeT *aux = root;
    while (aux != nullptr) {
        if (a < aux->getData() && b < aux->getData()) {
            aux = aux->getLeft();
        } else if (a > aux->getData() && b > aux->getData()) {
            aux = aux->getRight();
        } else {
            return aux->getData(); // aquí se separan (o uno de ellos es este nodo)
        }
    }
    return -1;
}

/*
 * operator==
 * Descripción: Compara dos árboles: son iguales solo si tienen los mismos datos y la misma forma.
 * Entrada: El BST con el que se compara el original.
 * Salida: true si son iguales, false si no.
 * Precondición: Ambos BST están instanciados. Pueden estar vacíos.
 * Postcondición: Ninguna, los árboles no cambian.
 * Complejidad: O(n) en el peor caso (árboles iguales, se visitan todos los nodos); si los tamaños son distintos termina en O(1).
 */
bool BST::operator==(const BST &other) const {
    if (size != other.size) {
        return false; // con distinto número de nodos no pueden ser iguales
    }
    return equalTrees(root, other.root);
}

/*
 * copyTree (auxiliar)
 * Descripción: Crea una copia de un subárbol: copia el nodo y luego, recursivamente, sus hijos izquierdo y derecho (recorrido preorden).
 * Entrada: El nodo raíz del subárbol a copiar.
 * Salida: Apuntador a la raíz de la copia (nullptr si el subárbol está vacío).
 * Precondición: Ninguna, si el nodo es nullptr regresa nullptr.
 * Postcondición: El árbol original no cambia.
 * Complejidad: O(n), una llamada y un nodo nuevo por cada nodo del subárbol.
 */
NodeT* BST::copyTree(NodeT *tree) const {
    if (tree == nullptr) {
        return nullptr;
    }
    NodeT *nuevo = new NodeT(tree->getData());
    nuevo->setLeft(copyTree(tree->getLeft()));
    nuevo->setRight(copyTree(tree->getRight()));
    return nuevo;
}

/*
 * equalTrees (auxiliar)
 * Descripción: Compara dos subárboles al mismo tiempo: los dos vacíos son iguales; si solo uno está vacío o los datos difieren son distintos; si no, deben ser iguales sus hijos izquierdos y sus hijos derechos.
 * Entrada: Las raíces de los dos subárboles a comparar.
 * Salida: true si son iguales en datos y en forma, false si no.
 * Precondición: Ninguna, acepta nullptr.
 * Postcondición: Los árboles no cambian.
 * Complejidad: O(n) en el peor caso, donde n es el número de nodos del subárbol más pequeño; se detiene en cuanto encuentra una diferencia.
 */
bool BST::equalTrees(NodeT *a, NodeT *b) const {
    if (a == nullptr && b == nullptr) {
        return true;
    }
    if (a == nullptr || b == nullptr) {
        return false;
    }
    if (a->getData() != b->getData()) {
        return false;
    }
    return equalTrees(a->getLeft(), b->getLeft()) && equalTrees(a->getRight(), b->getRight());
}

#endif // BST_H
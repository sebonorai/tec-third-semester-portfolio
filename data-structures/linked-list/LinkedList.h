// Implementa la clase para manejar listas simplemente encadenadas
// Incluye las operaciones de la Act 2.1: reverse, shift y operator==
// y las de la Act 2.2: constructor de copia, operator= y operator+=
// Sebastian Noriega Olavarrieta
// 06/10/2026

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <stdexcept>
#include "Node.h"

template <class T>
class LinkedList{
    public:
        LinkedList(); // constructor
        ~LinkedList(); // destructor
        void addFirst(T data); // agrega un nodo al inicio de la lista
        void addLast(T data); // agrega un nodo al final de la lista
        void deleteFirst(); // elimina el primer nodo de la lista
        void deleteLast(); // elimina el último nodo de la lista
        bool add(T data, int pos); // agrega un nodo en una posición específica
        void del(int pos); // elimina un nodo en una posicion especifica
        bool isEmpty() const; // verifica si la lista esta vacia
        int deleteAll(); // elimina todos los nodos de la lista
        T set(T data, int pos); // establece el dato de un nodo en una posicion especifica
        T get(int pos) const; // obtiene el dato de un nodo en una posicion especifica
        bool change(int pos1, int pos2); // intercambia los datos de dos nodos en posiciones especificas
        int getSize() const; // obtiene el tamaño de la lista
        void print() const; // imprime la lista
        void reverse(); // invierte el orden de la lista
        void shift(int n); // desplaza circularmente la lista n posiciones
        bool operator==(const LinkedList<T>& other) const; // compara dos listas
        LinkedList(const LinkedList<T>& other); // constructor de copia
        LinkedList<T>& operator=(const LinkedList<T>& other); // operador de asignación
        void operator+=(const LinkedList<T>& other); // operador de concatenación
    private:
        Node<T> *head;
        int size;
};

/*
 * Constructor
 * Descripción: crea una lista vacía.
 * Entrada: nada. Salida: nada.
 * Precondición: ninguna.
 * Postcondición: head es nullptr y size es 0.
 * Complejidad: O(1), solo asigna dos variables.
 */
template <class T>
LinkedList<T>::LinkedList() {
    head = nullptr; // inicializa la cabeza de la lista como nula
    size = 0; // inicializa el tamaño de la lista como 0
}

/*
 * Destructor
 * Descripción: libera la memoria de todos los nodos.
 * Entrada: nada. Salida: nada.
 * Precondición: ninguna.
 * Postcondición: no quedan nodos en memoria.
 * Complejidad: O(n), llama a deleteAll que visita los n nodos una vez.
 */
template <class T>
LinkedList<T>::~LinkedList() {
    deleteAll(); // elimina todos los nodos de la lista al destruir el objeto
}

/*
 * addFirst
 * Descripción: agrega un nodo con el dato al inicio de la lista.
 * Entrada: el dato a agregar. Salida: nada.
 * Precondición: la lista está instanciada.
 * Postcondición: el nuevo dato queda en la posición 0 y size aumenta en 1.
 * Complejidad: O(1), no recorre la lista.
 */
template <class T>
void LinkedList<T>::addFirst(T data) {
    head = new Node<T>(data, head); // crea un nuevo nodo y lo establece como la cabeza de la lista
    size++; // incrementa el tamaño de la lista
}

/*
 * addLast
 * Descripción: agrega un nodo con el dato al final de la lista.
 * Entrada: el dato a agregar. Salida: nada.
 * Precondición: la lista está instanciada.
 * Postcondición: el nuevo dato queda en la última posición y size aumenta en 1.
 * Complejidad: O(n), recorre toda la lista para llegar al último nodo
 * (en lista vacía es O(1)).
 */
template <class T>
void LinkedList<T>::addLast(T data) { // agrega un nodo al final de la lista
    if (isEmpty()){
        addFirst(data); // si la lista está vacía, agrega el nodo al inicio
    }
    else{
        Node<T> *current = head; // comienza desde la cabeza de la lista
        while (current->getNext() != nullptr) { // recorre la lista hasta el último nodo
            current = current->getNext(); // avanza al siguiente nodo
        }
        current->setNext(new Node<T>(data)); // agrega un nuevo nodo al final de la lista
        size++; // incrementa el tamaño de la lista
    }
}

/*
 * deleteFirst
 * Descripción: elimina el primer nodo de la lista.
 * Entrada: nada. Salida: nada.
 * Precondición: la lista está instanciada, puede estar vacía.
 * Postcondición: si había nodos, el primero se elimina y size disminuye en 1.
 * Complejidad: O(1), no recorre la lista.
 */
template <class T>
void LinkedList<T>::deleteFirst() { // elimina el primer nodo de la lista
    if (head != nullptr) { // verifica si la lista no esta vacia
        Node<T> *borrar = head; // guarda el nodo a eliminar
        head = head->getNext(); // actualiza la cabeza de la lista al siguiente nodo
        delete borrar; // elimina el nodo
        size--; // decrementa el tamaño de la lista
    }
}

/*
 * deleteLast
 * Descripción: elimina el último nodo de la lista.
 * Entrada: nada. Salida: nada.
 * Precondición: la lista está instanciada, puede estar vacía.
 * Postcondición: si había nodos, el último se elimina y size disminuye en 1.
 * Complejidad: O(n), recorre la lista hasta el penúltimo nodo.
 */
template <class T>
void LinkedList<T>::deleteLast() { // elimina el último nodo de la lista
    if (head == nullptr) { // lista vacía: no hay nada que borrar
        return;
    }
    if (head->getNext() == nullptr) { // un solo nodo
        deleteFirst();
        return;
    }
    Node<T> *current = head; // varios nodos: busca el penúltimo
    while (current->getNext()->getNext() != nullptr) {
        current = current->getNext();
    }
    delete current->getNext(); // borra el último nodo
    current->setNext(nullptr); // el penúltimo ahora es el último
    size--;
}

/*
 * add
 * Descripción: agrega un nodo con el dato en la posición indicada.
 * Entrada: el dato y la posición (0 a size).
 * Salida: true si se agregó, false si la posición no es válida.
 * Precondición: la lista está instanciada.
 * Postcondición: si fue válida, el dato queda en esa posición y size aumenta en 1.
 * Complejidad: O(n) en el peor caso, recorre hasta el nodo anterior a pos
 * (O(1) si pos es 0).
 */
template <class T>
bool LinkedList<T>::add(T data, int pos) { // agrega un nodo en una posición específica
    if (pos < 0 || pos > size) { // posiciones válidas: 0 a size
        return false;
    }
    if (pos == 0) {
        addFirst(data);
        return true;
    }
    Node<T> *current = head; // se detiene en el nodo anterior a pos
    for (int i = 0; i < pos - 1; i++) {
        current = current->getNext();
    }
    current->setNext(new Node<T>(data, current->getNext())); // inserta el nuevo nodo
    size++;
    return true;
}

/*
 * del
 * Descripción: elimina el nodo de la posición indicada.
 * Entrada: la posición (0 a size-1). Salida: nada.
 * Precondición: la lista está instanciada.
 * Postcondición: si la posición era válida, el nodo se elimina y size disminuye
 * en 1; si no, la lista no cambia.
 * Complejidad: O(n) en el peor caso, recorre hasta el nodo anterior a pos
 * (O(1) si pos es 0).
 */
template <class T>
void LinkedList<T>::del(int pos) { // elimina un nodo en una posicion especifica
    if (pos < 0 || pos >= size) { // posición inválida: no hace nada
        return;
    }
    if (pos == 0) {
        deleteFirst();
        return;
    }
    Node<T> *current = head; // se detiene en el nodo anterior a pos
    for (int i = 0; i < pos - 1; i++) {
        current = current->getNext();
    }
    Node<T> *borrar = current->getNext(); // nodo a eliminar
    current->setNext(borrar->getNext()); // lo salta
    delete borrar;
    size--;
}

/*
 * isEmpty
 * Descripción: indica si la lista no tiene nodos.
 * Entrada: nada. Salida: true si está vacía, false si no.
 * Precondición: la lista está instanciada.
 * Postcondición: la lista no cambia.
 * Complejidad: O(1), solo compara head con nullptr.
 */
template <class T>
bool LinkedList<T>::isEmpty() const { // verifica si la lista esta vacia
    return head == nullptr; // devuelve true si la cabeza de la lista es nula, indicando que la lista está vacía
}

/*
 * deleteAll
 * Descripción: elimina todos los nodos de la lista.
 * Entrada: nada. Salida: cuántos nodos se eliminaron.
 * Precondición: la lista está instanciada.
 * Postcondición: la lista queda vacía (head nullptr, size 0).
 * Complejidad: O(n), visita cada nodo una vez.
 */
template <class T>
int LinkedList<T>::deleteAll() { // elimina todos los nodos de la lista
    int borrados = 0; // cuenta los nodos eliminados
    while (head != nullptr) {
        Node<T> *borrar = head; // guarda el nodo actual
        head = head->getNext(); // avanza antes de borrar
        delete borrar;
        borrados++;
    }
    size = 0;
    return borrados;
}

/*
 * set
 * Descripción: cambia el dato de la posición indicada.
 * Entrada: el nuevo dato y la posición (0 a size-1).
 * Salida: el dato que estaba antes en esa posición.
 * Precondición: la posición es válida, si no lanza out_of_range.
 * Postcondición: la posición guarda el nuevo dato.
 * Complejidad: O(n) en el peor caso, recorre hasta la posición.
 */
template <class T>
T LinkedList<T>::set(T data, int pos) { // establece el dato de un nodo en una posicion especifica
    if (pos < 0 || pos >= size) {
        throw std::out_of_range("Posicion invalida");
    }
    Node<T> *current = head;
    for (int i = 0; i < pos; i++) {
        current = current->getNext();
    }
    T anterior = current->getData(); // guarda el dato anterior
    current->setData(data);
    return anterior;
}

/*
 * get
 * Descripción: obtiene el dato de la posición indicada.
 * Entrada: la posición (0 a size-1). Salida: el dato en esa posición.
 * Precondición: la posición es válida, si no lanza out_of_range.
 * Postcondición: la lista no cambia.
 * Complejidad: O(n) en el peor caso, recorre hasta la posición.
 */
template <class T>
T LinkedList<T>::get(int pos) const { // obtiene el dato de un nodo en una posicion especifica
    if (pos < 0 || pos >= size) {
        throw std::out_of_range("Posicion invalida");
    }
    Node<T> *current = head;
    for (int i = 0; i < pos; i++) {
        current = current->getNext();
    }
    return current->getData();
}

/*
 * change
 * Descripción: intercambia los datos de dos posiciones.
 * Entrada: las dos posiciones (0 a size-1).
 * Salida: true si se pudo intercambiar, false si alguna posición es inválida.
 * Precondición: la lista está instanciada.
 * Postcondición: los datos de ambas posiciones quedan intercambiados.
 * Complejidad: O(n), usa get y set, cada uno recorre hasta n nodos.
 */
template <class T>
bool LinkedList<T>::change(int pos1, int pos2) { // intercambia los datos de dos nodos en posiciones especificas
    if (pos1 < 0 || pos1 >= size || pos2 < 0 || pos2 >= size) {
        return false;
    }
    if (pos1 == pos2) { // mismo nodo: no hay nada que intercambiar
        return true;
    }
    T temp = get(pos1);
    set(get(pos2), pos1);
    set(temp, pos2);
    return true;
}

/*
 * getSize
 * Descripción: obtiene la cantidad de nodos de la lista.
 * Entrada: nada. Salida: el tamaño.
 * Precondición: la lista está instanciada.
 * Postcondición: la lista no cambia.
 * Complejidad: O(1), regresa el atributo size.
 */
template <class T>
int LinkedList<T>::getSize() const { // obtiene el tamaño de la lista
    return size; // devuelve el tamaño de la lista
}

/*
 * print
 * Descripción: imprime los datos de la lista separados por espacio.
 * Entrada: nada. Salida: nada (imprime en pantalla).
 * Precondición: la lista está instanciada y T se puede imprimir con cout.
 * Postcondición: la lista no cambia.
 * Complejidad: O(n), visita cada nodo una vez.
 */
template <class T>
void LinkedList<T>::print() const { // imprime la lista
    Node<T> *current = head; // comienza desde la cabeza de la lista
    while (current != nullptr) { // recorre la lista hasta el último nodo
        std::cout << current->getData() << " "; // imprime el dato del nodo actual
        current = current->getNext(); // avanza al siguiente nodo
    }
    std::cout << std::endl; // imprime un salto de línea al final
}

/*
 * reverse
 * Descripción: invierte el contenido de la lista.
 * Entrada: nada. Salida: nada.
 * Precondición: la lista está instanciada, puede estar vacía.
 * Postcondición: los nodos quedan en orden inverso al que tenían.
 * Complejidad: O(n), recorre cada nodo una vez y no reserva memoria nueva.
 */
template <class T>
void LinkedList<T>::reverse() {
    Node<T> *prev = nullptr; // nodo anterior, a donde apuntará current
    Node<T> *current = head; // nodo que se está procesando
    Node<T> *next = nullptr; // guarda el resto de la lista
    while (current != nullptr) {
        next = current->getNext(); // guarda el siguiente antes de cortar el enlace
        current->setNext(prev); // voltea el enlace
        prev = current; // avanza prev
        current = next; // avanza current
    }
    head = prev; // prev quedó en el último nodo original, que ahora es el primero
}

/*
 * shift
 * Descripción: desplaza circularmente la lista n posiciones. Con n positivo el
 * nodo de la posición 0 pasa a la posición n; con n negativo se desplaza en
 * sentido contrario (n = -1: el de la posición 0 pasa a ser el último).
 * Entrada: un entero n (puede ser positivo, negativo, cero o mayor que size).
 * Salida: nada.
 * Precondición: la lista está instanciada, puede estar vacía.
 * Postcondición: la lista queda con el corrimiento aplicado, mismo size.
 * Complejidad: O(n), recorre la lista una vez para encontrar el punto de corte
 * y otra vez para llegar al último nodo.
 */
template <class T>
void LinkedList<T>::shift(int n) {
    if (size <= 1) { // vacía o un nodo: no cambia nada
        return;
    }
    int k = n % size; // reduce n a un valor entre -(size-1) y size-1
    if (k < 0) {
        k += size; // lo vuelve positivo: shift(-1) equivale a shift(size-1)
    }
    if (k == 0) { // corrimiento completo: la lista queda igual
        return;
    }
    // Con k positivo el nodo de la posición size-k pasa a ser la nueva cabeza
    Node<T> *newTail = head; // nodo en la posición size-k-1
    for (int i = 0; i < size - k - 1; i++) {
        newTail = newTail->getNext();
    }
    Node<T> *newHead = newTail->getNext(); // nodo en la posición size-k
    newTail->setNext(nullptr); // corta la lista en dos
    Node<T> *last = newHead; // busca el último nodo de la segunda parte
    while (last->getNext() != nullptr) {
        last = last->getNext();
    }
    last->setNext(head); // pega la primera parte al final de la segunda
    head = newHead;
}

/*
 * operator==
 * Descripción: comprueba si dos listas tienen la misma cantidad de datos y los
 * mismos datos en las mismas posiciones.
 * Entrada: la lista con la que se compara. Salida: true si son iguales.
 * Precondición: ambas listas están instanciadas y T soporta el operador ==.
 * Postcondición: ninguna, las listas no cambian.
 * Complejidad: mejor caso O(1) si los tamaños son distintos o el primer dato
 * difiere; peor caso O(n) si son iguales y se recorren completas.
 */
template <class T>
bool LinkedList<T>::operator==(const LinkedList<T>& other) const {
    if (size != other.size) { // tamaños distintos: no pueden ser iguales
        return false;
    }
    Node<T> *a = head; // recorre esta lista
    Node<T> *b = other.head; // recorre la otra lista
    while (a != nullptr) { // ambas tienen el mismo tamaño
        if (a->getData() != b->getData()) { // dato distinto: son diferentes
            return false;
        }
        a = a->getNext();
        b = b->getNext();
    }
    return true;
}

/*
 * Constructor de copia
 * Descripción: crea una lista que es un clon de otra.
 * Entrada: la lista a copiar. Salida: nada.
 * Precondición: la lista de entrada está instanciada, puede estar vacía.
 * Postcondición: la nueva lista tiene los mismos datos en el mismo orden.
 * Complejidad: O(n), recorre la lista de entrada y crea n nodos nuevos.
 */

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& other){
    head = nullptr;
    size = 0;
    Node<T> *source = other.head;
    Node<T> *last = nullptr;
    while (source != nullptr) {
    Node<T> *copy = new Node<T>(source->getData());
    if (last == nullptr) {
        head = copy;
    } else {
        last->setNext(copy);
    }
    last = copy;
    size++;
    source = source->getNext();
    }
}

/*
 * operator=
 * Descripción: asigna una lista en la lista original, dejándola como clon.
 * Entrada: la lista que se copia. Salida: la lista original (permite a = b = c).
 * Precondición: ambas listas están instanciadas, pueden estar vacías.
 * Postcondición: la lista original es un clon de la de entrada; sus datos
 * anteriores se eliminan y no hay fuga de memoria.
 * Complejidad: O(n + m), borra los n nodos anteriores y copia los m de la entrada.
 */
template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {
    if (this != &other) { // evita borrar la lista si se asigna a sí misma (a = a)
        deleteAll(); // libera los nodos que ya tenía
        Node<T> *source = other.head; // recorre la lista original
        Node<T> *last = nullptr; // último nodo de la copia
        while (source != nullptr) {
            Node<T> *copy = new Node<T>(source->getData());
            if (last == nullptr) {
                head = copy;
            } else {
                last->setNext(copy);
            }
            last = copy;
            size++;
            source = source->getNext();
        }
    }
    return *this;
}

/*
 * operator+=
 * Descripción: agrega al final de la lista original una copia de cada dato de
 * la lista de entrada.
 * Entrada: la lista cuyos datos se copian. Salida: nada.
 * Precondición: ambas listas están instanciadas, pueden estar vacías.
 * Postcondición: la lista original tiene sus datos seguidos de una copia de los
 * datos de la entrada; la lista de entrada no cambia (salvo que sea la misma
 * lista, en cuyo caso sus datos se duplican).
 * Complejidad: O(n + m), recorre los n nodos propios para hallar el último y
 * copia los m nodos de la entrada.
 */
template <class T>
void LinkedList<T>::operator+=(const LinkedList<T>& other) {
    int count = other.size; // se guarda antes de modificar size (por si other es *this)
    Node<T> *last = head; // busca el último nodo propio
    while (last != nullptr && last->getNext() != nullptr) {
        last = last->getNext();
    }
    Node<T> *source = other.head;
    for (int i = 0; i < count; i++) { // copia exactamente count datos
        Node<T> *copy = new Node<T>(source->getData());
        if (last == nullptr) {
            head = copy; // la lista original estaba vacía
        } else {
            last->setNext(copy);
        }
        last = copy;
        source = source->getNext();
    }
    size += count;
}
#endif // LINKEDLIST_H

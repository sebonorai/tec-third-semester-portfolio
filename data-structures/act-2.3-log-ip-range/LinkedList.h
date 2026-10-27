/*
 * LinkedList.h
 * Act 2.3 - TC1031 Programación de estructuras de datos y algoritmos fundamentales
 *
 * Lista simplemente encadenada lineal genérica.
 * Se agregaron a la clase vista en clase:
 *   - Apuntador tail para insertar al final en O(1).
 *   - Ordenamiento Merge Sort que trabaja directamente sobre los nodos.
 *   - Despliegue de los elementos dentro de un rango (lista ordenada).
 *
 * Requisito para T: debe tener operator< , operator<= y un método toString().
 */
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include "Node.h"

template <class T>
class LinkedList {
private:
    Node<T>* head;   // Primer nodo de la lista
    Node<T>* tail;   // Último nodo de la lista
    int size;        // Cantidad de elementos

    /*
     * split: divide la lista que inicia en h en dos mitades usando la técnica
     * de apuntador lento / apuntador rápido. Corta la primera mitad y regresa
     * el inicio de la segunda.
     * Parámetros: h - inicio de la sublista (con al menos 2 nodos).
     * Regresa: apuntador al primer nodo de la segunda mitad.
     * Complejidad: O(n), con n el tamaño de la sublista.
     */
    Node<T>* split(Node<T>* h) {
        Node<T>* slow = h;
        Node<T>* fast = h->next;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        Node<T>* second = slow->next;
        slow->next = nullptr;   // Se corta la primera mitad
        return second;
    }

    /*
     * merge: une dos sublistas ya ordenadas en una sola ordenada, re-enlazando
     * los nodos existentes (no crea ni copia nodos). Es estable porque, en
     * empate, toma primero el nodo de la sublista izquierda.
     * Parámetros: a, b - inicios de las sublistas ordenadas.
     * Regresa: inicio de la sublista unida y ordenada.
     * Complejidad: O(n1 + n2) tiempo, O(1) espacio adicional.
     */
    Node<T>* merge(Node<T>* a, Node<T>* b) {
        Node<T>* result = nullptr;
        Node<T>** last = &result;   // Dirección del apuntador donde se enlaza el siguiente
        while (a != nullptr && b != nullptr) {
            if (a->data <= b->data) {
                *last = a;
                a = a->next;
            } else {
                *last = b;
                b = b->next;
            }
            last = &((*last)->next);
        }
        *last = (a != nullptr) ? a : b;  // Se pega lo que sobre
        return result;
    }

    /*
     * mergeSort: ordena recursivamente la sublista que inicia en h.
     * Parámetros: h - inicio de la sublista.
     * Regresa: inicio de la sublista ya ordenada.
     * Complejidad: O(n log n) tiempo; O(log n) espacio por la recursión.
     */
    Node<T>* mergeSort(Node<T>* h) {
        if (h == nullptr || h->next == nullptr) {
            return h;   // Caso base: 0 o 1 elemento ya está ordenado
        }
        Node<T>* second = split(h);
        Node<T>* left = mergeSort(h);
        Node<T>* right = mergeSort(second);
        return merge(left, right);
    }

public:
    /*
     * Constructor: crea una lista vacía.
     * Complejidad: O(1)
     */
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    /*
     * Destructor: libera la memoria de todos los nodos.
     * Complejidad: O(n)
     */
    ~LinkedList() {
        clear();
    }

    // Se deshabilita la copia para evitar liberar dos veces los mismos nodos.
    LinkedList(const LinkedList<T>&) = delete;
    LinkedList<T>& operator=(const LinkedList<T>&) = delete;

    /*
     * getSize: regresa la cantidad de elementos de la lista.
     * Complejidad: O(1)
     */
    int getSize() const {
        return size;
    }

    /*
     * isEmpty: indica si la lista no tiene elementos.
     * Complejidad: O(1)
     */
    bool isEmpty() const {
        return size == 0;
    }

    /*
     * addFirst: inserta un elemento al inicio de la lista.
     * Parámetros: data - elemento a insertar.
     * Complejidad: O(1)
     */
    void addFirst(const T& data) {
        head = new Node<T>(data, head);
        if (tail == nullptr) {
            tail = head;
        }
        size++;
    }

    /*
     * addLast: inserta un elemento al final de la lista usando tail.
     * Parámetros: data - elemento a insertar.
     * Complejidad: O(1)
     */
    void addLast(const T& data) {
        Node<T>* nuevo = new Node<T>(data);
        if (head == nullptr) {
            head = tail = nuevo;
        } else {
            tail->next = nuevo;
            tail = nuevo;
        }
        size++;
    }

    /*
     * clear: elimina todos los nodos y deja la lista vacía.
     * Complejidad: O(n)
     */
    void clear() {
        while (head != nullptr) {
            Node<T>* aux = head;
            head = head->next;
            delete aux;
        }
        tail = nullptr;
        size = 0;
    }

    /*
     * sort: ordena la lista de menor a mayor con Merge Sort directamente
     * sobre los nodos y actualiza tail.
     * Complejidad: O(n log n)
     */
    void sort() {
        head = mergeSort(head);
        tail = head;
        while (tail != nullptr && tail->next != nullptr) {
            tail = tail->next;   // Recorrido O(n) para ubicar el nuevo último
        }
    }

    /*
     * printRange: despliega los elementos x tales que inicio <= x <= fin.
     * Precondición: la lista está ordenada de menor a mayor.
     * Se salta los elementos menores a inicio y se detiene en cuanto encuentra
     * uno mayor a fin (no recorre el resto de la lista).
     * Parámetros: inicio, fin - límites inclusivos; out - flujo de salida.
     * Regresa: la cantidad de elementos desplegados.
     * Complejidad: O(n) en el peor caso; O(k + m) en general, donde k son los
     *              nodos anteriores al rango y m los nodos dentro del rango.
     */
    int printRange(const T& inicio, const T& fin, std::ostream& out = std::cout) const {
        int count = 0;
        Node<T>* aux = head;
        while (aux != nullptr && aux->data < inicio) {
            aux = aux->next;
        }
        while (aux != nullptr && aux->data <= fin) {
            out << aux->data.toString() << "\n";
            count++;
            aux = aux->next;
        }
        return count;
    }

    /*
     * print: despliega todos los elementos de la lista.
     * Parámetros: out - flujo de salida (consola o archivo).
     * Complejidad: O(n)
     */
    void print(std::ostream& out = std::cout) const {
        Node<T>* aux = head;
        while (aux != nullptr) {
            out << aux->data.toString() << "\n";
            aux = aux->next;
        }
    }
};

#endif // LINKEDLIST_H

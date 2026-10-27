/*
 * Node.h
 * Act 2.3 - TC1031 Programación de estructuras de datos y algoritmos fundamentales
 *
 * Nodo genérico de una lista simplemente encadenada lineal.
 * Cada nodo guarda un dato y un apuntador al siguiente nodo.
 */
#ifndef NODE_H
#define NODE_H

template <class T>
class Node {
public:
    T data;          // Dato almacenado en el nodo
    Node<T>* next;   // Apuntador al siguiente nodo (nullptr si es el último)

    /*
     * Constructor: crea un nodo con el dato recibido y sin siguiente.
     * Parámetros: data - dato a guardar.
     * Complejidad: O(1)
     */
    explicit Node(const T& data) : data(data), next(nullptr) {}

    /*
     * Constructor: crea un nodo con el dato y el siguiente indicados.
     * Parámetros: data - dato a guardar; next - nodo siguiente.
     * Complejidad: O(1)
     */
    Node(const T& data, Node<T>* next) : data(data), next(next) {}
};

#endif // NODE_H

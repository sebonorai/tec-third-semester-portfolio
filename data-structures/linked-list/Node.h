// implementa la clase nodo para listas simplemente encadenada
// Sebastian Noriega Olavarrieta
// 25/09/2026

#ifndef NODE_H
#define NODE_H



template <class T>
class Node{
    public:
        Node(T data); // constructor 
        Node(T data, Node<T> *next); // constructor con siguiente   
        T getData() const; // obtiene el dato del nodo
        Node<T> *getNext() const; // obtiene el siguiente nodo
        void setData(T data); // establece el dato del nodo
        void setNext(Node<T> *next); // establece el siguiente nodo
    private:
        T data;
        Node<T> *next;
};

template <class T>
Node<T>::Node(T data){
    this->data = data;
    next = nullptr;
} 

template <class T>
Node<T>::Node(T data, Node<T> *next){
    this->data = data;
    this->next = next;
} 

template <class T>
T Node<T>::getData() const{
    return data;
} 

template <class T>
Node<T> *Node<T>::getNext() const{
    return next;
}

template <class T>
void Node<T>::setData(T data){
    this->data = data;
} 

template <class T>
void Node<T>::setNext(Node<T> *next){
    this->next = next;
} 




#endif // NODE_H
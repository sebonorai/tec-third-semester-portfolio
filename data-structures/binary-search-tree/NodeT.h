// Implementa el ADT NodeT para arboles binarios
// Nombre: Sebastian Noriega Olavarrieta
// Fecha: 13/10/2026

#ifndef NODET_H
#define NODET_H

class NodeT{
    public:
        NodeT(int data); // Constructor que inicializa el nodo con un valor y establece los hijos en nullptr
        void setData(int data); // Establece el valor del nodo
        void setLeft(NodeT *Left); // Establece el hijo izquierdo
        void setRight(NodeT *Right); // Establece el hijo derecho
        int getData() const; // Obtiene el valor del nodo
        NodeT* getLeft() const; // Obtiene el hijo izquierdo
        NodeT* getRight() const; // Obtiene el hijo derecho

    private:
        int data;
        NodeT *left, *right;
        
};
NodeT::NodeT(int data) {
            this->data = data;
            left = right = nullptr;
}

void NodeT::setData(int data) {
            this->data = data;
}

void NodeT::setLeft(NodeT *Left) {
            this->left = Left;
}

void NodeT::setRight(NodeT *Right) {
            this->right = Right;
}

int NodeT::getData() const {
            return data;
}

NodeT* NodeT::getLeft() const {
            return left;
}

NodeT* NodeT::getRight() const {
            return right;
}


#endif // NODET_H
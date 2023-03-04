
#include "TreeSearchBinarie.h"
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

//estructura del arbol binario
template <class T>
NodeTree<T> *BinarySearchTree<T>::makeNode(const T &value)
{
    NodeTree<T> *temp = new NodeTree<T>;
    temp->data = value;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

//constructor
template <class T>
BinarySearchTree<T>::BinarySearchTree(const T &value)
{
    root = makeNode(value);
}

//destructor
template <class T>
BinarySearchTree<T>::~BinarySearchTree()
{
    destroy(root);
}

//Funcion auxiliar del destructor
template <class T>
void BinarySearchTree<T>::destroy(NodeTree<T> *ptr)
{
    if (!ptr)
        return;
    destroy(ptr->left);
    destroy(ptr->right);
    delete ptr;
}

//funcion para insertar un valor en el arbol de busqueda binaria
//ordenandolo con respecto a su raiz
//no puede que se balancee
template <class T>
void BinarySearchTree<T>::insertValue(NodeTree<T> *&ptr, const T &value)
{

    if (!ptr)
    {
        ptr = makeNode(value);
    }
    else
    {
        if (value < ptr->data)
        {
            insertValue(ptr->left, value);
        }
        else
        {
            insertValue(ptr->right, value);
        }
    }
}

//getter function
template <class T>
NodeTree<T> *&BinarySearchTree<T>::getRoot()
{
    return root;
}

template <class T>
T BinarySearchTree<T>::getRootValue()
{
    return root->data;
}

//setter function
template <class T>
void BinarySearchTree<T>::setRootValue(const T &value)
{
    root->data = value;
}

//getter function
template <class T>
int BinarySearchTree<T>::getCountNodes(const NodeTree<T> *ptr)
{
    if (!ptr)
    {
        return 0;
    }
    else
    {
        return 1 + getCountNodes(ptr->left) + getCountNodes(ptr->right);
    }
}

//getter function
template <class T>
void BinarySearchTree<T>::getCountNodes()
{
    cout << "Nodos del arbol: " << getCountNodes(root) << endl;
}

//mostrando el arbol  en postorden
template <class T>
void BinarySearchTree<T>::printTreeValues(const NodeTree<T> *ptr)
{
    if (!ptr)
    {
        return;
    }
    printTreeValues(ptr->left);
    printTreeValues(ptr->right);
    cout << ptr->data << " - ";
}


//metodo para buscar un valor dentro del arbol de manera recursiva
template <class T>
bool BinarySearchTree<T>::searchValue(const NodeTree<T> *ptr, const T &value)
{
    if (!ptr)
    {
        return false;
    }

    if (ptr->data == value)
    {
        return true;
    }
    else
    {
        if (value < ptr->data)
        {
            return searchValue(ptr->left, value);
        }
        else
        {
            return searchValue(ptr->right, value);
        }
    }
}

//metodo no tail de buscar el valor dentro del arbol
template <class T>
void BinarySearchTree<T>::getSearchValue(const T &value)
{
    if (searchValue(root, value))
    {
        cout << "Existe el valor" << endl;
    }
    else
    {
        cout << "No existe el valor" << endl;
    }
}

//metodo para mostrar de manera grafica/primivita el arbol
//cabe resaltar que se muestra de manera  vertical y el primero que se muestra es la hoja de la derecha
template <class T>
void BinarySearchTree<T>::showTree(NodeTree<T> *ptr, int count)
{
    if (!ptr)
    {
        return;
    }
    else
    {
        showTree(ptr->right, count + 1);
        for (int i = 0; i < count; ++i)
        {
            cout << "  ";
        }
        cout << ptr->data << "-----\n";
        showTree(ptr->left, count + 1);
    }
}


//eliminando un valor del arbol dependiendo del caso
template <class T>
void BinarySearchTree<T>::removeNode(NodeTree<T> *&ptr, const T &value)
{

    if (!searchValue(root, value) || !ptr)
    {
        cout << "No existe ese elemento en el arbol" << endl;
        assert(false);
    }

    T aux1, aux2;

    if (value < ptr->data)
    {
        removeNode(ptr->left, value);
    }
    else if (value > ptr->data)
    {
        removeNode(ptr->right, value);
    }
    else
    {
        if (!ptr->left && !ptr->right)  //El caso que no tiene hijos o sea es una hoja lo borra directamente
        {
            delete ptr;
            ptr = NULL;
        }
        //El nodo a borrar tiene un hijo. En este caso, se elimina el nodo y se reemplaza por su hijo.
        else if ((!ptr->left && ptr->right) || (ptr->left && !ptr->right)) 
        {
            if (ptr->left)
            {
                aux1 = ptr->left->data;
                delete ptr->left;
                ptr->left = NULL;
                delete ptr;
                ptr = NULL;
                insertValue(root, aux1);
            }
            else if (ptr->right)
            {
                aux1 = ptr->right->data;
                delete ptr->right;
                ptr->right = NULL;
                delete ptr;
                ptr = NULL;
                insertValue(root, aux1);
            }
        }
        //El nodo a borrar tiene dos hijos se toma el hijo menor del sub arbol derecho y se reemplaza como padre
        else if (ptr == root)
        {
            aux1 = getMinValue(ptr->right);
            setRootValue(aux1);
            removeNode(root->right, aux1);
        }
        else if (ptr->left && ptr->right)
        {
            aux1 = ptr->left->data;
            aux2 = ptr->right->data;

            delete ptr->left;
            ptr->left = NULL;
            delete ptr->right;
            ptr->right = NULL;
            delete ptr;
            ptr = NULL;
            insertValue(root, aux1);
            insertValue(root, aux2);
        }
    }
}

//metodo para obtener el nodo con el valor minimo del arbol
template <class T>
T BinarySearchTree<T>::getMinValue(NodeTree<T> *ptr)
{
    NodeTree<T> *current = ptr;
    while (current->left)
    {
        current = current->left;
    }
    return current->data;
}

//metodo para obtener el nodo con el valor miaximo del arbol
template <class T>
T BinarySearchTree<T>::getMaxValue(NodeTree<T> *ptr)
{
    NodeTree<T> *current = ptr;
    while (current->right)
    {
        current = current->right;
    }
    return current->data;
}


//metodo para mostrar todas las rutas desde la raiz a las hojas
template <class T>
void BinarySearchTree<T>::showRoutLeaft(const NodeTree<T> *ptr, vector<int> route)
{
    //se guarda el camino en un vector y se recorre recursivamentente hasta llegar a las diferentes hojas
    //una vez se determine que sea una hoja se imprime el vecctor mostrando el camino de cada una
    route.push_back(ptr->data);

    if (!ptr->left && !ptr->right)
    {
        for (int i : route)
        {
            cout << i << " - ";
        }
        cout << endl;
    }
    else
    {
        showRoutLeaft(ptr->left, route);
        showRoutLeaft(ptr->right, route);
    }
}


#ifndef TREESEARCHBINARIE_TREESEARCHBINARIE_H
#define TREESEARCHBINARIE_TREESEARCHBINARIE_H

#include <vector>

using namespace std;

template <class T>
struct NodeTree
{
    T data;
    NodeTree<T> *left;
    NodeTree<T> *right;
};

template <class T>
class BinarySearchTree
{
protected:
    NodeTree<T> *root;
    void destroy(NodeTree<T> *ptr);
    bool searchValue(const NodeTree<T> *ptr, const T &value);
    int getCountNodes(const NodeTree<T> *ptr);

public:
    NodeTree<T> *makeNode(const T &value);
    BinarySearchTree(const T &value);
    ~BinarySearchTree();

    void getCountNodes();
    void setRootValue(const T &value);
    void insertValue(NodeTree<T> *&ptr, const T &value);
    T getRootValue();
    T getMinValue(NodeTree<T> *ptr);
    T getMaxValue(NodeTree<T> *ptr);
    NodeTree<T> *&getRoot();
    void getSearchValue(const T &value);
    void showTree(NodeTree<T> *ptr, int count);
    void printTreeValues(const NodeTree<T> *ptr);
    void removeNode(NodeTree<T> *&ptr, const T &value);
    void showRoutLeaft(const NodeTree<T> *ptr, vector<int> route);
};

#endif

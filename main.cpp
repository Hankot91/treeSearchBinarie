#include "TreeSearchBinarie/TreeSearchBinarie.cpp"
int main()
{
    vector<int> route;
    BinarySearchTree<int> numeros(5);
    numeros.insertValue(numeros.getRoot(), 2);
    numeros.insertValue(numeros.getRoot(), 8);
    numeros.insertValue(numeros.getRoot(), 3);
    numeros.insertValue(numeros.getRoot(), 1);
    numeros.insertValue(numeros.getRoot(), 9);
    numeros.insertValue(numeros.getRoot(), 7);
    numeros.getCountNodes();
    numeros.showTree(numeros.getRoot(), 0);
    cout << "\n"
    << endl;
    numeros.showRoutLeaft(numeros.getRoot(), route);
    cout << "Valor minimo: " << numeros.getMinValue(numeros.getRoot())
    << ", Valor maximo: " << numeros.getMaxValue(numeros.getRoot()) << endl;
    numeros.removeNode(numeros.getRoot(), 5);
    numeros.showTree(numeros.getRoot(), 0);
    numeros.printTreeValues(numeros.getRoot());

    return 0;
}

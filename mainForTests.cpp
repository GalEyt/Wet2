
#include "HashTable.h"
#include "UnionFind.h"

void unitest1(){
    HashTable<int, int>* table = new HashTable<int, int>();
    table->addElement(55, 72);
}


int main(){
    unitest1();
    // AVLTree<int, int>* array[2] = {new AVLTree<int, int>(), new AVLTree<int, int>()};
    // AVLTree<int, int>** table = new AVLTree<int, int>*(new AVLTree<int, int>());
    // table[0]->insert(1,2);
    // table[1] = new AVLTree<int, int>();

    return 0;
}
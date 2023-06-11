
#include "HashTable.h"
//#include "unionFind.h"
#include <cassert>

void unitest1(){
    HashTable<int, int>* table = new HashTable<int, int>();
    table->addElement(55, 72);
    table->addElement(43, 54);
    table->addElement(23, 76);
    table->addElement(123, 672);
    table->addElement(876, 54);
    table->addElement(32, 875);
    table->addElement(12, 3);
    table->addElement(535, 4);
    table->addElement(2, 8);
    table->addElement(5345, 712342);
    table->addElement(44, 55);
    table->addElement(66, 98);
    table->addElement(23, 12);
    table->addElement(1, 90);
    assert(table->getElement(72)!=55);
}


void unitestsUF(){
    
}


int main(){
    unitest1();
    unitestsUF();
    // AVLTree<int, int>* array[2] = {new AVLTree<int, int>(), new AVLTree<int, int>()};
    // AVLTree<int, int>** table = new AVLTree<int, int>*(new AVLTree<int, int>());
    // table[0]->insert(1,2);
    // table[1] = new AVLTree<int, int>();

    return 0;
}
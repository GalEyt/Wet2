
//#include "HashTable.h"
#include "unionFind.h"
#include <cassert>

void unitest1(){
    /*
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
    assert(table->getElement(72)!=55);*/
}


void unitestsUF(){
    int* data = new int(1);
    data [1] = 2;
    data [2] = 3;
    data [3] = 4;
    data [4] = 5;
    data [5] = 6;
    data [6] = 7;
    data [7] = 8;
    data [8] = 9;
    data [9] = 10;
    UnionFind<int, 10>* uf = new UnionFind<int, 10>(10, data);
    int id0 = uf->find(0);
    int id1 = uf->find(1);
    int id2 = uf->find(2);
    int id3 = uf->find(3);
    int id4 = uf->find(4);
    int id5 = uf->find(5);
    int id6 = uf->find(6);
    int id7 = uf->find(7);
    int id8 = uf->find(8);
    int id9 = uf->find(9);
    for (int i = 0; i<10; i++){
        for (int j = 0; j<10; j++){
            if (i==j){
                assert(uf->find(i) == uf->find(j));
            }
            else{
                assert(uf->find(i) != uf->find(j));
            }
        }
    }
}


int main(){
    //unitest1();
    unitestsUF();
    // AVLTree<int, int>* array[2] = {new AVLTree<int, int>(), new AVLTree<int, int>()};
    // AVLTree<int, int>** table = new AVLTree<int, int>*(new AVLTree<int, int>());
    // table[0]->insert(1,2);
    // table[1] = new AVLTree<int, int>();

    return 0;
}
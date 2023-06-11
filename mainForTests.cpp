
#include "HashTable.h"
//#include "unionFind.h"
#include "RankTree.h"
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

void unittestRT(){
    RankTree<int, int>* root = new RankTree<int,int>();
    root = root->insert(1,1);
    root = root->insert(1,2);
    root = root->insert(1,3);
    root = root->remove(2);
    root = root->remove(1);
    root = root->remove(3);

}


// void unitestsUF(){
//     int* data = new int(1);
//     data [1] = 2;
//     data [2] = 3;
//     data [3] = 4;
//     data [4] = 5;
//     data [5] = 6;
//     data [6] = 7;
//     data [7] = 8;
//     data [8] = 9;
//     data [9] = 10;
//     UnionFind<int>* uf = new UnionFind<int>(10, data);
//     for (int i = 0; i<10; i++){
//         for (int j = 0; j<10; j++){
//             if (i==j){
//                 assert(uf->find(i) == uf->find(j));
//             }
//             else{
//                 assert(uf->find(i) != uf->find(j));
//             }
//         }
//     }
// }


int main(){
    unittestRT();

    return 0;
}
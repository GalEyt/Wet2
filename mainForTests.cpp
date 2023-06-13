
#include "HashTable.h"
#include "unionFind.h"
#include <cassert>
#include <random>
#include <iostream>

void unitestHT(){
    HashTable<int, int>* table = new HashTable<int, int>();
    table->addElement(55, 72);
    assert(table->getElement(72)==55);
    table->addElement(43, 54);
    table->addElement(23, 76);
    assert(table->getElement(72)==55);
    assert(table->getElement(54)==43);
    assert(table->getElement(76)==23);
    table->addElement(123, 672);
    table->addElement(876, 58);
    assert(table->getElement(72)==55);
    assert(table->getElement(54)==43);
    assert(table->getElement(76)==23);
    assert(table->getElement(672)==123);
    assert(table->getElement(58)==876);
    table->addElement(32, 875);
    table->addElement(12, 3);
    table->addElement(535, 4);
    table->addElement(2, 8);
    table->addElement(5345, 712342);
    table->addElement(44, 55);
    table->addElement(66, 98);
    table->addElement(23, 12);
    table->addElement(1, 90);
    assert(table->getElement(72)==55);
    assert(table->getElement(54)==43);
    assert(table->getElement(76)==23);
    assert(table->getElement(672)==123);
    assert(table->getElement(58)==876);
    assert(table->getElement(875)==32);
    assert(table->getElement(3)==12);
    assert(table->getElement(4)==535);
    assert(table->getElement(8)==2);
    assert(table->getElement(712342)==5345);
    assert(table->getElement(55)==44);
    assert(table->getElement(98)==66);
    assert(table->getElement(12)==23);
    assert(table->getElement(90)==1);
    table->removeElement(72);
    table->removeElement(54);
    table->removeElement(76);
    table->removeElement(672);
    table->removeElement(58);
    table->removeElement(875);
    table->removeElement(3);
    table->removeElement(4);
    assert(table->getElement(8)==2);
    assert(table->getElement(712342)==5345);
    assert(table->getElement(55)==44);
    assert(table->getElement(98)==66);
    assert(table->getElement(12)==23);
    assert(table->getElement(90)==1);
    table->removeElement(8);
    table->removeElement(712342);
    table->removeElement(55);
    table->removeElement(98);
    table->removeElement(12);
    table->removeElement(90);
}

void unitestHT2(){
    HashTable<int, int>* table = new HashTable<int, int>();
    table->addElement(55, 72);
    assert(table->getElement(72)==55);
    table->addElement(43, 54);
    table->addElement(23, 76);
    assert(table->getElement(72)==55);
    assert(table->getElement(54)==43);
    assert(table->getElement(76)==23);
    table->addElement(123, 672);
    table->addElement(876, 58);
    assert(table->getElement(72)==55);
    assert(table->getElement(54)==43);
    assert(table->getElement(76)==23);
    assert(table->getElement(672)==123);
    assert(table->getElement(58)==876);
    table->addElement(32, 875);
    table->addElement(12, 3);
    table->addElement(535, 4);
    table->addElement(2, 8);
    table->addElement(5345, 712342);
    table->addElement(44, 55);
    table->addElement(66, 98);
    table->addElement(23, 12);
    table->addElement(1, 90);
    assert(table->getElement(72)==55);
    assert(table->getElement(54)==43);
    assert(table->getElement(76)==23);
    assert(table->getElement(672)==123);
    assert(table->getElement(58)==876);
    assert(table->getElement(875)==32);
    assert(table->getElement(3)==12);
    assert(table->getElement(4)==535);
    assert(table->getElement(8)==2);
    assert(table->getElement(712342)==5345);
    assert(table->getElement(55)==44);
    assert(table->getElement(98)==66);
    assert(table->getElement(12)==23);
    assert(table->getElement(90)==1);
    table->removeElement(72);
    table->removeElement(54);
    table->removeElement(76);
    table->removeElement(672);
    table->removeElement(58);
    table->removeElement(875);
    table->removeElement(3);
    table->removeElement(4);
    assert(table->getElement(8)==2);
    assert(table->getElement(712342)==5345);
    assert(table->getElement(55)==44);
    assert(table->getElement(98)==66);
}

void unitestHT3(){
    HashTable<int, int>* table = new HashTable<int, int>();
    int arrSize = 10000;
    int data[arrSize];
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < arrSize; j++)
        {
            data[j] = rand()%10000;
            table->addElement(data[j], j+i);
        }
        for (int j = 0; j < arrSize; j++)
        {
            assert(table->getElement(j+i)==data[j]);
        }
        for (int j = 0; j < arrSize; j++)
        {
            table->removeElement(j+i);
        }
    }
}

void unitestHT4(){
    HashTable<int, int>* table = new HashTable<int, int>();
    int arrSize = 10000;
    int data[arrSize];
    for (int i = 1; i < 1001; i++)
    {
        for (int j = 1; j < arrSize+1; j++)
        {
            data[j-1] = rand()%10000;
            table->addElement(data[j-1], j*i);
        }
        for (int j = 1; j < arrSize+1; j++)
        {
            assert(table->getElement(j*i)==data[j-1]);
        }
        for (int j = 1; j < arrSize+1; j++)
        {
            table->removeElement(j*i);
        }
    }
}

void unitestsUF(){
    int* data = (int*)malloc(sizeof(int)*10);
    data [1] = 2;
    data [2] = 3;
    data [3] = 4;
    data [4] = 5;
    data [5] = 6;
    data [6] = 7;
    data [7] = 8;
    data [8] = 9;
    data [9] = 10;
    int* heights = (int*)malloc(sizeof(int)*10);
    heights [1] = 2;
    heights [2] = 3;
    heights [3] = 4;
    heights [4] = 5;
    heights [5] = 6;
    heights [6] = 7;
    heights [7] = 8;
    heights [8] = 9;
    heights [9] = 10;
    UnionFind<int, 10>* uf = new UnionFind<int, 10>(data, heights);
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
    delete data;
    delete heights;
}

void unitestsUF2(){
    int* data = (int*)malloc(sizeof(int)*10);
    data [1] = 2;
    data [2] = 3;
    data [3] = 4;
    data [4] = 5;
    data [5] = 6;
    data [6] = 7;
    data [7] = 8;
    data [8] = 9;
    data [9] = 10;
    int* heights = (int*)malloc(sizeof(int)*10);
    heights [1] = 2;
    heights [2] = 3;
    heights [3] = 4;
    heights [4] = 5;
    heights [5] = 6;
    heights [6] = 7;
    heights [7] = 8;
    heights [8] = 9;
    heights [9] = 10;
    UnionFind<int, 10>* uf = new UnionFind<int, 10>(data, heights);
    uf->unionGroups(2,4);
    assert(uf->getHeight(2) == 5);
    assert(uf->getHeight(4) == 0);
    assert(uf->find(2) == uf->find(4));
    uf->unionGroups(2,6);
    assert(uf->getHeight(6) == 0);
    assert(uf->getHeight(4) == 7);
    assert(uf->getHeight(2) == 12);
    assert(uf->find(2) == uf->find(4));
    assert(uf->find(2) == uf->find(6));
    assert(uf->find(4) == uf->find(6));
    uf->unionGroups(8,9);
    assert(uf->getHeight(8) == 10);
    assert(uf->getHeight(9) == 0);
    assert(uf->find(2) == uf->find(4));
    assert(uf->find(2) == uf->find(6));
    assert(uf->find(6) == uf->find(4));
    assert(uf->find(2) != uf->find(8));
    assert(uf->find(8) == uf->find(9));
    uf->unionGroups(9,6);
    assert(uf->getHeight(6) == 0);
    assert(uf->getHeight(4) == 7);
    assert(uf->getHeight(2) == 12);
    assert(uf->getHeight(9) == 15);
    assert(uf->getHeight(8) == 25);
    assert(uf->find(2) == uf->find(4));
    assert(uf->find(2) == uf->find(6));
    assert(uf->find(6) == uf->find(4));
    assert(uf->find(2) == uf->find(8));
    assert(uf->find(8) == uf->find(9));
    assert(uf->find(6) == uf->find(9));
    delete data;
    delete heights;
}

void unitestsUF3(){
    int* data = (int*)malloc(sizeof(int)*10);
    data[0] = 1;
    data [1] = 2;
    data [2] = 3;
    data [3] = 4;
    data [4] = 5;
    data [5] = 6;
    data [6] = 7;
    data [7] = 8;
    data [8] = 9;
    data [9] = 10;
    int* heights = (int*)malloc(sizeof(int)*10);
    heights [1] = 2;
    heights [2] = 3;
    heights [3] = 4;
    heights [4] = 5;
    heights [5] = 6;
    heights [6] = 7;
    heights [7] = 8;
    heights [8] = 9;
    heights [9] = 10;
    UnionFind<int, 10> uf(data, heights);
    uf.unionGroups(2,4);
    uf.unionGroups(2,6);
    uf.unionGroups(8,9);
    uf.unionGroups(9,6);
    uf.unionGroups(9,8);
    uf.unionGroups(9,2);
    assert(uf.getHeight(6) == 0);
    assert(uf.getHeight(4) == 7);
    assert(uf.getHeight(2) == 12);
    assert(uf.getHeight(9) == 15);
    assert(uf.getHeight(8) == 25);
    assert(uf.find(2) == uf.find(4));
    assert(uf.find(2) == uf.find(6));
    assert(uf.find(6) == uf.find(4));
    assert(uf.find(2) == uf.find(8));
    assert(uf.find(8) == uf.find(9));
    assert(uf.find(6) == uf.find(9));
    delete data;
    delete heights;
}

int main(){
    unitestHT();
    unitestHT2();
    unitestHT3();
    unitestHT4();
    unitestsUF();
    unitestsUF2();
    unitestsUF3();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
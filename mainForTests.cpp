
#include "HashTable.h"
#include "unionFind.h"
#include "PrizeTree.h"
#include "recordsCompany.h"
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
    UnionFind<int>* uf = new UnionFind<int>(data, heights, 10);
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
    UnionFind<int>* uf = new UnionFind<int>(data, heights, 10);
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
    UnionFind<int> uf(data, heights, 10);
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

void unitestPrizeTree(){
    PrizeTree<int, int>* root = new PrizeTree<int,int>();
    root = root->insert(1, 7);
    root = root->insert(1, 3);
    root = root->insert(1, 11);
    root = root->insert(1, 1);
    root = root->insert(1, 5);
    root = root->insert(1, 9);
    root = root->insert(1, 13);
    root->addPrize(3, 11);
    root->addPrize(-3, 3);
    assert(root->getSum(root->find(1)) == 0);
    assert(root->getSum(root->find(3)) == 3);
    assert(root->getSum(root->find(5)) == 3);
    assert(root->getSum(root->find(7)) == 3);
    assert(root->getSum(root->find(9)) == 3);
    assert(root->getSum(root->find(11)) == 0);
    assert(root->getSum(root->find(13)) == 0);
    root->addPrize(1, 7);
    root->addPrize(-1, 5);
    assert(root->getSum(root->find(1)) == 0);
    assert(root->getSum(root->find(3)) == 3);
    assert(root->getSum(root->find(5)) == 4);
    assert(root->getSum(root->find(7)) == 3);
    assert(root->getSum(root->find(9)) == 3);
    assert(root->getSum(root->find(11)) == 0);
    assert(root->getSum(root->find(13)) == 0);
    root->addPrize(2, 13);
    root->addPrize(-2, 9);
    assert(root->getSum(root->find(1)) == 0);
    assert(root->getSum(root->find(3)) == 3);
    assert(root->getSum(root->find(5)) == 4);
    assert(root->getSum(root->find(7)) == 3);
    assert(root->getSum(root->find(9)) == 5);
    assert(root->getSum(root->find(11)) == 2);
    assert(root->getSum(root->find(13)) == 0);
    delete root;
}
 
void unitestPrizeTree2(){
    PrizeTree<int, int>* root = new PrizeTree<int,int>();
    root = root->insert(1, 7);
    root = root->insert(1, 3);
    root = root->insert(1, 11);
    root = root->insert(1, 1);
    root = root->insert(1, 5);
    root = root->insert(1, 9);
    root = root->insert(1, 13);
    root->addPrize(3, 12);
    root->addPrize(-3, 3);
    assert(root->getSum(root->find(1)) == 0);
    assert(root->getSum(root->find(3)) == 3);
    assert(root->getSum(root->find(5)) == 3);
    assert(root->getSum(root->find(7)) == 3);
    assert(root->getSum(root->find(9)) == 3);
    assert(root->getSum(root->find(11)) == 3);
    assert(root->getSum(root->find(13)) == 0);
    root->addPrize(1, 9);
    root->addPrize(-1, 6);
    assert(root->getSum(root->find(1)) == 0);
    assert(root->getSum(root->find(3)) == 3);
    assert(root->getSum(root->find(5)) == 3);
    assert(root->getSum(root->find(7)) == 4);
    assert(root->getSum(root->find(9)) == 3);
    assert(root->getSum(root->find(11)) == 3);
    assert(root->getSum(root->find(13)) == 0);
    root->addPrize(2, 14);
    root->addPrize(-2, 10);
    assert(root->getSum(root->find(1)) == 0);
    assert(root->getSum(root->find(3)) == 3);
    assert(root->getSum(root->find(5)) == 3);
    assert(root->getSum(root->find(7)) == 4);
    assert(root->getSum(root->find(9)) == 3);
    assert(root->getSum(root->find(11)) == 5);
    assert(root->getSum(root->find(13)) == 2);
    root->addPrize(1000, 1);
    root->addPrize(-1000, -3);
    assert(root->getSum(root->find(1)) == 0);
    assert(root->getSum(root->find(3)) == 3);
    assert(root->getSum(root->find(5)) == 3);
    assert(root->getSum(root->find(7)) == 4);
    assert(root->getSum(root->find(9)) == 3);
    assert(root->getSum(root->find(11)) == 5);
    assert(root->getSum(root->find(13)) == 2);
    root = root->insert(1, 0);
    root = root->insert(1, 2);
    root = root->insert(1, 4);
    root = root->insert(1, 6);
    root = root->insert(1, 8);
    root = root->insert(1, 10);
    root = root->insert(1, 12);
    root = root->insert(1, 14);
    assert(root->getSum(root->find(0)) == 0);
    assert(root->getSum(root->find(2)) == 0);
    assert(root->getSum(root->find(4)) == 0);
    assert(root->getSum(root->find(6)) == 0);
    assert(root->getSum(root->find(8)) == 0);
    assert(root->getSum(root->find(10)) == 0);
    assert(root->getSum(root->find(12)) == 0);
    assert(root->getSum(root->find(14)) == 0);
    assert(root->getSum(root->find(1)) == 0);
    assert(root->getSum(root->find(3)) == 3);
    assert(root->getSum(root->find(5)) == 3);
    assert(root->getSum(root->find(7)) == 4);
    assert(root->getSum(root->find(9)) == 3);
    assert(root->getSum(root->find(11)) == 5);
    assert(root->getSum(root->find(13)) == 2);
    root = root->insert(1, 15);
    root = root->insert(1, 16);
    assert(root->getSum(root->find(0)) == 0);
    assert(root->getSum(root->find(2)) == 0);
    assert(root->getSum(root->find(4)) == 0);
    assert(root->getSum(root->find(6)) == 0);
    assert(root->getSum(root->find(8)) == 0);
    assert(root->getSum(root->find(10)) == 0);
    assert(root->getSum(root->find(12)) == 0);
    assert(root->getSum(root->find(14)) == 0);
    assert(root->getSum(root->find(1)) == 0);
    assert(root->getSum(root->find(3)) == 3);
    assert(root->getSum(root->find(5)) == 3);
    assert(root->getSum(root->find(7)) == 4);
    assert(root->getSum(root->find(9)) == 3);
    assert(root->getSum(root->find(11)) == 5);
    assert(root->getSum(root->find(13)) == 2);
    assert(root->getSum(root->find(15)) == 0);
    assert(root->getSum(root->find(16)) == 0);
    root->addPrize(4, 18);
    root->addPrize(-4, 17);
    assert(root->getSum(root->find(0)) == 0);
    assert(root->getSum(root->find(2)) == 0);
    assert(root->getSum(root->find(4)) == 0);
    assert(root->getSum(root->find(6)) == 0);
    assert(root->getSum(root->find(8)) == 0);
    assert(root->getSum(root->find(10)) == 0);
    assert(root->getSum(root->find(12)) == 0);
    assert(root->getSum(root->find(14)) == 0);
    assert(root->getSum(root->find(1)) == 0);
    assert(root->getSum(root->find(3)) == 3);
    assert(root->getSum(root->find(5)) == 3);
    assert(root->getSum(root->find(7)) == 4);
    assert(root->getSum(root->find(9)) == 3);
    assert(root->getSum(root->find(11)) == 5);
    assert(root->getSum(root->find(13)) == 2);
    assert(root->getSum(root->find(15)) == 0);
    assert(root->getSum(root->find(16)) == 0);
}

void unitestPrizeTree3(){
    PrizeTree<int, int>* root = new PrizeTree<int,int>();
    root = root->insert(1, 7);
    root->addPrize(4, 8);
    root->addPrize(-4, 6);
    assert(root->getSum(root->find(7)) == 4);
    root->addPrize(4, 7);
    root->addPrize(-4, 6);
    assert(root->getSum(root->find(7)) == 4);
    root->addPrize(4, 8);
    root->addPrize(-4, 7);
    assert(root->getSum(root->find(7)) == 8);
}

void unitestRecordCompany(){
    RecordsCompany* rc = new RecordsCompany();
    rc->addCostumer(45115, 1108);
    rc->addCostumer(18904, 94069);
    Output_t<int> phone = rc->getPhone(18904);
    assert(phone.ans() == 94069);
    int arr[40] = {19, 16, 5, 10, 5, 2, 9, 5, 8, 9, 15, 8, 8, 8, 11, 14, 4, 19, 9, 16, 2, 11, 3, 6, 7, 4, 17, 10, 11, 4, 17, 12, 7, 3, 6, 4, 5, 1, 5, 4};
    rc->newMonth(arr, 40);
    rc->putOnTop(3, 28);
}

int main(){
    // unitestHT();
    // unitestHT2();
    // unitestHT3();
    // unitestHT4();
    // unitestsUF();
    // unitestsUF2();
    // unitestsUF3();
    // unitestPrizeTree();
    // unitestPrizeTree2();
    // unitestPrizeTree3();
    unitestRecordCompany();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
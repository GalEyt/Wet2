
#ifndef HASH_TABLE
#define HASH_TABLE
#include "AVLTree.h"
using namespace std;


template <class Key, class T>
class HashTable{
private:
        int elementCount = 0;
        AVLTree<T, Key>** table;
        int tableSize = 2;

    bool checkForExpansion(){
        return elementCount == tableSize;
    }

    void expand(){
        changeSize(tableSize*2, tableSize);
    }

    bool checkForShrink(){
        return tableSize != 2 && elementCount == tableSize/4;
    }

    void shrink(){
        changeSize(tableSize/2, tableSize);
    }

    void arrayInit(AVLTree<T, Key>** array, int size){
        for (int i = 0; i < size; i++)
        {
            array[i] = new AVLTree<T, Key>();
        }
    }

    void changeSize(int size, int oldSize){
        AVLTree<T, Key>* newTable[size];
        arrayInit(newTable, size);
        tableSize = size;
        for (int i=0; i<oldSize; i++){
            while (table[i] && table[i]->getHeight() != -1){
                Key rootID = table[i]->getID();
                if (!newTable[hushFunk(rootID)]){
                    newTable[hushFunk(rootID)] = new AVLTree<T, Key>();
                }
                newTable[hushFunk(rootID)] = newTable[hushFunk(rootID)]->insert(table[i]->getData(), rootID);
                table[i] = table[i]->remove(rootID);
            }
            //delete table[i];
        }
        delete[] table;
        table = newTable;
    }

    int hushFunk(Key key){
        return key % tableSize;
    }

public:
        HashTable(){
            table = new AVLTree<T, Key>*(new AVLTree<T, Key>());
            table[1] = new AVLTree<T, Key>();
        }

        void addElement(T elem, Key key){
            if (checkForExpansion()){
                expand();
            }
            if (!table[hushFunk(key)]){
                table[hushFunk(key)] = new AVLTree<T, Key>();
            }
            table[hushFunk(key)] = table[hushFunk(key)]->insert(elem, key);
            elementCount++;
        }

        void removeElement(Key key){
            if (checkForShrink()){
                shrink();
            }
            if (!table[hushFunk(key)]){
                throw NotFound();
            }
            table[hushFunk(key)] = table[hushFunk(key)]->remove(key);
            elementCount--;
        }

        void getElement(Key key){
            if (!table[hushTable(key)]){
                throw NotFound();
            }
            return table[hushTable(key)]->find(key);
        }

};

#endif //HASH_TABLE
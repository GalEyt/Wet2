
#ifdef HASH_TABLE
#define HASH_TABLE
#include "AVLTree.h"
using namespace std;

template <class Key, class T>
class HashTable{
    private:
        int elementCount = 0;
        AVLTree<T, Key>* table[] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
        int tableSize = 8;

    bool checkForExpansion(){
        return elementCount == tableSize;
    }

    void expand(){
        AVLTree<T, Key>* newTable[tableSize*2];
        for (int i=0; i<tableSize; i++){
            while (table[i] && table[i].getHeight() != -1){
                Key rootID = table[i].getID();
                if (!newTable[hushFunkExpand(rootID)]){
                    newTable[hushFunkExpand(rootID)] = new AVLTree<T, Key>();
                }
                newTable[hushFunkExpand(rootID)].insert(table[i].getData(), rootID);
                table[i].remove(rootID);
            }
            //delet table[i];
        }
        delete[] table;
        tableSize *= 2;
        table = newTable;
    }

    bool checkForShrink(){
        return tableSize != 8 && elementCount == tableSize/4;
    }

    void shrink(){
        AVLTree<T, Key>* newTable[tableSize/2];
        for (int i=0; i<tableSize; i++){
            while (table[i] && table[i].getHeight() != -1){
                Key rootID = table[i].getID();
                if (!newTable[hushFunkShrink(rootID)]){
                    newTable[hushFunkShrink(rootID)] = new AVLTree<T, Key>();
                }
                newTable[hushFunkShrink(rootID)].insert(table[i].getData(), rootID);
                table[i].remove(rootID);
            }
            //delet table[i];
        }
        delete[] table;
        tableSize /= 2;
        table = newTable;
    }

    int hushFunk(Key key){
        return key % tableSize;
    }

    int hushFunkExpand(Key key){
        return key % tableSize*2;
    }

    int hushFunkShrink(Key key){
        return key % tableSize/2;
    }

    public:
        HashTable() = default;

        void addElement(T elem, Key key){
            if (checkForExpansion()){
                expand();
            }
            if (!table[hushTable(key)]){
                table[hushTable(key)] = new AVLTree<T, Key>();
            }
            table[hushTable(key)].insert(elem, key);
            elementCount ++;
        }

        void removeElement(Key key){
            if (checkForShrink()){
                shrink();
            }
            if (!table[hushTable(key)]){
                throw notFound();
            }
            table[hushTable(key)].remove(key);
            elementCount --;
        }

        void getElement(Key key){
            if (!table[hushTable(key)]){
                throw notFound();
            }
            return table[hushTable(key)].find(key);
        }



};

#endif //HASH_TABLE
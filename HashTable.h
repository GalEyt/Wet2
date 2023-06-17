
#ifndef HASH_TABLE
#define HASH_TABLE
#include "AVLTree.h"
using namespace std;

template <class Key, class T>
class HashTable
{
private:
    int elementCount;
    AVLTree<T, Key> **table;
    int tableSize;

    bool checkForExpansion()
    {
        return elementCount == tableSize;
    }

    void expand()
    {
        changeSize(tableSize * 2, tableSize);
    }

    bool checkForShrink()
    {
        return tableSize != 2 && elementCount == tableSize / 4;
    }

    void shrink()
    {
        changeSize(tableSize / 2, tableSize);
    }

    void arrayInit(AVLTree<T, Key> **array, int size)
    {
        for (int i = 0; i < size; i++)
        {
            array[i] = new AVLTree<T, Key>();
        }
    }

    void changeSize(int size, int oldSize)
    {
        // AVLTree<T, Key> **newTable = (AVLTree<T, Key> **)malloc(sizeof(AVLTree<T, Key> *) * size);
        AVLTree<T, Key> **newTable = new AVLTree<T, Key> *[size];
        arrayInit(newTable, size);
        tableSize = size;
        for (int i = 0; i < oldSize; i++)
        {
            while (table[i] && table[i]->getHeight() != -1)
            {
                Key rootID = table[i]->getID();
                newTable[hushFunk(rootID)] = newTable[hushFunk(rootID)]->insert(table[i]->getData(), rootID);
                table[i] = table[i]->remove(rootID);
            }
        }
        for (int i = 0; i < oldSize; i++)
        {
            if (table[i])
            {
                table[i]->deleteTree(table[i]);
            }
        }
        delete[] table;
        table = newTable;
    }

    int hushFunk(Key key)
    {
        return key % tableSize;
    }

public:
    HashTable() : elementCount(0), tableSize(2)
    {
        table = new AVLTree<T, Key> *[2];
        table[0] = new AVLTree<T, Key>();
        table[1] = new AVLTree<T, Key>();
    }

    ~HashTable()
    {
        for (int i = 0; i < tableSize; i++)
        {
            table[i]->deleteTree(table[i]);
        }
        delete[] table;
        // free(table);
    }

    void addElement(T elem, Key key)
    {
        if (checkForExpansion())
        {
            expand();
        }
        table[hushFunk(key)] = table[hushFunk(key)]->insert(elem, key);
        elementCount++;
    }

    void removeElement(Key key)
    {
        if (checkForShrink())
        {
            shrink();
        }
        if (!table[hushFunk(key)])
        {
            throw NotFound();
        }
        table[hushFunk(key)] = table[hushFunk(key)]->remove(key);
        elementCount--;
    }

    T getElement(Key key)
    {
        return table[hushFunk(key)]->find(key)->getData();
    }

    AVLTree<T, Key> **getTable()
    {
        return table;
    }

    int getSize()
    {
        return tableSize;
    }

    void reset()
    {
        for (int i = 0; i < tableSize; i++)
        {
            table[i]->deleteTree(table[i]);
        }
        // free(table);
        delete[] table;
        table = new AVLTree<T, Key> *[2];
        // table = (AVLTree<T, Key> **)malloc(sizeof(AVLTree<T, Key> *) * 2);
        table[0] = new AVLTree<T, Key>();
        table[1] = new AVLTree<T, Key>();
        tableSize = 2;
        elementCount = 0;
    }
};

#endif // HASH_TABLE
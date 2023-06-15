#ifndef UNION_FIND
#define UNION_FIND
#include <cassert>
#include <memory>

template<class T>
struct rootPair{
    T* root;
    int rSum;

    rootPair(T* root, int rSum) : root(root), rSum(rSum){}
};

class Group
{
private:
    int ID;
    int groupCount;
    int groupHeight;

public:
    Group(int id, int height) : ID(id), groupCount(1), groupHeight(height) {}
    int getID() { return ID; }
    int getHeight() const { return groupHeight; }
    void addHeight(int height) { groupHeight += height; }
    void setID(int id)
    {
        ID = id;
    }
    int getGroupCount() { return groupCount; }
    void addGroupCount(int num)
    {
        groupCount += num;
    }
};

template <class T>
class Element
{
private:
    int ID;
    int distanceFromRoot;
    std::shared_ptr<Group> group;
    Element<T> *next;
    T data;
    int height;
    int r;

public:
    Element(int id, T data, int groupID, int height) : ID(id), distanceFromRoot(0), group(nullptr), next(nullptr), data(data), height(height), r(0)
    {
        group = std::shared_ptr<Group>(new Group(groupID, height));
    }

    bool isRoot()
    {
        return distanceFromRoot == 0;
    }

    int getHeight() const
    {
        return height;
    }
    int getR() const
    {
        return r;
    }
    void addToR(int rNew)
    {
        r += rNew;
    }
    void setR(int rNew)
    {
        r = rNew;
    }
    void setNext(Element<T> *next)
    { // next should be root!!!
        if (group)
        {
            if (next->isRoot())
            {
                next->group->addGroupCount(group->getGroupCount());
                next->group->addHeight(group->getHeight());
                next->group->setID(int(string(group->getID()) + string(next->group->getID())));
            }
        }
        this->next = next;
        distanceFromRoot = next->distanceFromRoot + 1;
        group = nullptr;
    }

    Element<T> *getRoot()
    {
        Element<T> *it = this;
        while (!it->isRoot())
        {
            it = it->next;
        }
        return it;
    }
    rootPair<Element<T> > getRootAndR()
    {
        Element<T> *it = this;
        int rSum = 0;
        while (!it->isRoot())
        {
            rSum+= it->getR();
            it = it->next;
        }
        return rootPair<Element<T> >(it, rSum);
    }

    int getDistance()
    {
        return distanceFromRoot;
    }

    std::shared_ptr<Group> getGroup()
    {
        Element<T> *Root = getRoot();
        return Root->group;
    }

    Element<T> *getNext() { return next; }

    int getID() { return ID; }
};

template <class T>
class UnionFind
{
private:
    Element<T>** elements;
    int amount;

    void unionhelper(Element<T> *elem, Element<T> *root)
    {
        elem->setNext(root);
    }

public:
    UnionFind() : elements(nullptr), amount(0) {}

    UnionFind(T *t, int *heights, int amount)
    {
        elements = (Element<T>**)malloc(sizeof(Element<T>**)*amount);
        for (int i = 0; i < amount; i++)
        {
            elements[i] = new Element<T>(i, t[i], i, heights[i]);
        }
    }

    ~UnionFind(){
        delete[] elements;
    //     for(int i = 0; i < amount; i++){
    //         delete elements[i];
    //     }
    //     free(elements);
    }

    int find(int elementID)
    {
        rootPair<Element<T> > root = elements[elementID]->getRootAndR();
        Element<T> *it = elements[elementID];
        Element<T> *tmp;
        int rTmp;

        while (!it->isRoot())
        {
            rTmp = it->getR();
            tmp = it->getNext();
            it->setNext(root.root);
            it->setR(root.rSum);
            root.rSum-=rTmp;
            it = tmp;
        }
        return root.root->getGroup()->getID();
    }

    int getHeight(int elemID){
        find(elemID);
        Element<T> *elem = elements[elemID];
        if(elem->isRoot()){
            return elem->getR();
        }
        return elem->getR()+elem->getNext()->getR();
    }

    void unionGroups(int id1, int id2)
    { // id1's group onTop of id2's group
        Element<T> *root1 = elements[id1]->getRoot();
        Element<T> *root2 = elements[id2]->getRoot();
        if (find(root1->getID()) == find(root2->getID()))
        {
            return;
        }

        if (root1->getGroup()->getGroupCount() < root2->getGroup()->getGroupCount())
        {
            root1->addToR(root2->getGroup()->getHeight() - root2->getR());
            unionhelper(root1, root2);
        }
        else
        {
            root1->addToR(root2->getGroup()->getHeight());
            root2->addToR(-1 * root1->getR());
            unionhelper(root2, root1);
        }
    }

    void update(T *t, int amount){
        delete[] elements;
        elements = (Element<T>**)malloc(sizeof(Element<T>**)*amount);
        for (int i = 0; i < amount; i++)
        {
            elements[i] = new Element<T>(i, t[i], i, t[i]);
        }
    }

};

#endif // UNION_FIND

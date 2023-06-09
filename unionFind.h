#ifndef UNION_FIND
#define UNION_FIND
using namespace std;
#include <cassert>


class Group{
    private:
        int ID;
        //more param here
    public:
        Group(int id): ID(id){}
        int getID(){return ID;}
        void setID(int id){
            ID = id;
        }
};


template<class T>
class Element{
    private:
        int ID;
        int distanceFromRoot = 0;;
        Group* group;
        Element<T>* next;
        T data;
    public:
        Element(int id, T data, int groupID): ID(id), distanceFromRoot(0), group(nullptr), next(nullptr), data(data){
            group = new Group(groupID);
        }

        bool isRoot(){
            return distanceFromRoot==0;
        }

        void setNext(Element<T>* next){ //next should be root!!!
            if(group){
                delete group;
            }
            this->next = next;
            distanceFromRoot = next->distanceFromRoot+1;
        }

        Element<T>* getRoot(){
            Element<T>* it = this;
            while(!it->isRoot()){
                it = it->next;
            }
            return it;
        }

        int getDistance(){
            return distanceFromRoot;
        }

        Group* getGroup(){
            Element<T>* Root = getRoot();
            return Root->group;
        }

        Element<T>* getNext(){return next;}
};


template<class T>
class UnionFind{
    private:
        Element<T>* elements[];
        int amount;

        void unionhelper(Element<T>* elem, Element<T>* root){
            elem->setNext(root);
        }

    public:
        UnionFind(int amount, T* t){
            this->elements = new Element<T>*[amount];
            for (int i=0; i<amount; i++){
                this->elements[i] = new Element<T>(i, t[i], i);
            }
            this->amount = amount;
        }

        ~UnionFind(){
            for (int i=0; i<amount; i++){
                if (elements[i]->isRoot()){
                    delete elements[i]->getGroup();
                }
                delete elements[i];
            }
        }

        int find(int elementID){
            Element<T>* root = elements[elementID]->getRoot();
            Element<T>* it = elements[elementID];
            while (!it->isRoot()){
                it.setNext(root);
                it = it->getNext();
            }
            return root->getGroup()->getID();
        }

        void unionGroups(int id1, int id2){
            if (find(id1) == find(id2)){return;}
            if (elements[id1]->getDistance() < elements[id2]->getDistance()){
                unionhelper(elements[id2], elements[id1]->getRoot());
            }
            else{
                unionhelper(elements[id1], elements[id2]->getRoot());
            }
        }
};

#endif //UNION_FIND
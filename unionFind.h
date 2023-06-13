#ifndef UNION_FIND
#define UNION_FIND
#include <cassert>
#include <memory>


class Group{
    private:
        int ID;
        int groupCount;
        //more param here
    public:
        Group(int id): ID(id), groupCount(1){}
        int getID(){return ID;}
        void setID(int id){
            ID = id;
        }
        int getGroupCount(){return groupCount;}
        void addGroupCount(int num){
            groupCount += num;
        }
};


template<class T>
class Element{
    private:
        int ID;
        int distanceFromRoot = 0;
        std::shared_ptr<Group> group;
        Element<T>* next;
        T data;
    public:
        Element(int id, T data, int groupID): ID(id), distanceFromRoot(0), group(nullptr), next(nullptr), data(data){
            group = std::shared_ptr<Group>(new Group(groupID));
        }

        bool isRoot(){
            return distanceFromRoot==0;
        }

        void setNext(Element<T>* next){ //next should be root!!!
            if(group){
                if (next->isRoot()){
                    next->group->addGroupCount(group->getGroupCount());
                }
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

        std::shared_ptr<Group> getGroup(){
            Element<T>* Root = getRoot();
            return Root->group;
        }

        Element<T>* getNext(){return next;}

        int getID(){return ID;}
};


template<class T, int N>
class UnionFind{
    private:
        std::shared_ptr<Element<T> > elements[N];
        int amount;

        void unionhelper(std::shared_ptr<Element<T> > elem, std::shared_ptr<Element<T> > root){
            elem->setNext(root);
        }

    public:
        UnionFind(int amount, T* t){
            for (int i=0; i<amount; i++){
                elements[i] = std::shared_ptr<Element<T> >(new Element<T>(i, t[i], i));
            }
            this->amount = amount;
        }

        ~UnionFind(){
            delete[] elements;
        }

        int find(int elementID){
            Element<T>* root = elements[elementID]->getRoot();
            Element<T>* it = elements[elementID].get();
            while (!it->isRoot()){
                it->setNext(root);
                it = it->getNext();
            }
            return root->getGroup()->getID();
        }

        void unionGroups(int id1, int id2){
            Element<T>* root1 = elements[id1]->getRoot();
            Element<T>* root2 = elements[id2]->getRoot();
            if (find(root1->getID()) == find(root2->getID())){return;}
            
            if (root1->getGroup()->getGroupCount() < root2->getGroup()->getGroupCount()){
                unionhelper(root1, root2);
            }
            else{
                unionhelper(root1, root2);
            }
        }
};

#endif //UNION_FIND
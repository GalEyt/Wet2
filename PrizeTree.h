

#ifndef PRIZE_TREE
#define PRIZE_TREE
#include <iostream>
#include "AVLTree.h"
using namespace std;
#define COUNT 10

template <class T, class ID>
class PrizeTree
{
private:
	PrizeTree<T, ID> *right = nullptr;
	PrizeTree<T, ID> *left = nullptr;
	PrizeTree<T, ID> *parent = nullptr;
	int height = -1;
	int balance = 0;
    int extra = 0;
	T m_data;
	ID m_id;

	void swap(PrizeTree<T, ID> *other);
	void swapFatherRightSon();
	PrizeTree<T, ID> *getMostLeft();
	void updateHeightBalance();
	void removeRoll();
	void insertRoll();
	void updateParent(PrizeTree<T, ID> *newParent);
    
	void rollLL();
	void rollLR();
	void rollRR();
	void rollRL();
	int max(int num1, int num2);
	ID getClosest(ID id);
	bool isLeaf()
	{
		return (!right && !left);
	}

	bool isLeftSon()
	{
		// assert parent
		if (parent->left == this)
		{
			return true;
		}
		return false;
	}

	PrizeTree<T, ID> *removeLeaf()
	{
		if (!parent)
		{
			deleteTree(this);
			return nullptr;
		}
		else
		{
			if (isLeftSon())
			{
				parent->left = nullptr;
			}
			else
			{
				parent->right = nullptr;
			}
		}
		PrizeTree<T, ID> *tmpParent = parent;
		delete this;
		return tmpParent;
	}

	PrizeTree<T, ID> *removeOnlySon()
	{
		PrizeTree<T, ID> *tmp;
		if (!parent)
		{
			if (right)
			{
				right->parent = nullptr;
				tmp = right;
			}
			else
			{
				left->parent = nullptr;
				tmp = left;
			}
		}
		else
		{
			if (isLeftSon())
			{
				if (right)
				{
					parent->left = right;
					right->parent = parent;
				}
				else
				{
					parent->left = left;
					left->parent = parent;
				}
				tmp = parent;
			}
			else
			{
				if (right)
				{
					parent->right = right;
					right->parent = parent;
				}
				else
				{
					parent->right = left;
					left->parent = parent;
				}
				tmp = parent;
			}
		}
		delete this;
		return tmp;
	}

	PrizeTree<T, ID> *removeTwoSons()
	{
		PrizeTree<T, ID> *toSwitch = right->getMostLeft();
		swap(toSwitch);
		if (isLeaf())
		{
			return removeLeaf();
		}
		return removeOnlySon();
	}

	PrizeTree<T, ID> *removeHelper(ID id)
	{
		PrizeTree<T, ID> *toRoll;
		PrizeTree<T, ID> *toDelete = find(id);
		if (toDelete->isLeaf())
		{
			toRoll = toDelete->removeLeaf();
			if (!toRoll)
			{
				return new PrizeTree<T, ID>;
			}
		}
		else if (toDelete->right && toDelete->left)
		{
			toRoll = toDelete->removeTwoSons();
		}
		else
		{
			toRoll = toDelete->removeOnlySon();
		}
		toRoll->removeRoll();
		return toRoll;
	}

public:
	PrizeTree() : right(nullptr), left(nullptr), parent(nullptr), height(-1), balance(0), m_data(), m_id(), extra(0) {}
	PrizeTree(PrizeTree<T, ID> *parent, T data, ID id) : right(nullptr), left(nullptr), parent(parent), height(0), balance(0), m_data(data), m_id(id), extra(0) {}
	~PrizeTree() = default;
	void deleteTree(PrizeTree<T, ID> *root);
	PrizeTree<T, ID> *find(ID id);
    void addPrize(int prize, ID id);
	PrizeTree<T, ID> *getRoot()
	{

		if (!parent || height == -1)
		{
			return this;
		}
		return parent->getRoot();
	}
	PrizeTree<T, ID> *getRight() { return right; }
	PrizeTree<T, ID> *getLeft() { return left; }
	PrizeTree<T, ID> *getParent() { return parent; }
	T getData() { return m_data; }
	ID getID() { return m_id; }
	int getHeight() { return height; }
	int getSum(PrizeTree<T, ID> *node);
	void setExtra(int extra) { this->extra = extra; }
	// Function to print binary tree in 2D
	// It does reverse inorder traversal
	void print2DUtil(PrizeTree<int, int> *root, int space)
	{
		// Base case
		if (root == NULL)
			return;

		// Increase distance between levels
		space += COUNT;

		// Process right child first
		print2DUtil(root->right, space);

		// Print current node after space
		// count
		cout << endl;
		for (int i = COUNT; i < space; i++)
			cout << " ";
		cout << root->m_id << "\n";

		// Process left child
		print2DUtil(root->left, space);
	}

	// Wrapper over print2DUtil()
	void print2D(PrizeTree<int, int> *root)
	{
		// Pass initial space count as 0
		print2DUtil(root, 0);
	}

	void printTreeInOrder()
	{
		if (left)
		{
			left->printTreeInOrder();
		}
		std::cout << m_id << " "; // << "balance: " << balance << "\n";
		if (balance >= 2 || balance <= -2)
		{
			std::cout << " BalanceError " << balance;
		}
		if (right)
		{
			right->printTreeInOrder();
		}
	}
	void printTreePreOrder()
	{
		std::cout << "id: " << m_id; // << "balance: " << balance << "\n";

		if (left)
		{
			left->printTreePreOrder();
		}
		if (right)
		{
			right->printTreePreOrder();
		}
	}

	PrizeTree<T, ID> *insert(T data, ID id)
	{
		insertHelper(data, id);
		return getRoot();
	}

	void insertHelper(T data, ID id)
	{
		if (height == -1)
		{
			m_data = data;
			m_id = id;
			height++;
			return;
		}
		if (m_id < id)
		{
			if (!right)
			{
				right = new PrizeTree<T, ID>(this, data, id);
                right->extra = -1 * right->getSum(right);
				right->insertRoll();
			}
			else
			{
				right->insert(data, id);
			}
		}
		else if (m_id == id)
		{
			throw Exist();
		}
		else
		{
			if (!left)
			{
				left = new PrizeTree<T, ID>(this, data, id);
                left->extra = -1 * left->getSum(left);
				left->insertRoll();
			}
			else
			{
				left->insert(data, id);
			}
		}
	}

	PrizeTree<T, ID> *remove(ID id)
	{
		PrizeTree<T, ID> *tmp = removeHelper(id);
		return tmp->getRoot();
	}
};

template <class T, class ID>
PrizeTree<T, ID> *PrizeTree<T, ID>::find(ID id)
{
	if (height == -1)
	{
		throw EmptyTree();
	}
	if (m_id == id)
	{
		return this;
	}
	if (m_id < id)
	{
		if (!right)
		{
			throw NotFound();
		}
		return right->find(id);
	}
	if (!left)
	{
		throw NotFound();
	}
	return left->find(id);
}




template <class T, class ID>
inline void PrizeTree<T, ID>::addPrize(int prize, ID id)
{
	bool rightS = false;
	PrizeTree<T, ID>* it = this;
    while(it){
		if (it->m_id < id){
			if(!rightS){
				it->extra+= prize;
				rightS=true;
			}
			it = it->right;
			continue;
		}
		if(it->m_id > id){
			if(rightS){
				it->extra-=prize;
				rightS = false;
			}
			it = it->left;
			continue;
		}
		if(rightS){
			it->extra-=prize;
		}
		if(it->left){
			it->left->extra+= prize;
			
		}
		
		break;
	}
}

template <class T, class ID>
void PrizeTree<T, ID>::swapFatherRightSon()
{
	PrizeTree<T, ID> *son = right;
	PrizeTree<T, ID> *sonRight = son->right;
	PrizeTree<T, ID> *tmpLeft = left;
	PrizeTree<T, ID> *tmpParent = parent;
	son->updateParent(tmpParent);
	parent = son;
	son->right = this;
	son->left = tmpLeft;
	tmpLeft->updateParent(son);
	left = nullptr;
	right = sonRight;
	if (sonRight)
	{
		sonRight->updateParent(this);
	}
	updateHeightBalance();
	son->updateHeightBalance();
}

template <class T, class ID>
void PrizeTree<T, ID>::swap(PrizeTree<T, ID> *other)
{
	if (right == other)
	{
		swapFatherRightSon();
		return;
	}
	PrizeTree<T, ID> *tmpLeftA = left;
	PrizeTree<T, ID> *tmpRightA = right;
	PrizeTree<T, ID> *tmpParentA = parent;
	PrizeTree<T, ID> *tmpRightB = other->right;
	PrizeTree<T, ID> *tmpParentB = other->parent;
	left = other->left; // should be null
	right = tmpRightB;
	if (tmpRightB)
	{
		tmpRightB->updateParent(this);
	}
	updateParent(tmpParentB);
	tmpLeftA->updateParent(other);
	tmpRightA->updateParent(other);
	other->updateParent(tmpParentA);
	updateHeightBalance();
	other->updateHeightBalance();
}

template <class T, class ID>
int PrizeTree<T, ID>::max(int num1, int num2)
{
	return num1 > num2 ? num1 : num2;
}

template <class T, class ID>
void PrizeTree<T, ID>::updateHeightBalance()
{
	if (left && right)
	{
		height = PrizeTree::max(left->height, right->height) + 1;
		balance = left->height - right->height;
	}
	else if (left)
	{
		height = left->height + 1;
		balance = height;
	}
	else if (right)
	{
		height = right->height + 1;
		balance = height * (-1);
	}
	else
	{
		height = 0;
		balance = 0;
	}
}

template <class T, class ID>
void PrizeTree<T, ID>::insertRoll()
{
	updateHeightBalance();
	if (balance > -2 && balance < 2)
	{
		if (parent)
		{
			parent->insertRoll();
		}
	}
	else
	{
		if (balance == 2)
		{
			if (left->balance == 1)
			{
				rollLL();
			}
			else
			{
				rollLR();
			}
		}
		else if (balance == -2)
		{
			if (right->balance == 1)
			{
				rollRL();
			}
			else
			{
				rollRR();
			}
		}
	}
}

template <class T, class ID>
void PrizeTree<T, ID>::rollLL()
{
	PrizeTree<T, ID> *A = left;
	PrizeTree<T, ID> *parentB = parent;
	PrizeTree<T, ID> *AR = A->right;
    int sum = parentB->getSum(parentB);
    int realExtraB = sum + this->extra;
    int realExtraA = realExtraB + A->extra;
	int realExtraAR;
    
    A->extra = realExtraA - sum;
    this->extra = realExtraB - sum - A->extra;
    
	A->updateParent(parentB);
	updateParent(A);
	if (AR)
	{
		AR->updateParent(this);
		realExtraAR = realExtraA + AR->extra;
		AR->extra = realExtraAR - sum - A->extra - this->extra; 
	}
	else
	{
		left = nullptr;
	}
	updateHeightBalance();
	A->updateHeightBalance();
}

template <class T, class ID>
void PrizeTree<T, ID>::rollRR()
{
	PrizeTree<T, ID> *A = right;
	PrizeTree<T, ID> *parentB = parent;
	PrizeTree<T, ID> *AL = A->left;
    int sum = parentB->getSum(parentB);
    int realExtraB = sum + this->extra;
    int realExtraA = realExtraB + A->extra;
	int realExtraAL;

    A->extra = realExtraA - sum;
    this->extra = realExtraB - sum - A->extra;
    
	A->updateParent(parentB);
	updateParent(A);
	if (AL)
	{
		AL->updateParent(this);
		realExtraAL = realExtraA + AL->extra;
		AL->extra = realExtraAL - sum - A->extra - this->extra; 
	}
	else
	{
		right = nullptr;
	}
	updateHeightBalance();
	A->updateHeightBalance();
}

template <class T, class ID>
void PrizeTree<T, ID>::rollLR()
{
	left->rollRR();
	rollLL();
}

template <class T, class ID>
void PrizeTree<T, ID>::rollRL()
{
	right->rollLL();
	rollRR();
}

template <class T, class ID>
void PrizeTree<T, ID>::removeRoll()
{
	updateHeightBalance();
	if (balance == 2)
	{
		if (left->balance >= 0)
		{
			rollLL();
		}
		else
		{
			rollLR();
		}
	}
	else if (balance == -2)
	{
		if (right->balance == 1)
		{
			rollRL();
		}
		else
		{
			rollRR();
		}
	}
	if (parent)
	{
		parent->removeRoll();
	}
}

template <class T, class ID>
void PrizeTree<T, ID>::deleteTree(PrizeTree<T, ID> *root)
{
	if (!root)
	{
		throw EmptyTree();
	}
	if (root->left)
	{
		if (!root->left->isLeaf())
		{
			deleteTree(root->left);
		}
		else
		{
			delete root->left;
		}

		root->left = nullptr;
	}
	if (root->right)
	{
		if (!root->right->isLeaf())
		{
			deleteTree(root->right);
		}
		else
		{
			delete root->right;
		}
		root->right = nullptr;
	}
	delete root;
	root = nullptr;
}

template <class T, class ID>
PrizeTree<T, ID> *PrizeTree<T, ID>::getMostLeft()
{
	if (!left)
	{
		return this;
	}
	return left->getMostLeft();
}

template <class T, class ID>
void PrizeTree<T, ID>::updateParent(PrizeTree<T, ID> *newParent)
{
	parent = newParent;
	if (!newParent)
	{
		return;
	}
	if (m_id < newParent->m_id)
	{
		newParent->left = this;
	}
	else
	{
		newParent->right = this;
	}
}

template <class T, class ID>
inline int PrizeTree<T, ID>::getSum(PrizeTree<T, ID> *node)
{
    int tmp = 0;
    while(node){
        tmp+= node->extra;
        node = node->parent;
    }
    return tmp;
}

#endif // PRIZE_TREE
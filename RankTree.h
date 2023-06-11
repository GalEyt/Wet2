

#ifndef RANK_TREE
#define RANK_TREE
#include <iostream>
using namespace std;
#define COUNT 10


template <class T, class ID>
class RankTree
{
private:
    class Exist
    {
    };
    class EmptyTree
    {
    };
    class NotFound
    {
    };
	RankTree<T, ID> *right = nullptr;
	RankTree<T, ID> *left = nullptr;
	RankTree<T, ID> *parent = nullptr;
	int height = -1;
	int balance = 0;
    int subTreeSize = 0;
	T m_data;
	ID m_id;

	void swap(RankTree<T, ID> *other);
	void swapFatherRightSon();
	RankTree<T, ID> *getMostLeft();
	void updateHeightBalance();
	void removeRoll();
	void insertRoll();
	void updateParent(RankTree<T, ID> *newParent);
	void rollLL();
	void rollLR();
	void rollRR();
	void rollRL();
	int max(int num1, int num2);
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

	RankTree<T, ID> *removeLeaf()
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
		RankTree<T, ID> *tmpParent = parent;
		delete this;
		return tmpParent;
	}

	RankTree<T, ID> *removeOnlySon()
	{
		RankTree<T, ID> *tmp;
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

	RankTree<T, ID> *removeTwoSons()
	{
		RankTree<T, ID> *toSwitch = right->getMostLeft();
		swap(toSwitch);
		if (isLeaf())
		{
			return removeLeaf();
		}
		return removeOnlySon();
	}

	RankTree<T, ID> *removeHelper(ID id)
	{
		RankTree<T, ID> *toRoll;
		RankTree<T, ID> *toDelete = find(id);
		if (toDelete->isLeaf())
		{
			toRoll = toDelete->removeLeaf();
			if (!toRoll)
			{
				return new RankTree<T, ID>;
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
	RankTree() : right(nullptr), left(nullptr), parent(nullptr), height(-1), balance(0), m_data(), m_id() {}
	RankTree(RankTree<T, ID> *parent, T data, ID id) : right(nullptr), left(nullptr), parent(parent), height(0), balance(0), m_data(data), m_id(id) {}
	~RankTree() = default;
	void deleteTree(RankTree<T, ID> *root);
	RankTree<T, ID> *find(ID id);
	RankTree<T, ID> *getRoot()
	{

		if (!parent || height == -1)
		{
			return this;
		}
		return parent->getRoot();
	}
	RankTree<T, ID> *getRight() { return right; }
	RankTree<T, ID> *getLeft() { return left; }
	RankTree<T, ID> *getParent() { return parent; }
    int getSubTreeSize() const { return subTreeSize;}
	T getData() { return m_data; }
	ID getID() { return m_id; }
	int getHeight() { return height; }
    RankTree<T, ID> *findByRank(int rank) const;
	// Function to print binary tree in 2D
	// It does reverse inorder traversal
	void print2DUtil(RankTree<int, int> *root, int space)
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
	void print2D(RankTree<int, int> *root)
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

	RankTree<T, ID> *insert(T data, ID id)
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
            subTreeSize = 1;
			return;
		}
		if (m_id < id)
		{
			if (!right)
			{
				right = new RankTree<T, ID>(this, data, id);
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
				left = new RankTree<T, ID>(this, data, id);
				left->insertRoll();
			}
			else
			{
				left->insert(data, id);
			}
		}
	}

	RankTree<T, ID> *remove(ID id)
	{
		RankTree<T, ID> *tmp = removeHelper(id);
		return tmp->getRoot();
	}
};

template <class T, class ID>
RankTree<T, ID> *RankTree<T, ID>::find(ID id)
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
void RankTree<T, ID>::swapFatherRightSon()
{
	RankTree<T, ID> *son = right;
	RankTree<T, ID> *sonRight = son->right;
	RankTree<T, ID> *tmpLeft = left;
	RankTree<T, ID> *tmpParent = parent;
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
void RankTree<T, ID>::swap(RankTree<T, ID> *other)
{
	if (right == other)
	{
		swapFatherRightSon();
		return;
	}
	RankTree<T, ID> *tmpLeftA = left;
	RankTree<T, ID> *tmpRightA = right;
	RankTree<T, ID> *tmpParentA = parent;
	RankTree<T, ID> *tmpRightB = other->right;
	RankTree<T, ID> *tmpParentB = other->parent;
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
int RankTree<T, ID>::max(int num1, int num2)
{
	return num1 > num2 ? num1 : num2;
}

template <class T, class ID>
void RankTree<T, ID>::updateHeightBalance()
{
	if (left && right)
	{
		height = RankTree::max(left->height, right->height) + 1;
		balance = left->height - right->height;
        subTreeSize = 1 + left->subTreeSize + right->subTreeSize;
	}
	else if (left)
	{
		height = left->height + 1;
		balance = height;
        subTreeSize = 1 + left->subTreeSize;
	}
	else if (right)
	{
		height = right->height + 1;
		balance = height * (-1);
        subTreeSize = 1 + right->subTreeSize;
	}
	else
	{
		height = 0;
		balance = 0;
        subTreeSize = 1;
	}
}

template <class T, class ID>
void RankTree<T, ID>::insertRoll()
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
void RankTree<T, ID>::rollLL()
{
	RankTree<T, ID> *A = left;
	RankTree<T, ID> *parentB = parent;
	RankTree<T, ID> *AR = A->right;
	A->updateParent(parentB);
	updateParent(A);
	if (AR)
	{
		AR->updateParent(this);
	}
	else
	{
		left = nullptr;
	}
	updateHeightBalance();
	A->updateHeightBalance();
}

template <class T, class ID>
void RankTree<T, ID>::rollRR()
{
	RankTree<T, ID> *A = right;
	RankTree<T, ID> *parentB = parent;
	RankTree<T, ID> *AL = A->left;
	A->updateParent(parentB);
	updateParent(A);
	if (AL)
	{
		AL->updateParent(this);
	}
	else
	{
		right = nullptr;
	}
	updateHeightBalance();
	A->updateHeightBalance();
}

template <class T, class ID>
void RankTree<T, ID>::rollLR()
{
	left->rollRR();
	rollLL();
}

template <class T, class ID>
void RankTree<T, ID>::rollRL()
{
	right->rollLL();
	rollRR();
}

template <class T, class ID>
void RankTree<T, ID>::removeRoll()
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
void RankTree<T, ID>::deleteTree(RankTree<T, ID> *root)
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
RankTree<T, ID> *RankTree<T, ID>::getMostLeft()
{
	if (!left)
	{
		return this;
	}
	return left->getMostLeft();
}

template <class T, class ID>
void RankTree<T, ID>::updateParent(RankTree<T, ID> *newParent)
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
int getRankOfClosetMatch(RankTree<T, ID>* root,ID id, bool fromAbove)
{
    if (root->getHeight() == -1)
	{
		throw EmptyTree();
	}
	if (root->getID() == id)
	{
		return this;
	}
	if (root->getID() < id)
	{
		if (!root->getRight())
		{
			if(from)
		}
		return root->getRight()->find(id);
	}
	if (!root->getLeft())
	{
		throw NotFound();
	}
	return root->getLeft()->find(id);
}

template <class T, class ID>
RankTree<T, ID> *RankTree<T, ID>::findByRank(int rank) const
{
    
}


#endif // RANK_TREE
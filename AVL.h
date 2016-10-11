#include "Searching.h"
#include <algorithm>

class AVLNode
{
public:
	Company *comp = NULL;
	AVLNode *rightChild;
	AVLNode *leftChild;

	AVLNode(Company* company)
	{
		comp = company;
		rightChild = NULL;
		leftChild = NULL;
	}
};

class AVLTree
{
	public:
		AVLNode *root = NULL;

	AVLTree()
	{}

	~AVLTree()
	{}

	int calculateHeight(AVLNode* node)
	{
		int leftHeight, rightHeight;
		int height = 0;
		if (node != NULL)
		{
			leftHeight = calculateHeight(node->leftChild);
			rightHeight = calculateHeight(node->rightChild);
			return max(leftHeight, rightHeight) + 1;
		}
		return height;
	}

	int balanceFactor(AVLNode* node)
	{
		if (node != NULL)
			return calculateHeight(node->rightChild) - calculateHeight(node->leftChild);
		else
			return 0;
	}

	AVLNode* rotateLeft(AVLNode* root)
	{
		AVLNode *pivot = new AVLNode(NULL);
		pivot = root->rightChild;
		root->rightChild = pivot->leftChild;
		pivot->leftChild = root;
		return pivot;
	}

	AVLNode* rotateRight(AVLNode* root)
	{
		AVLNode *pivot = new AVLNode(NULL);
		pivot = root->leftChild;
		root->leftChild = pivot->rightChild;
		pivot->rightChild = root;
		return pivot;
	}


	AVLNode* balancer(AVLNode* node)
	{
		if (balanceFactor(node)> 1)
		{
			if (balanceFactor(node->rightChild) < 0)
				node->rightChild = rotateRight(node->rightChild);
			return rotateLeft(node);
		}
		if (balanceFactor(node) < -1)
		{
			if (balanceFactor(node->leftChild)>0)
				node->leftChild =rotateLeft(node->leftChild);
			return rotateRight(node);
		}
		return node;
	}

	AVLNode* insert(AVLNode* root, Company* company)
	{			
		if (!root)
		{
			AVLNode *node = new AVLNode(company);
			return node;
		}
		else if (company->id < root->comp->id)
		{
			root->leftChild = insert(root->leftChild,company);
		}
		else if (company->id >= root->comp->id)
		{
			root->rightChild = insert(root->rightChild, company);
		}
		return  balancer(root);
	}

	void SearchAVL(AVLNode* root,int searchTerm)
	{
		if (!root)
		{
			cout << "Company Not Found" << endl;
		}
		else if (searchTerm < root->comp->id)
		{
			SearchAVL(root->leftChild, searchTerm);
		}
		else if (searchTerm > root->comp->id)
		{
			SearchAVL(root->rightChild, searchTerm);
		}
		else if (searchTerm == root->comp->id)
		{
			 root->comp->printInfo();
		}		
	}

	AVLNode* minValueNode(AVLNode* node)
	{
		AVLNode* temp = new AVLNode(NULL);
		temp = node;
		while (temp->leftChild != NULL)
			temp = temp->leftChild;
		return temp;
	}

	AVLNode* Delete(AVLNode* root, int searchTerm)
	{
		AVLNode* temp = new AVLNode(NULL);
		if(root==NULL)
			return root;
		if (searchTerm < root->comp->id)
			root->leftChild= Delete(root->leftChild, searchTerm);
		else if (searchTerm>root->comp->id)
			root->rightChild= Delete(root->rightChild, searchTerm);
		else 
		{
			if (root->leftChild == NULL || root->rightChild == NULL)
			{
				if (root->leftChild == NULL)
					temp = root->rightChild;
				else
					temp = root->leftChild;
				if (temp==NULL)
				{
					temp = root;
					root = NULL;
				}
				else
					root = temp;
				delete(temp);
			}
			else
			{
				temp = minValueNode(root->rightChild);
				root->comp = temp->comp;
				root->rightChild = Delete(root->rightChild, temp->comp->id);
			}
		}
		if (root == NULL)
			return root;
		return balancer(root);
	}
};
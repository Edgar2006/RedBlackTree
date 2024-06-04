#pragma once
#include "Node.h"



//Properties of Red Black Tree:
//The Red-Black tree satisfies all the properties of binary search tree in addition to that it satisfies following additional properties
//
//1. Root property: The root is black.
//2. External property: Every leaf (Leaf is a NULL child of a node) is black in Red-Black tree.
//3. Internal property: The children of a red node are black. Hence possible parent of red node is a black node.
//4. Depth property: All the leaves have the same black depth.
//5. Path property: Every simple path from root to descendant leaf node contains same number of black nodes. 

//1.	Search	O(log n)
//2.	Insert	O(log n)
//3.	Delete	O(log n)

class RedBlackTree
{
private:
	Node* m_root;

public:
	RedBlackTree();
	void inset(const int& newNodeValue);
	void deleteNode(const int& deleteNodeValue);
	bool find(const int& findNodeValue)const;
	bool ifBalanced()const;
	void print()const;

private:
	Node*& findNode(const int& findNodeValue)const;
	Node*& getUncle(Node*& r_node)const;
	Node*& getBrother(Node*& r_node)const;
	Status leftOrRightChild(Node*& r_node);
	void swapColors(Node*& r_node1, Node*& r_node2);

private:
	void addNewNode(Node*& r_newNode);
	void paintNewNode(Node*& r_node);
	void rotate(Node*& r_node);
	void rotateParentAndGrandFather(Node*& r_node, Status status);
	void rotateNodeAndParent(Node*& r_node, Status status);
	void rotate_LL(Node*& r_node);
	void rotate_LR(Node*& r_node);
	void rotate_RR(Node*& r_node);
	void rotate_RL(Node*& r_node);

private:
	void removeNode(Node*& r_deleteNode);
	void removeNodeNoChild(Node*& r_deleteNode);
	void removeNodeOneChild(Node*& r_deleteNode);
	void removeNodeTwoChild(Node*& r_deleteNode);
	void deleteFixColor(Node*& r_node, Node*& r_brother);
	void deleteFixColorCaseBrotherRed(Node* p_node, Node*& r_brother, Status brotherChildStatus, bool ifCase1);
	void deleteFixColorCaseBrother2ChildBlack(Node*& r_brother);
	void deleteFixColorCase_LL_RR(Node* p_node, Node*& r_brother, Status brotherChildStatus);
	void deleteFixColorCase_LR_RL(Node*& r_brother, Status brotherChildStatus);
	void changeColorDeleteNodeOneChild(Node*& r_deleteNode);
	void changeDeletedNodePatentChild(Node*& r_deleteNode, Node*& r_newChild);

private:
	Node* getRoot()const;
	bool ifBalancedSubTree(Node*& r_root, int& maxHeight, int& minHeight)const;
	void printSpace(double n, Node*& r_removed)const;
	int heightOfTree(Node*& r_root)const;
	void printBinaryTree(Node* p_root)const;



};


#include <iostream>
#include "RedBlackTree.h"
#include <vector>
#include <time.h> 
#include <cstdlib> 

Node* Node::null = new Node(Color::BLACK);

int main()
{
	RedBlackTree a;

	int count = 1000000;
	int count1 = count - 2;
	srand(time(0)); 

	std::vector<int>v;

	for (int i = 1; i <= count; i++)
	{
		int value = rand();
		v.push_back(value);
		a.inset(value);
		//a.print();
	}
	//for  (int i = count1; i > 0; i--)
	//{
	//	int value = v[i];
	//	a.deleteNode(value);
	//}
	//a.deleteNode(6);
	v.clear();
	//a.print();
	a.ifBalanced();


	return 0;
}

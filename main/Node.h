#pragma once


enum class Color
{
	RED,
	BLACK
};
enum class Status
{
	LEFT,
	RIGHT
};

class Node
{

private:
	Color m_color;
	int m_value;

public:
	Node* p_parent;
	Node* p_left;
	Node* p_right;
	static Node* null;
public:
	Node();

	Node(Color color);
	Node(int m_value, const Node& m_left, const Node& m_right);
	Node(int m_value);
	void operator=(const Node* anotherNode);
	bool operator >(const Node& anotherNode)const;
	bool operator <(const Node& anotherNode)const;
	bool operator <=(const Node& anotherNode)const;
	bool operator >=(const Node& anotherNode)const;


	void setColor(Color color);
	void setValue(const int value);
	Color getColor()const;
	int getValue()const;

};


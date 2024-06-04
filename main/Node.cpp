#include "Node.h"
#include <iostream>





Node::Node()
{
	this->m_value = 0;
	this->p_left = null;
	this->p_right = null;
	this->p_parent = null;
	this->m_color = Color::RED;
}


Node::Node(Color color) :Node()
{
	this->m_color = color;
}

Node::Node(int m_value) :Node()
{
	this->m_value = m_value;
}



Node::Node(int m_value, const Node& m_left, const Node& m_right) :Node(m_value)
{
	this->p_left = new Node(m_left);
	this->p_right = new Node(m_right);
}

void Node::operator=(const Node* anotherNode)
{
	this->m_value = anotherNode->m_value;
	this->m_color = anotherNode->m_color;
}

bool Node::operator>(const Node& anotherNode)const
{
	if (this->m_value > anotherNode.m_value)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Node::operator<(const Node& anotherNode)const
{
	if (this->m_value < anotherNode.m_value)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Node::operator<=(const Node& anotherNode) const
{
	if (this->m_value <= anotherNode.m_value)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Node::operator>=(const Node& anotherNode) const
{
	if (this->m_value >= anotherNode.m_value)
	{
		return true;
	}
	else
	{
		return false;
	}
}




void Node::setColor(Color color)
{
	this->m_color = color;
}

void Node::setValue(const int value)
{
	this->m_value = value;

}


Color Node::getColor()const
{
	return this->m_color;
}

int Node::getValue()const
{
	return this->m_value;
}




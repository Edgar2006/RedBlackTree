#include "RedBlackTree.h"
#include <iostream>
#include <cmath>
#include <queue>
#include <time.h> 
#include <cstdlib> 



RedBlackTree::RedBlackTree()
{
   m_root = Node::null;
}

void RedBlackTree::inset(const int& newNodeValue)
{
   Node* newNode = new Node(newNodeValue);
   if (m_root == Node::null)
   {
      newNode->setColor(Color::BLACK);
      m_root = newNode;
   }
   else
   {
      addNewNode(newNode);
   }
}

void RedBlackTree::deleteNode(const int& deleteNodeValue)
{
   Node*& deleteNode = findNode(deleteNodeValue);
   if (deleteNode == Node::null)
   {
      std::cout << "No find node with this value: "<< deleteNodeValue << std::endl;
   }
   else 
   {
      removeNode(deleteNode);
   }

}

bool RedBlackTree::find(const int& findNodeValue)const
{
   Node*& deleteNode = findNode(findNodeValue);
   if (deleteNode == Node::null)
   {
      std::cout << "No find node with this value: " << findNodeValue << std::endl;
      return 0;
   }
   else 
   {
      std::cout << "Find node with this value: " << findNodeValue << std::endl;
      return 0;
   }
}

void RedBlackTree::print()const
{
   printBinaryTree(m_root);
   this->ifBalanced();
   std::cout << std::endl;
   std::cout << std::endl;
   std::cout << std::endl;
   std::cout << std::endl;
}

bool RedBlackTree::ifBalanced() const
{
   int maxHeight = 0;
   int minHeight = 0;
   Node* p_root = m_root;
   if (ifBalancedSubTree(p_root, maxHeight, minHeight))
   {
      std::cout << "Balanced" << std::endl;
      return 1;
   }
   else
   {
      std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!No balanced" << std::endl;
      return 0;
   }
}

Node* RedBlackTree::getRoot()const
{
   return this->m_root;
}

void RedBlackTree::addNewNode(Node*& r_newNode)
{
   Node* iterator = m_root;
   Node* parent = m_root->p_parent;
   Status status = Status::LEFT;
   while (iterator != Node::null)
   {
      parent = iterator;
      if (*iterator < *r_newNode)
      {
         iterator = iterator->p_right;
         status = Status::RIGHT;
      }
      else
      {
         iterator = iterator->p_left;
         status = Status::LEFT;
      }
   }
   if (status == Status::LEFT)
   {
      parent->p_left = r_newNode;
   }
   else
   {
      parent->p_right = r_newNode;
   }
   r_newNode->p_parent = parent;

   // balance color
   paintNewNode(r_newNode);


}

void RedBlackTree::paintNewNode(Node*& r_node)
{
   if (r_node->p_parent == Node::null)// root color always black
   {
      r_node->setColor(Color::BLACK);
      return;
   }
   else
   {
      if (r_node->p_parent->getColor() == Color::RED)
      {  
         Node*& uncle(getUncle(r_node));
         if (uncle->getColor() == Color::RED)
         {
            /*   If grandfather not root change color red and call paintNewNode use argument grandfather

                              (G)B                             (G)R                    
                              /   \                           /    \
                          (P)R     (U)R                   (P)B      (U)B  
                         /                               /
                     (X)R                            (X)R
         
            */
            uncle->setColor(Color::BLACK);
            r_node->p_parent->setColor(Color::BLACK);
            if (r_node->p_parent->p_parent != m_root)
            {
               r_node->p_parent->p_parent->setColor(Color::RED);
               paintNewNode(r_node->p_parent->p_parent);
            }
         }
         else
         {
            rotate(r_node);
         }
      }
   }

}

Node*& RedBlackTree::getUncle(Node*& r_node)const
{
   return getBrother(r_node->p_parent);
}

Node*& RedBlackTree::getBrother(Node*& r_node)const
{
   Node*& p_parent = r_node->p_parent;
   if (p_parent->p_left != r_node)
   {
      return p_parent->p_left;
   }
   else
   {
      return p_parent->p_right;
   }
}

void RedBlackTree::swapColors(Node*& r_node1, Node*& r_node2)
{
   Color color1 = r_node1->getColor();
   r_node1->setColor(r_node2->getColor());
   r_node2->setColor(color1);
}

Node*& RedBlackTree::findNode(const int& findNodeValue)const
{
   Node* p_iterator = m_root;
   while (p_iterator != Node::null)
   {
      if (p_iterator->getValue() == findNodeValue) 
      {
         break;
      }
      if (p_iterator->getValue() < findNodeValue)
      {
         p_iterator = p_iterator->p_right;
      }
      else
      {
         p_iterator = p_iterator->p_left;
      }
   }
   return p_iterator;

}

Status RedBlackTree::leftOrRightChild(Node*& r_node)
{
   if (r_node->p_parent->p_left == r_node)
   {
      return Status::LEFT;
   }
   else
   {
      return Status::RIGHT;
   }
}

void RedBlackTree::rotate(Node*& r_node)
{
   if (leftOrRightChild(r_node->p_parent) == Status::LEFT)
   {
      if (leftOrRightChild(r_node) == Status::LEFT)
      {
         rotate_LL(r_node);
      }
      else
      {
         rotate_LR(r_node);
      }
   }
   else
   {
      if (leftOrRightChild(r_node) == Status::RIGHT)
      {
         rotate_RR(r_node);
      }
      else
      {
         rotate_RL(r_node);
      }
   }

}

void RedBlackTree::rotate_LL(Node*& r_node)
{
   rotateParentAndGrandFather(r_node, Status::LEFT);
}

void RedBlackTree::rotate_LR(Node*& r_node)
{
/*   

                 (G)B                      (G)B                        (X)B     
                /    \                    /    \                      /    \
            (P)R      (U)B            (X)R      (U)B              (P)R      (G)R   
                \                    /                                          \
                 (X)R            (P)R                                            (U)B   
         
*/

   Node* p_patentNode = r_node->p_parent;
   rotateNodeAndParent(r_node, Status::LEFT);
   rotate_LL(p_patentNode);
}

void RedBlackTree::rotate_RR(Node*& r_node)
{
   rotateParentAndGrandFather(r_node, Status::RIGHT);
}

void RedBlackTree::rotate_RL(Node*& r_node)
{
/*   

            (G)B                      (G)B                             (X)B     
            /    \                    /   \                           /    \
         (U)B      (P)R            (U)B    (X)R                   (G)R      (P)R   
                  /                            \                 /
              (X)R                              (P)R         (U)B  
         
*/
   Node* p_patentNode = r_node->p_parent;
   rotateNodeAndParent(r_node, Status::RIGHT);
   rotate_RR(p_patentNode);



}

void RedBlackTree::rotateParentAndGrandFather(Node*& r_node, Status status)
{
/* 
   if x and parent left child need left rotation

                  (G)B                             (P)B                    
                 /    \                           /    \
             (P)R      (U)B                   (X)R      (G)R  
            /                                               \
        (X)R                                                 (U)B

*/
/* 

   if x and parent right child need right rotation

 
               (G)B                                   (P)B                    
               /    \                                 /   \
           (U)B      (P)R                         (G)R     (X)R  
                         \                       /
                          (X)R               (U)B    

*/

   Node*& r_parent = r_node->p_parent;
   Node*& r_grandFather = r_node->p_parent->p_parent;
   
   if (leftOrRightChild(r_grandFather) == Status::LEFT)
   {
      r_grandFather->p_parent->p_left = r_parent;
   }
   else
   {
      r_grandFather->p_parent->p_right = r_parent;
   }
   
   if (status == Status::RIGHT) {
      r_grandFather->p_right = r_parent->p_left;
      r_parent->p_left->p_parent = r_grandFather;
      r_parent->p_left = r_grandFather;
   }
   else
   {
      r_grandFather->p_left = r_parent->p_right;
      r_parent->p_right->p_parent = r_grandFather;
      r_parent->p_right = r_grandFather;
   }

   Node* p_grandFather = r_grandFather;
   r_parent->p_parent = r_grandFather->p_parent;
   p_grandFather->p_parent = r_parent;
   if (p_grandFather == m_root)
   {
      m_root = r_parent;
   }
   swapColors(r_parent, p_grandFather);
}

void RedBlackTree::rotateNodeAndParent(Node*& r_node, Status status)
{
/*   
      if x right child and parent left child need right rotation

                 (G)B                      (G)B
                /    \                    /    \                      
            (P)R      (U)B            (X)R      (U)B            
                \                    /                                          
                 (X)R            (P)R      
         
*/
/*   
      if x left child and parent right child need left rotation

                 (G)B                     (G)B                             
                /    \                   /    \                        
            (U)B      (P)R           (U)B      (X)R                   
                     /                             \                 
                 (X)R                               (P)R         
         
*/


   Node* p_child = nullptr;
   Node* p_rightChild = r_node->p_right;
   Node* p_parent = r_node->p_parent;
   Node* p_grandFather = r_node->p_parent->p_parent;
   Node*& r_parent = r_node->p_parent;
   Node*& r_grandFather = r_node->p_parent->p_parent;

   if (status == Status::RIGHT)
   {
      p_child = r_node->p_right;
      r_grandFather->p_right = r_node;
      r_node->p_right = r_parent;
   }
   else
   {
      p_child = r_node->p_left;
      r_grandFather->p_left = r_node;
      r_node->p_left = r_parent;
   }
   
   r_parent->p_parent = r_node;
   r_node->p_parent = p_grandFather;
   
   if (status != Status::RIGHT)
   {
      p_parent->p_right = p_child;
   }
   else
   {
      p_parent->p_left = p_child;
   }
   
   p_child->p_parent = p_parent;
}

void RedBlackTree::removeNode(Node*& r_deleteNode)
{
   bool ifNoChildOrOneChild = 0;
   // no have child
   if (r_deleteNode->p_left == Node::null && r_deleteNode->p_right == Node::null) 
   {
      if(r_deleteNode == m_root) // this case tree have only root
      {
         Node::null->setValue(0);
         Node::null->setColor(Color::BLACK);
         Node::null->p_parent = Node::null;
         Node::null->p_left = Node::null;
         Node::null->p_right = Node::null;
         m_root = Node::null;
      }

      Node*& r_brother = getBrother(r_deleteNode);
      removeNodeNoChild(r_deleteNode);
      if (r_deleteNode->getColor() == Color::BLACK)
      {
         deleteFixColor(r_deleteNode,r_brother);
      }
      ifNoChildOrOneChild = 1;
      // need real delete this node
   }
   // have one child
   else if (r_deleteNode->p_left == Node::null || r_deleteNode->p_right == Node::null)
   {
      if(r_deleteNode == m_root)
      {
         if (r_deleteNode->p_left != Node::null) 
         {
            m_root = r_deleteNode->p_left;
         }
         else
         {
            m_root = r_deleteNode->p_right;
         }  
         m_root->setColor(Color::BLACK);
      }
      else
      {
         changeColorDeleteNodeOneChild(r_deleteNode);
         removeNodeOneChild(r_deleteNode);
      }
      ifNoChildOrOneChild = 1;
      // need real delete this node
   }
   // have two child
   else 
   {
      removeNodeTwoChild(r_deleteNode);
   }

   if (ifNoChildOrOneChild)
   {
      delete r_deleteNode;
   }

}

void RedBlackTree::removeNodeNoChild(Node*& r_deleteNode)
{
   changeDeletedNodePatentChild(r_deleteNode, Node::null);
}

void RedBlackTree::removeNodeOneChild(Node*& r_deleteNode)
{
   Status leftOrRightChildStatus = leftOrRightChild(r_deleteNode);
   Node* p_child = Node::null;
   if (r_deleteNode->p_left != Node::null)
   {
      p_child = r_deleteNode->p_left;
   }
   else
   {
      p_child = r_deleteNode->p_right;
   }
   changeDeletedNodePatentChild(r_deleteNode, p_child);
   p_child->p_parent = r_deleteNode->p_parent;

}

void RedBlackTree::removeNodeTwoChild(Node*& r_deleteNode)
{
   // need find minimal less node and set this node value to deleteNode and delete less node
   Node* p_child = r_deleteNode->p_left;
   while (p_child->p_right != Node::null)
   {
      p_child = p_child->p_right;
   }
   r_deleteNode->setValue(p_child->getValue());
   removeNode(p_child);
}

void RedBlackTree::changeDeletedNodePatentChild(Node*& r_deleteNode, Node*& r_newChild)
{
   Status leftOrRightChildStatus = leftOrRightChild(r_deleteNode);
   if (leftOrRightChildStatus == Status::LEFT)
   {
      r_deleteNode->p_parent->p_left = r_newChild;
   }
   else
   {
      r_deleteNode->p_parent->p_right = r_newChild;
   }
}

void RedBlackTree::changeColorDeleteNodeOneChild(Node*& r_deleteNode)
{
   if (r_deleteNode->p_left != Node::null) 
   {
      r_deleteNode->p_left->setColor(Color::BLACK);
   }
   else
   {
      r_deleteNode->p_right->setColor(Color::BLACK);
   }
}

void RedBlackTree::deleteFixColor(Node*& r_node,Node*& r_brother)
{


   if (r_node != m_root)
   {
      Status brotherChildStatus = leftOrRightChild(r_brother);
      if (r_brother->getColor() == Color::RED)
      {
         deleteFixColorCaseBrotherRed(r_node, r_brother, brotherChildStatus,1);
      }
      else
      {
         if (r_brother->p_left->getColor() == Color::BLACK && r_brother->p_right->getColor() == Color::BLACK)
         {
            deleteFixColorCaseBrother2ChildBlack(r_brother);
         }
         else 
         {
            if (brotherChildStatus == Status::RIGHT) 
            {
               if(r_brother->p_right->getColor() == Color::RED)// RR
               {
                  deleteFixColorCase_LL_RR(r_node, r_brother, brotherChildStatus);
               }
               else if(r_brother->p_left->getColor() == Color::RED)// RL
               {
                  deleteFixColorCase_LR_RL(r_brother,brotherChildStatus);
               }
            }
            else 
            {
               if(r_brother->p_left->getColor() == Color::RED)// LL
               {
                  deleteFixColorCase_LL_RR(r_node, r_brother, brotherChildStatus);
               }
               else if(r_brother->p_right->getColor() == Color::RED)// LR
               {
                  deleteFixColorCase_LR_RL(r_brother,brotherChildStatus);
               }
            }
         }
      }
   }
}

void RedBlackTree::deleteFixColorCaseBrotherRed(Node* p_node, Node*& r_brother,Status brotherChildStatus, bool ifCase1)
{
/*
If brother is red,
Right Case (B is right child of its parent). We left rotate the parent p. Left Case is mirror of right right
DB = double black

                      (P)B                                                
                     /    \                           
                 (X)DB     (B)R                     
                          /    \                                          
                      (LC)B     (RC)B                                                 



                         (B)R     
                        /    \    
                    (P)R     (RC)B
                   /    \         
              (X)DB      (LC)B     



                         (B)R     
                        /    \    
                    (P)B     (RC)B
                   /    \         
              (X)NULL    (LC)R     
*/

   Node* p_parent = r_brother->p_parent;
   Node* p_child = nullptr;
   if (brotherChildStatus == Status::RIGHT) {
      p_child = r_brother->p_left;
      rotateParentAndGrandFather(r_brother->p_right, brotherChildStatus);
      p_parent->p_right = p_child;
   }
   else
   {
      p_child = r_brother->p_right;
      rotateParentAndGrandFather(r_brother->p_left, brotherChildStatus);
      p_parent->p_left = p_child;
   }
   p_child->p_parent = p_parent;
   Node*& r_newBrother = getBrother(p_node);
   if(ifCase1==1)// if this funcion call not recourse
   {
      if (brotherChildStatus == Status::RIGHT) {
         deleteFixColor(p_node, p_node->p_parent->p_right);
      }
      else
      {
         deleteFixColor(p_node, p_node->p_parent->p_left);
      }
   }
}

void RedBlackTree::deleteFixColorCaseBrother2ChildBlack(Node*& r_brother)
{
   //  If brother 2 child is black
   r_brother->setColor(Color::RED);
   if (r_brother->p_parent->getColor() == Color::BLACK)
   {
      deleteFixColor(r_brother->p_parent,getBrother(r_brother->p_parent));
   }
   else
   {
      r_brother->p_parent->setColor(Color::BLACK);
   }
}

void RedBlackTree::deleteFixColorCase_LL_RR(Node* p_node, Node*& r_brother, Status brotherChildStatus)
{
/*
Brother parent right is brother and brother right child is red or mirror in left

                      (P)B                                                
                     /    \                           
                 (X)DB     (B)B                     
                          /    \                                          
                      (LC)R     (RC)R                                                 


                         (B)R     
                        /    \    
                    (P)R     (RC)B
                   /    \         
              (X)NULL    (LC)B     
*/

   deleteFixColorCaseBrotherRed(p_node, r_brother, brotherChildStatus,0);
   if (brotherChildStatus == Status::RIGHT)
   {
      r_brother->p_parent->p_parent->p_right->setColor(Color::BLACK);
   }
   else
   {
      r_brother->p_parent->p_parent->p_left->setColor(Color::BLACK);
   }
}

void RedBlackTree::deleteFixColorCase_LR_RL(Node*& r_brother, Status brotherChildStatus)
{
/*
   Brother parent right is brother and brother left child is red or mirror in left


                      (P)B                                                
                     /    \                           
                 (X)DB     (B)B                     
                          /                                              
                     (LC)R                                                    


                      (P)B                                                
                     /    \                           
                 (X)DB     (LC)B                     
                               \                                              
                                (B)R   


                      (LC)B                                                
                     /     \                           
                 (P)B       (B)B                     
                /                                             
         (X)NULL   
*/


   Node* p_parent = r_brother->p_parent;
   if (brotherChildStatus == Status::RIGHT) 
   {
      swapColors(r_brother, r_brother->p_left);
      rotateNodeAndParent(r_brother->p_left, Status::RIGHT);
      rotateParentAndGrandFather(r_brother->p_right, Status::RIGHT);
   }
   else
   {   
      swapColors(r_brother, r_brother->p_right);
      rotateNodeAndParent(r_brother->p_right, Status::LEFT);
      rotateParentAndGrandFather(r_brother->p_left, Status::LEFT);
   }
   p_parent->p_parent->p_left->setColor(Color::BLACK);
   p_parent->p_parent->p_right->setColor(Color::BLACK);
}

void RedBlackTree::printSpace(double n, Node*& r_removed)const
{
   for (; n > 0; n--)
   {
      std::cout << "\t";
   }
   if (r_removed == nullptr)
   {
      std::cout << " ";
   }
   else {
      if (r_removed->getColor() == Color::RED)
      {
         std::cout << r_removed->getValue() << " R";
      }
      else
      {
         std::cout << r_removed->getValue() << " B";
      }
   }
}

int RedBlackTree::heightOfTree(Node*& r_root)const
{
   if (r_root == Node::null) {
      return 0;
   }
   return 1 + std::max(heightOfTree(r_root->p_left), heightOfTree(r_root->p_right));
}

void RedBlackTree::printBinaryTree(Node* p_root)const
{
   std::queue<Node*> treeLevel, temp;
   treeLevel.push(p_root);
   int counter = 0;
   int height = heightOfTree(p_root) - 1;
   double numberOfElements = pow(2, (height + 1)) - 1;
   while (counter <= height)
   {
      Node* removed = treeLevel.front();
      treeLevel.pop();
      if (temp.empty())
      {
         printSpace(numberOfElements / pow(2, counter + 1), removed);
      }
      else
      {
         printSpace(numberOfElements / pow(2, counter), removed);
      }
      if (removed == Node::null)
      {
         temp.push(Node::null);
         temp.push(Node::null);
      }
      else
      {
         temp.push(removed->p_left);
         temp.push(removed->p_right);
      }
      if (treeLevel.empty())
      {
         std::cout << std::endl << std::endl;
         treeLevel = temp;
         while (!temp.empty())
         {
            temp.pop();
         }
         counter++;
      }
   }
}

bool RedBlackTree::ifBalancedSubTree(Node*& root, int& maxHeight, int& minHeight)const
{
   // Base case
   if (root == Node::null)
   {
      maxHeight = minHeight = 0;
      return true;
   }

   int lmxh, lmnh;
   int rmxh, rmnh;

   if (ifBalancedSubTree(root->p_left, lmxh, lmnh) == false)
   {
      return false;
   }   
   if (ifBalancedSubTree(root->p_right, rmxh, rmnh) == false)
   {
      return false;
   }
   maxHeight = std::max(lmxh, rmxh) + 1;
   minHeight = std::min(lmnh, rmnh) + 1;

   if (maxHeight <= 2 * minHeight)
   {
      return true;
   }

   return false;
}

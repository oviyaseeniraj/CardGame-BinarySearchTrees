// cards.cpp
// Author: Oviya Seeniraj
// Implementation of the classes defined in cards.h

#include "cards.h"
#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST()
{
    this->root = nullptr;
}

// destructor deletes all nodes
IntBST::~IntBST()
{
    clear(this->root);
}

// recursive helper for destructor
void IntBST::clear(Node *n)
{
    // post-order deletion

    if (n == nullptr)
    {
        return;
    }

    clear(n->left);
    clear(n->right);
    delete n;
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value)
{
    return (insert(value, this->root));
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n)
{
    // base case:
    if (n == nullptr)
    {
        n = new Node(value);
        this->root = n;

        return true;
    }

    else if (n->left == nullptr && value < n->info)
    {
        n->left = new Node(value);
        n->left->parent = n;
    }

    else if (n->right == nullptr && value > n->info)
    {
        n->right = new Node(value);
        n->right->parent = n;
    }

    else if (value < n->info)
    {
        insert(value, n->left);
    }

    else if (value > n->info)
    {
        insert(value, n->right);
    }

    return false;
}

// print tree data pre-order
void IntBST::printPreOrder() const
{
    printPreOrder(this->root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const
{
    if (n == nullptr)
    {
        return;
    }
    cout << n->info << " ";
    printPreOrder(n->left);
    printPreOrder(n->right);
}

// print tree data in-order, with helper
void IntBST::printInOrder() const
{
    printInOrder(this->root); // IMPLEMENT HERE
}

void IntBST::printInOrder(Node *n) const
{
    if (n == nullptr)
    {
        return;
    }
    printInOrder(n->left);
    cout << n->info << " ";
    printInOrder(n->right);
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const
{
    printPostOrder(this->root);
}

void IntBST::printPostOrder(Node *n) const
{
    if (n == nullptr)
    {
        return;
    }
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout << n->info << " ";
}

// return sum of values in tree
int IntBST::sum() const
{
    return sum(this->root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const
{
    if (n == nullptr)
    {
        return 0;
    }
    return n->info + sum(n->left) + sum(n->right);
}

// return count of values
int IntBST::count() const
{
    return count(this->root);
}

// recursive helper for count
int IntBST::count(Node *n) const
{
    if (n == nullptr)
    {
        return 0;
    }
    return 1 + count(n->left) + count(n->right);
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node *IntBST::getNodeFor(int value, Node *n) const
{

    if (n == nullptr)
    {
        return NULL;
    }

    if (n->info == value)
    {
        return n;
    }

    if (value < n->info)
    {
        return getNodeFor(value, n->left);
    }
    else
    {
        return getNodeFor(value, n->right);
    }
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const
{
    if (getNodeFor(value, this->root) != NULL)
    {
        return true;
    }
    return false;
}

// returns the Node containing the predecessor of the given value
IntBST::Node *IntBST::getPredecessorNode(int value) const
{
    if (count() == 0 || count() == 1)
    {
        return nullptr;
    }

    Node* n  = getNodeFor(value, this->root);

    if (n == nullptr)
        return 0;

    if (!n->left)
    {
        Node *temp = n;
        while (temp->parent)
        {
            temp = temp->parent;
            if (temp->info < value)
            {
                n = temp;
                break;
            }
        }
        if (n->info == value)
        {
            return 0;
        }
        else
        {
            return n;
        }
    }

    if (n->left)
    {
        n = n->left;
        while (n->right)
        {
            n = n->right;
        }
        return n;
    }
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const
{
    if (getPredecessorNode(value))
    {
        return getPredecessorNode(value)->info;
    }

    return 0;
}

// returns the Node containing the successor of the given value
IntBST::Node *IntBST::getSuccessorNode(int value) const
{
    if (count() == 0 || count() == 1)
    {
        return nullptr;
    }

    Node* n  = getNodeFor(value, this->root);

    if (n == nullptr)
        return 0;

    if (!n->right)
    {
        if (n->parent)
        {

        }
        Node *temp = n;
        while (temp->parent)
        {
            temp = temp->parent;
            if (temp->info > value)
            {
                n = temp;
                break;
            }
        }
        if (n->info == value)
        {
            return 0;
        }
        else
        {
            return n;
        }
    }

    if (n->right)
    {
        n = n->right;
        while (n->left)
        {
            n = n->left;
        }
        return n;
    }
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const
{

    if (getSuccessorNode(value))
    {
        return getSuccessorNode(value)->info;
    }

    return 0;
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value)
{
    Node* n = getNodeFor(value,this->root);


    if (!n) // node does not exist
    {
        return false;
    } 

    bool isLeftChild;
    if (n->parent)
        isLeftChild = (n->info < n->parent->info);
    else
        isLeftChild = false;

    if (count() == 1) // one node case
    {
        this->root = nullptr;
        delete n;
        return true;
    }

    if (!n->left && !n->right) // no children case
    {
        if (isLeftChild) 
        {
            n->parent->left = NULL;
        } 
        else 
        {
            n->parent->right = NULL;
        }
        delete n;
        return true;
    } 

    // one child cases:

    else if (!n->left) 
    {
        if (n == this->root) // root case: does not have parent
        {
            this->root = n->right;
            this->root->parent = nullptr;
            delete n;
            return true;
        } 
        else if (isLeftChild) 
        {
            n->parent->left = n->right;
            n->right->parent = n->parent;
            delete n;
            return true;
        } 
        else 
        {
            n->parent->right = n->right;
            n->right->parent = n->parent;
            delete n;
            return true;
        }
    } 

    else if (!n->right) 
    {
        if (n == this->root) // root case, no parent
        {
            this->root = n->left;
            this->root->parent = nullptr;
            delete n;
            return true;
        } 
        else if (isLeftChild) 
        {
            n->parent->left = n->left;
            n->left->parent = n->parent;
            delete n;
            return true;
        } 
        else 
        {
            n->parent->right = n->left;
            n->left->parent = n->parent;
            delete n;
            return true;
        }
    } 
    else // two node case
    {
        Node* pre = getPredecessorNode(value);
        if (!pre) 
            return false;

        int newVal = pre->info;
        remove(pre->info);
        n->info = newVal;
        return true;
    }
}

bool IntBST::playB(IntBST bst)
{
    if (!this->root)
    {
        return false;
    }

    Node* curr = this->root;
    while (curr->left)
    {
        curr = curr->left;
    }

    while (curr)
    {
        if (bst.contains(curr->info))
        {
            bst.remove(curr->info);
            this->remove(curr->info);
            cout << "Alice picked matching card ";
            this->print(curr->info);
            
            return true;
            break;
        }
        curr = getSuccessorNode(curr->info);
    }

    return false;
}

bool IntBST::playA(IntBST bst)
{
    if (!this->root)
    {
        return false;
    }

    Node* curr = this->root;
    while (curr->right)
    {
        curr = curr->right;
    }

    while (curr)
    {
        if (bst.contains(curr->info))
        {
            bst.remove(curr->info);
            this->remove(curr->info);

            cout << "Bob picked matching card ";
            print(curr->info);

            return true;
            break;
        }
        curr = getPredecessorNode(curr->info);
    }

    return false;
}

void IntBST::printAll()
{
    if (!this->root)
    {
        return;
    }

    Node* curr = this->root;
    print(curr->info);
    while (curr->left)
    {
        curr = curr->left;
        print(curr->info);
    }
}

void IntBST::print(int value)
{
    if (value / 100 == 1)
            cout << "c ";
    else if (value / 100 == 2)
        cout << "d ";
    else if (value / 100 == 3)
        cout << "s ";
    else if (value / 100 == 4)
        cout << "h ";

    if (value % 100 == 1)
        cout << "a" << endl;
    else if (value % 100 == 2)
        cout << "2" << endl;
    else if (value % 100 == 3)
        cout << "3" << endl;
    else if (value % 100 == 4)
        cout << "4" << endl;
    else if (value % 100 == 5)
        cout << "5" << endl;
    else if (value % 100 == 6)
        cout << "6" << endl;
    else if (value % 100 == 7)
        cout << "7" << endl;
    else if (value % 100 == 8)
        cout << "8" << endl;
    else if (value % 100 == 9)
        cout << "9" << endl;
    else if (value % 100 == 10)
        cout << "10" << endl;
    else if (value % 100 == 11)
        cout << "j" << endl;
    else if (value % 100 == 12)
        cout << "q" << endl;
    else if (value % 100 == 13)
        cout << "k" << endl;
}
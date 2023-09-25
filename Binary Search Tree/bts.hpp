/*
Header guards
Added in headers to avoid conflicts due to redeclaration or so called circular declaration error
checks if any of the imports or definitions have already been declared and avoid reimporting them.
*/
#ifndef BST_HPP // if not define then
#define BST_HPP // define this

#include <iostream>

// Node struct
// This struct is used to represent a node in the BST
struct Node
{
    int data;
    Node *left;
    Node *right;
    Node *parent;
};

// Binary Search Tree class, class decalaration
// This class is used to represent a BST
class BinarySearchTree
{
private:
    Node *root;
    int _size;

    // Helper methods
    // Methods used to traverse the BST
    void Inorder(Node *node);
    void Preorder(Node *node);
    void Postorder(Node *node);

    // Create new node
    Node *NewNode(int data);

public:
    // Constructors
    BinarySearchTree();          // default constructor
    BinarySearchTree(int *data); // constructor from an array of integers

    // Methods

    // Size getter
    int Size();

    // Queries
    int Minimum();                                    // returns the minimum value in the tree
    int Maximum();                                    // returns the maximum value in the tree
    Node *Exist(int data);                            // check if a node with the given data exists in the tree
    int Successor(int data);                          // returns the successor of the node with the given data
    int Predecessor(int data);                        // returns the predecessor of the node with the given data
    int TreeSearch(int data, Node *pointer);          // returns the node with the given data
    int IterativeTreeSearch(int data, Node *pointer); // returns the node with the given data in a non recursive way
    void Display(int order);                          // displays the tree in the given order, the order can be 1 for inorder, 2 for preorder and 3 for postorder

    // Insertion
    void Insert(int data);

    // Deletion
    void Delete(int data);
};

// Class implementation
// Constructors
BinarySearchTree::BinarySearchTree()
{
    root = NULL;
    _size = 0;
}

BinarySearchTree::BinarySearchTree(int *data)
{
    root = NULL;
    _size = 0;
    for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++)
    {
        Insert(data[i]);
    }
}

// Helper methods

// Inorder traversal
void BinarySearchTree::Inorder(Node *node)
{
    if (node != NULL)
    {
        Inorder(node->left);
        std::cout << node->data << " ";
        Inorder(node->right);
    }
}

// Preorder traversal
void BinarySearchTree::Preorder(Node *node)
{
    if (node != NULL)
    {
        std::cout << node->data << " ";
        Preorder(node->left);
        Preorder(node->right);
    }
}

// Postorder traversal

void BinarySearchTree::Postorder(Node *node)
{
    if (node != NULL)
    {
        Postorder(node->left);
        Postorder(node->right);
        std::cout << node->data << " ";
    }
}

// Create new node
Node *BinarySearchTree::NewNode(int data)
{
    Node *node = new Node;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}

// Size getter
int BinarySearchTree::Size()
{
    return _size;
}

// Queries
// Minimum
int BinarySearchTree::Minimum()
{
    if (this->root == NULL)
    {
        std::cout << "The tree is empty" << std::endl;
        return -1;
    }
    else
    {
        Node *min = this->root;
        while (min->left != NULL)
        {
            min = min->left;
        }

        return min->data;
    }
}

// Maximum
int BinarySearchTree::Maximum()
{
    if (this->root == NULL)
    {
        std::cout << "The tree is empty" << std::endl;
        return -1;
    }
    else
    {
        Node *max = this->root;
        while (max->right != NULL)
        {
            max = max->right;
        }
        return max->data;
    }
}

// Exist
Node *BinarySearchTree::Exist(int data)
{
    Node *node = this->root;
    while (node != NULL)
    {
        if (node->data == data)
        {
            return node;
        }
        else if (node->data > data)
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }
    }
    return false;
}

// Successor
int BinarySearchTree::Successor(int data)
{
    Node *node = Exist(data);
    if (node == NULL)
    {
        std::cout << "The provided data is not in the tree" << std::endl;
        return -1;
    }
    else
    {
        if (node->right != NULL)
        {
            while (node->left != NULL)
            {
                node = node->left;
            }
            return node->data;
        }
        else
        {
            Node *y = node->parent;
            while (y != NULL && node == y->right)
            {
                node = y;
                y = y->parent;
            }
            return y->data;
        }
    }
}

// Predecessor
int BinarySearchTree::Predecessor(int data)
{
    Node *node = Exist(data);
    if (node == NULL)
    {
        std::cout << "The provided data is not in the tree" << std::endl;
        return -1;
    }
    else
    {
        if (node->left != NULL)
        {
            while (node->right != NULL)
            {
                node = node->right;
            }
            return node->data;
        }
        else
        {
            Node *y = node->parent;
            while (y != NULL && node == y->left)
            {
                node = y;
                y = y->parent;
            }
            return y->data;
        }
    }
}

// TreeSearch
int BinarySearchTree::TreeSearch(int data, Node *pointer)
{
    if (this->root == NULL)
    {
        std::cout << "The tree is empty" << std::endl;
        return -1;
    }
    else
    {
        Node *node = (pointer == NULL) ? this->root : pointer;
        if (node == NULL)
        {
            std::cout << "The element is not in the tree" << std::endl;
            return -1;
        }
        else if (node->data == data)
            return node->data;
        else if (data < node->data)
            return TreeSearch(data, node->left);
        else
            return TreeSearch(data, node->right);
    }
}

// IterativeTreeSearch
int BinarySearchTree::IterativeTreeSearch(int data, Node *pointer)
{
    if (this->root == NULL)
    {
        std::cout << "The tree is empty" << std::endl;
        return -1;
    }
    else
    {
        Node *node = (pointer == NULL) ? this->root : pointer;
        while (node != NULL && node->data != data)
        {
            if (data < node->data)
                node = node->left;
            else
                node = node->right;
        }
        if (node == NULL)
        {
            std::cout << "The element is not in the tree" << std::endl;
            return -1;
        }
        else
            return node->data;
    }

    // Insertion
    void BinarySearchTree::Insert(int data)
    {
        Node *node = NewNode(data);
        Node *y = NULL;
        Node *x = this->root;
        while (x != NULL)
        {
            y = x;
            if (node->data < x->data)
                x = x->left;
            else
                x = x->right;
        }
        node->parent = y;
        if (y == NULL)
            this->root = node;
        else if (node->data < y->data)
            y->left = node;
        else
            y->right = node;
    }
}

#endif
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
    // Transplant
    void Transplant(Node *u, Node *v);

public:
    // Constructors
    BinarySearchTree();                    // default constructor
    BinarySearchTree(int *data, int size); // constructor from an array of integers

    // Methods

    // Size getter
    int Size();

    // Queries
    Node *Minimum(int data);                          // returns the minimum value in the tree
    Node *Maximum();                                  // returns the maximum value in the tree
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

BinarySearchTree::BinarySearchTree(int *data, int size)
{
    root = NULL;
    _size = size;
    for (int i = 0; i < size; i++)
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

// Transplant
void BinarySearchTree::Transplant(Node *u, Node *v)
{
    if (u->parent == NULL)
    {
        this->root = v;
    }
    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }
    if (v != NULL)
    {
        v->parent = u->parent;
    }
}

// Size getter
int BinarySearchTree::Size()
{
    return _size;
}

// Queries
// Minimum
Node *BinarySearchTree::Minimum(int data)
{
    if (this->root == NULL)
    {
        std::cout << "The tree is empty" << std::endl;
        return nullptr;
    }
    else
    {
        Node *min = Exist(data);

        if (min == NULL)
        {
            std::cout << "The provided data is not in the tree" << std::endl;
            return nullptr;
        }
        while (min->left != NULL)
        {
            min = min->left;
        }

        return min;
    }
}

// Maximum
Node *BinarySearchTree::Maximum()
{
    if (this->root == NULL)
    {
        std::cout << "The tree is empty" << std::endl;
        return nullptr;
    }
    else
    {
        Node *max = this->root;
        while (max->right != NULL)
        {
            max = max->right;
        }
        return max;
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
    return nullptr;
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

// Deletion
void BinarySearchTree::Delete(int data)
{
    if (this->root == NULL)
    {
        std::cout << "The tree is empty" << std::endl;
        return;
    }
    Node *node = Exist(data);

    if (node == NULL)
    {
        std::cout << "The element is not in the tree" << std::endl;
        return;
    }

    // Node has no children
    if (node->left == nullptr && node->right == nullptr)
    {
        if (node->parent == nullptr)
            root = nullptr;
        else if (node == node->parent->left)
            node->parent->left = nullptr;
        else
            node->parent->right = nullptr;

        delete node;
    }

    Node *y = NULL;
    if (node->left == NULL)
    {
        Transplant(node, node->right);
        delete node;
    }
    else if (node->right == NULL)
    {
        Transplant(node, node->left);
        delete node;
    }
    else
    {
        y = Minimum(node->right->data);
        if (y != node->right)
        {
            Transplant(y, y->right);
            y->right = node->right;
            y->right->parent = y;
        }
        Transplant(node, y);
        y->left = node->left;
        y->left->parent = y;
        delete node;
    }
}

// Display
void BinarySearchTree::Display(int order = 1)
{
    if (this->root == NULL)
    {
        std::cout << "The tree is empty" << std::endl;
        return;
    }
    else
    {
        switch (order)
        {
        case 1:
            Inorder(this->root);
            std::cout << std::endl;
            break;
        case 2:
            Preorder(this->root);
            std::cout << std::endl;
            break;
        case 3:
            Postorder(this->root);
            std::cout << std::endl;
            break;
        default:
            std::cout << "The provided order is not valid" << std::endl;
            break;
        }
        std::cout << std::endl;
    }
}

#endif
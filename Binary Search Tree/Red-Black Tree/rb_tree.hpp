#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <iostream>

enum COLOR
{
    RED,
    BLACK
};

// Color Node Structure for Red-Black Tree
struct Node
{
    COLOR color;
    int data;
    Node *left, *right, *parent;
};

// Class for Red-Black Tree

class Red_Black_Tree
{
private:
    Node *root;
    int _size;
    Node *NIL;

    // Create Node
    void InitNIL();
    Node *createNode(int);

    // Rotations
    void LeftRotation(Node *);
    void RightRotation(Node *);

    // Fix Insert
    void FixInsert(Node *);

    // Fix Delete
    void FixDelete(Node *);

    // Transplant
    void Transplant(Node *, Node *);

    // inorder
    void Inorder(Node *);

public:
    // Constructor
    Red_Black_Tree();
    Red_Black_Tree(int *, int);

    // Search
    Node *Search(int, Node *);

    // Insertion
    void Insert(int);

    // Delete
    void Delete(int);

    // Destructor
    ~Red_Black_Tree();
};

void Red_Black_Tree::InitNIL()
{
    NIL = new Node;
    NIL->color = BLACK;
    NIL->left = NIL->right = NIL->parent = nullptr;
}

Node *Red_Black_Tree::createNode(int data)
{
    Node *newNode = new Node();
    newNode->data = data;
    newNode->color = RED;
    newNode->left = newNode->right = newNode->parent = NIL;
    return newNode;
}

void Red_Black_Tree::LeftRotation(Node *data)
{
    Node *temp = data->right;
    data->right = temp->left;
    if (temp->left != NIL)
        temp->left->parent = data;
    temp->parent = data->parent;
    if (data->parent == NIL)
        this->root = temp;
    else if (data == data->parent->left)
        data->parent->left = temp;
    else
        data->parent->right = temp;
    temp->left = data;
    data->parent = temp;
}

void Red_Black_Tree::RightRotation(Node *data)
{
    Node *temp = data->left;
    data->left = temp->right;
    if (temp->right != NIL)
        temp->right->parent = data;
    temp->parent = data->parent;
    if (data->parent == NIL)
        this->root = temp;
    else if (data == data->parent->left)
        data->parent->left = temp;
    else
        data->parent->right = temp;
    temp->right = data;
    data->parent = temp;
}

#endif
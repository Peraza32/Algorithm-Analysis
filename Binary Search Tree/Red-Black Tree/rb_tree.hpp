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

    // Minimum
    Node *Minimum(Node *);

    // Insertion
    void Insert(int);

    // Delete
    void Delete(int);

    // Display
    void Display();

    // Destructor
    ~Red_Black_Tree();
};

// Constructor
Red_Black_Tree::Red_Black_Tree()
{
    this->root = NIL;
    this->_size = 0;
    InitNIL();
}

Red_Black_Tree::Red_Black_Tree(int *arr, int size)
{
    this->root = NIL;
    this->_size = 0;
    InitNIL();
    for (int i = 0; i < size; i++)
        Insert(arr[i]);
}

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

// Fixes
//  Fix Insert
void Red_Black_Tree::FixInsert(Node *data)
{
    while (data->parent->color == RED)
    {
        if (data->parent == data->parent->parent->left)
        {
            Node *uncle = data->parent->parent->right;
            if (uncle->color == RED)
            {
                data->parent->color = BLACK;
                uncle->color = BLACK;
                data->parent->parent->color = RED;
                data = data->parent->parent;
            }
            else
            {
                if (data == data->parent->right)
                {
                    data = data->parent;
                    this->LeftRotation(data);
                }
                data->parent->color = BLACK;
                data->parent->parent->color = RED;
                this->RightRotation(data->parent->parent);
            }
        }
        else
        {
            Node *uncle = data->parent->parent->left;
            if (uncle->color == RED)
            {
                data->parent->color = BLACK;
                uncle->color = BLACK;
                data->parent->parent->color = RED;
                data = data->parent->parent;
            }
            else
            {
                if (data == data->parent->left)
                {
                    data = data->parent;
                    this->RightRotation(data);
                }
                data->parent->color = BLACK;
                data->parent->parent->color = RED;
                this->LeftRotation(data->parent->parent);
            }
        }
        this->root->color = BLACK;
    }
}

// Transplant
void Red_Black_Tree::Transplant(Node *u, Node *v)
{
    if (u->parent == NIL)
        this->root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

// Inorder
void Red_Black_Tree::Inorder(Node *data)
{
    if (data != NIL)
    {
        Inorder(data->left);
        std::cout << data->data << " ";
        Inorder(data->right);
    }
}

// Search
Node *Red_Black_Tree::Search(int data, Node *node = nullptr)
{
    if (this->root == NIL)
    {
        std::cout << "Tree is Empty" << std::endl;
        return nullptr;
    }
    if (node == nullptr)
        node = this->root;
    if (node == NIL || node->data == data)
        return node;
    if (data < node->data)
        return Search(data, node->left);
    else
        return Search(data, node->right);
}

// Minimum
Node *Red_Black_Tree::Minimum(Node *node)
{
    while (node->left != NIL)
        node = node->left;
    return node;
}

// Insert
void Red_Black_Tree::Insert(int data)
{
    Node *newNode = createNode(data);
    Node *it = this->root;
    Node *last_visited = NIL;
    while (it != NIL)
    {
        last_visited = it;
        if (newNode->data < it->data)
            it = it->left;
        else
            it = it->right;
    }
    newNode->parent = last_visited;
    if (last_visited == NIL)
        this->root = newNode;
    else if (newNode->data < last_visited->data)
        last_visited->left = newNode;
    else
        last_visited->right = newNode;
    this->FixInsert(newNode);
}

void Red_Black_Tree::Delete(int data)
{
    if (this->root == NIL)
    {
        std::cout << "Tree is Empty" << std::endl;
        return;
    }
    Node *toDelete = Search(data);
    if (toDelete == nullptr)
    {
        std::cout << "Element not found" << std::endl;
        return;
    }
    Node *y = toDelete;
    Node *x;
    COLOR y_original_color = y->color;
    if (toDelete->left == NIL)
    {
        x = toDelete->right;
        this->Transplant(toDelete, toDelete->right);
        delete toDelete;
    }
    else if (toDelete->right == NIL)
    {
        x = toDelete->left;
        this->Transplant(toDelete, toDelete->left);
        delete toDelete;
    }
    else
    {
        y = this->Minimum(toDelete->right);
        y_original_color = y->color;
        x = y->right;
        if (y != toDelete->right)
        {
            this->Transplant(y, y->right);
            y->right = toDelete->right;
            y->right->parent = y;
        }
        else
            x->parent = y;
        this->Transplant(toDelete, y);
        y->left = toDelete->left;
        y->left->parent = y;
        y->color = toDelete->color;
        if (y_original_color == BLACK)
            this->FixDelete(x);
        delete toDelete;
    }
}

// Display
void Red_Black_Tree::Display()
{
    Inorder(this->root);
}

#endif
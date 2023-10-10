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
    void FixInsertRefactor(Node *);

    // Fix Delete
    void FixDelete(Node *);
    void FixDeleteRefactor(Node *);

    // Transplant
    void Transplant(Node *, Node *);

    // Order
    void Inorder(Node *);
    void Postorder(Node *);
    void Preorder(Node *);

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
    void Display(int);

    // Display Tree Shape
    void DisplayTreeShape();

    // Destructor
    ~Red_Black_Tree();
};

void Red_Black_Tree::InitNIL()
{
    NIL = new Node;
    NIL->data = INT_MIN;
    NIL->color = BLACK;
    NIL->left = NIL->right = NIL->parent = nullptr;
}

// Constructor
Red_Black_Tree::Red_Black_Tree()
{
    InitNIL();
    this->root = NIL;
    this->_size = 0;
}

Red_Black_Tree::Red_Black_Tree(int *arr, int size)
{
    InitNIL();
    this->root = NIL;
    this->_size = 0;
    for (int i = 0; i < size; i++)
        Insert(arr[i]);
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
    Node *uncle;
    while (data->parent->color == RED)
    {

        if (data->parent == data->parent->parent->left)
        {
            uncle = data->parent->parent->right;
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

            uncle = data->parent->parent->left;
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
            if (data == root)
            {
                break;
            }
        }
    }
    this->root->color = BLACK;
}

void Red_Black_Tree::FixInsertRefactor(Node *data)
{
    Node *uncle;
    while (data->parent->color == RED)
    {
        bool isLeftChild = (data->parent == data->parent->parent->left);

        uncle = (isLeftChild) ? data->parent->parent->right : data->parent->parent->left;

        if (uncle->color == RED)
        {
            data->parent->color = BLACK;
            uncle->color = BLACK;
            data->parent->parent->color = RED;
            data = data->parent->parent;
        }
        else
        {
            if ((isLeftChild && data == data->parent->right) || (!isLeftChild && data == data->parent->left))
            {
                data = data->parent;
                (isLeftChild) ? this->LeftRotation(data) : this->RightRotation(data);
            }

            data->parent->color = BLACK;
            data->parent->parent->color = RED;
            (isLeftChild) ? this->RightRotation(data->parent->parent) : this->LeftRotation(data->parent->parent);
        }

        if (data == root)
            break;
    }
    this->root->color = BLACK;
}

// Fix Delete

void Red_Black_Tree::FixDelete(Node *data)
{
    Node *sibling;
    while (data != this->root && data->color == BLACK)
    {
        if (data == data->parent->left)
        {
            sibling = data->parent->right;
            if (sibling->color == RED)
            {
                sibling->color = BLACK;
                data->parent->color = RED;
                this->LeftRotation(data->parent);
                sibling = data->parent->right;
            }
            if (sibling->left->color == BLACK && sibling->right->color == BLACK)
            {
                sibling->color = RED;
                data = data->parent;
            }
            else
            {
                if (sibling->right->color == BLACK)
                {
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    this->RightRotation(sibling);
                    sibling = data->parent->right;
                }
                sibling->color = data->parent->color;
                data->parent->color = BLACK;
                sibling->right->color = BLACK;
                this->LeftRotation(data->parent);
                data = this->root;
            }
        }
        else
        {
            sibling = data->parent->left;
            if (sibling->color == RED)
            {
                sibling->color = BLACK;
                data->parent->color = RED;
                this->RightRotation(data->parent);
                sibling = data->parent->left;
            }
            if (sibling->right->color == BLACK && sibling->left->color == BLACK)
            {
                sibling->color = RED;
                data = data->parent;
            }
            else
            {
                if (sibling->left->color == BLACK)
                {
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    this->LeftRotation(sibling);
                    sibling = data->parent->left;
                }
                sibling->color = data->parent->color;
                data->parent->color = BLACK;
                sibling->left->color = BLACK;
                this->RightRotation(data->parent);
                data = this->root;
            }
        }
    }
    data->color = BLACK;
}

// Fix Delete Refactor
void Red_Black_Tree::FixDeleteRefactor(Node *data)
{
    Node *sibling;

    while (data != this->root && data->color == BLACK)
    {
        bool isLeftChild = (data == data->parent->left);
        sibling = (isLeftChild) ? data->parent->right : data->parent->left;

        if (sibling->color == RED)
        {
            sibling->color = BLACK;
            data->parent->color = RED;
            (isLeftChild) ? this->LeftRotation(data->parent) : this->RightRotation(data->parent);
            sibling = (isLeftChild) ? data->parent->right : data->parent->left;
        }

        if (sibling->left->color == BLACK && sibling->right->color == BLACK)
        {
            sibling->color = RED;
            data = data->parent;
        }
        else
        {
            if ((isLeftChild && sibling->right->color == BLACK) || (!isLeftChild && sibling->left->color == BLACK))
            {
                (isLeftChild) ? (sibling->left->color = BLACK) : (sibling->right->color = BLACK);
                sibling->color = RED;
                (isLeftChild) ? this->RightRotation(sibling) : this->LeftRotation(sibling);
                sibling = (isLeftChild) ? data->parent->right : data->parent->left;
            }

            sibling->color = data->parent->color;
            data->parent->color = BLACK;
            (isLeftChild) ? (sibling->right->color = BLACK) : (sibling->left->color = BLACK);
            (isLeftChild) ? this->LeftRotation(data->parent) : this->RightRotation(data->parent);
            data = this->root;
        }
    }

    data->color = BLACK; // Ensure the root is black
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

// Postorder
void Red_Black_Tree::Postorder(Node *data)
{
    if (data != NIL)
    {
        Postorder(data->left);
        Postorder(data->right);
        std::cout << data->data << " ";
    }
}

// Preorder
void Red_Black_Tree::Preorder(Node *data)
{
    if (data != NIL)
    {
        std::cout << data->data << " ";
        Preorder(data->left);
        Preorder(data->right);
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
    try
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
        this->_size++;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
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
void Red_Black_Tree::Display(int order = 1)
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

// Display Tree Shape
void Red_Black_Tree::DisplayTreeShape()
{
    if (this->root == NIL)
    {
        std::cout << "Tree is Empty" << std::endl;
        return;
    }
    std::cout << "Root: " << this->root->data << std::endl;
    std::cout << "NIL: " << NIL->data << std::endl;
    std::cout << "Size: " << this->_size << std::endl;
    std::cout << "Inorder: ";
    Inorder(this->root);
    std::cout << std::endl;
    std::cout << "Preorder: ";
    Preorder(this->root);
    std::cout << std::endl;
    std::cout << "Postorder: ";
    Postorder(this->root);
    std::cout << std::endl;
}

#endif
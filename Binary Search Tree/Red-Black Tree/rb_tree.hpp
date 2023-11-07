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
    void InitNIL(); // Initialize NIL node for the tree
    Node *createNode(int); // Create a new node with given data

    // Rotations
    void LeftRotation(Node *); // Perform left rotation
    void RightRotation(Node *); // Perform right rotation

    // Fix Insert
    void FixInsert(Node *); // Fix the Red-Black Tree property after insertion
    void FixInsertRefactor(Node *); // Refactored version for better readability

    // Fix Delete
    void FixDelete(Node *); // Fix the Red-Black Tree property after deletion
    void FixDeleteRefactor(Node *); // Refactored version for better readability

    // Transplant
    void Transplant(Node *, Node *); // Replace one subtree with another

    // Order
    void Inorder(Node *); // Inorder traversal
    void Postorder(Node *); // Postorder traversal
    void Preorder(Node *); // Preorder traversal

public:
    // Constructor
    Red_Black_Tree(); // Initialize an empty Red-Black Tree
    Red_Black_Tree(int *, int); // Initialize Red-Black Tree with an array of elements

    // Search
    Node *Search(int, Node *); // Search for a node with a given value

    // Minimum
    Node *Minimum(Node *); // Find the node with the minimum value in the tree

    // Insertion
    void Insert(int); // Insert a new node with the given value

    // Delete
    void Delete(int); // Delete the node with the given value

    // Display
    void Display(int); // Display the tree in a specified order

    // Display Tree Shape
    void DisplayTreeShape(); // Display additional information about the tree

    // Destructor
    ~Red_Black_Tree(); // Destructor to free allocated memory
};

// Initialize NIL node
void Red_Black_Tree::InitNIL()
{
    NIL = new Node;
    NIL->data = INT16_MIN;
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

// Constructor with array input
Red_Black_Tree::Red_Black_Tree(int *arr, int size)
{
    InitNIL();
    this->root = NIL;
    this->_size = 0;
    for (int i = 0; i < size; i++)
        Insert(arr[i]);
}

// Create a new node with given data
Node *Red_Black_Tree::createNode(int data)
{
    Node *newNode = new Node();
    newNode->data = data;
    newNode->color = RED;
    newNode->left = newNode->right = newNode->parent = NIL;
    return newNode;
}

// Left rotation operation for balancing the Red-Black Tree
void Red_Black_Tree::LeftRotation(Node *data)
{
    // Save the right child of 'data' in a temporary variable
    Node *temp = data->right;

    // Update pointers to perform the rotation
    data->right = temp->left;
    if (temp->left != NIL)
        temp->left->parent = data;

    temp->parent = data->parent;

    // Update parent pointers
    if (data->parent == NIL)
        this->root = temp;
    else if (data == data->parent->left)
        data->parent->left = temp;
    else
        data->parent->right = temp;

    temp->left = data;
    data->parent = temp;
}

// Right rotation operation for balancing the Red-Black Tree
void Red_Black_Tree::RightRotation(Node *data)
{
    // Save the left child of 'data' in a temporary variable
    Node *temp = data->left;

    // Update pointers to perform the rotation
    data->left = temp->right;
    if (temp->right != NIL)
        temp->right->parent = data;

    temp->parent = data->parent;

    // Update parent pointers
    if (data->parent == NIL)
        this->root = temp;
    else if (data == data->parent->left)
        data->parent->left = temp;
    else
        data->parent->right = temp;

    temp->right = data;
    data->parent = temp;
}

// Fix Insertion to maintain Red-Black Tree properties
void Red_Black_Tree::FixInsert(Node *data)
{
    Node *uncle;
    while (data->parent->color == RED)
    {
        // Determine if the parent is the left or right child of its parent
        bool isLeftChild = (data->parent == data->parent->parent->left);

        // Identify the uncle of the current node
        uncle = (isLeftChild) ? data->parent->parent->right : data->parent->parent->left;

        if (uncle->color == RED)
        {
            // Case 1: Both parent and uncle are red
            data->parent->color = BLACK;
            uncle->color = BLACK;
            data->parent->parent->color = RED;
            data = data->parent->parent;
        }
        else
        {
            // Case 2: Parent is red, but uncle is black
            if ((isLeftChild && data == data->parent->right) || (!isLeftChild && data == data->parent->left))
            {
                data = data->parent;
                (isLeftChild) ? this->LeftRotation(data) : this->RightRotation(data);
            }

            // Case 3: Parent is red, uncle is black, and 'data' is left child of parent (or vice versa)
            data->parent->color = BLACK;
            data->parent->parent->color = RED;
            (isLeftChild) ? this->RightRotation(data->parent->parent) : this->LeftRotation(data->parent->parent);
        }

        if (data == root)
            break;
    }

    this->root->color = BLACK;
}

// Refactored version of FixInsert for better readability
void Red_Black_Tree::FixInsertRefactor(Node *data)
{
    Node *uncle;
    while (data->parent->color == RED)
    {
        // Determine if the parent is the left or right child of its parent
        bool isLeftChild = (data->parent == data->parent->parent->left);

        // Identify the uncle of the current node
        uncle = (isLeftChild) ? data->parent->parent->right : data->parent->parent->left;

        if (uncle->color == RED)
        {
            // Case 1: Both parent and uncle are red
            data->parent->color = BLACK;
            uncle->color = BLACK;
            data->parent->parent->color = RED;
            data = data->parent->parent;
        }
        else
        {
            // Case 2: Parent is red, but uncle is black
            if ((isLeftChild && data == data->parent->right) || (!isLeftChild && data == data->parent->left))
            {
                data = data->parent;
                (isLeftChild) ? this->LeftRotation(data) : this->RightRotation(data);
            }

            // Case 3: Parent is red, uncle is black, and 'data' is left child of parent (or vice versa)
            data->parent->color = BLACK;
            data->parent->parent->color = RED;
            (isLeftChild) ? this->RightRotation(data->parent->parent) : this->LeftRotation(data->parent->parent);
        }

        if (data == root)
            break;
    }

    this->root->color = BLACK;
}

// Fix Deletion to maintain Red-Black Tree properties
void Red_Black_Tree::FixDelete(Node *data)
{
    Node *sibling;
    while (data != this->root && data->color == BLACK)
    {
        // Determine if 'data' is the left or right child of its parent
        bool isLeftChild = (data == data->parent->left);

        // Identify the sibling of the current node
        sibling = (isLeftChild) ? data->parent->right : data->parent->left;

        if (sibling->color == RED)
        {
            // Case 1: Sibling is red
            sibling->color = BLACK;
            data->parent->color = RED;
            this->LeftRotation(data->parent);
            sibling = data->parent->right;
        }

        if (sibling->left->color == BLACK && sibling->right->color == BLACK)
        {
            // Case 2: Sibling is black, and both its children are black
            sibling->color = RED;
            data = data->parent;
        }
        else
        {
            if (sibling->right->color == BLACK)
            {
                // Case 3: Sibling is black, its left child is red, and its right child is black
                sibling->left->color = BLACK;
                sibling->color = RED;
                this->RightRotation(sibling);
                sibling = data->parent->right;
            }

            // Case 4: Sibling is black, and its right child is red
            sibling->color = data->parent->color;
            data->parent->color = BLACK;
            sibling->right->color = BLACK;
            this->LeftRotation(data->parent);
            data = this->root;
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
        // Determine if 'data' is the left or right child of its parent
        bool isLeftChild = (data == data->parent->left);

        // Identify the sibling of the current node
        sibling = (isLeftChild) ? data->parent->right : data->parent->left;

        if (sibling->color == RED)
        {
            // Case 1: Sibling is red
            sibling->color = BLACK;
            data->parent->color = RED;
            (isLeftChild) ? this->LeftRotation(data->parent) : this->RightRotation(data->parent);
            sibling = (isLeftChild) ? data->parent->right : data->parent->left;
        }

        if (sibling->left->color == BLACK && sibling->right->color == BLACK)
        {
            // Case 2: Sibling is black, and both its children are black
            sibling->color = RED;
            data = data->parent;
        }
        else
        {
            if ((isLeftChild && sibling->right->color == BLACK) || (!isLeftChild && sibling->left->color == BLACK))
            {
                // Case 3: Sibling is black, its right (or left) child is black, and its left (or right) child is red
                (isLeftChild) ? (sibling->left->color = BLACK) : (sibling->right->color = BLACK);
                sibling->color = RED;
                (isLeftChild) ? this->RightRotation(sibling) : this->LeftRotation(sibling);
                sibling = (isLeftChild) ? data->parent->right : data->parent->left;
            }

            // Case 4: Sibling is black, and its right (or left) child is red
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

// Inorder traversal of the Red-Black Tree
void Red_Black_Tree::Inorder(Node *data)
{
    if (data != NIL)
    {
        Inorder(data->left);
        std::cout << data->data << " ";
        Inorder(data->right);
    }
}

// Postorder traversal of the Red-Black Tree
void Red_Black_Tree::Postorder(Node *data)
{
    if (data != NIL)
    {
        Postorder(data->left);
        Postorder(data->right);
        std::cout << data->data << " ";
    }
}

// Preorder traversal of the Red-Black Tree
void Red_Black_Tree::Preorder(Node *data)
{
    if (data != NIL)
    {
        std::cout << data->data << " ";
        Preorder(data->left);
        Preorder(data->right);
    }
}

// Search for a node with a given data value in the Red-Black Tree
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

// Find the node with the minimum value in the Red-Black Tree
Node *Red_Black_Tree::Minimum(Node *node)
{
    while (node->left != NIL)
        node = node->left;
    return node;
}

// Insert a new node with the given data value into the Red-Black Tree
void Red_Black_Tree::Insert(int data)
{
    try
    {
        Node *newNode = createNode(data);
        Node *it = this->root;
        Node *last_visited = NIL;

        // Traverse the tree to find the appropriate position for the new node
        while (it != NIL)
        {
            last_visited = it;
            if (newNode->data < it->data)
                it = it->left;
            else
                it = it->right;
        }

        // Update pointers to insert the new node
        newNode->parent = last_visited;
        if (last_visited == NIL)
            this->root = newNode;
        else if (newNode->data < last_visited->data)
            last_visited->left = newNode;
        else
            last_visited->right = newNode;

        // Fix any violations of the Red-Black Tree properties after insertion
        this->FixInsert(newNode);

        this->_size++;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

// Delete a node with the given data value from the Red-Black Tree
void Red_Black_Tree::Delete(int data)
{
    if (this->root == NIL)
    {
        std::cout << "Tree is Empty" << std::endl;
        return;
    }

    // Search for the node to be deleted
    Node *toDelete = Search(data);
    if (toDelete == nullptr)
    {
        std::cout << "Element not found" << std::endl;
        return;
    }

    Node *y = toDelete;
    Node *x;
    COLOR y_original_color = y->color;

    // Case 1: Node to be deleted has no left child
    if (toDelete->left == NIL)
    {
        x = toDelete->right;
        this->Transplant(toDelete, toDelete->right);
        delete toDelete;
    }
    // Case 2: Node to be deleted has no right child
    else if (toDelete->right == NIL)
    {
        x = toDelete->left;
        this->Transplant(toDelete, toDelete->left);
        delete toDelete;
    }
    // Case 3: Node to be deleted has both left and right children
    else
    {
        y = this->Minimum(toDelete->right);
        y_original_color = y->color;
        x = y->right;

        // If the minimum node is not the right child of the node to be deleted
        if (y != toDelete->right)
        {
            this->Transplant(y, y->right);
            y->right = toDelete->right;
            y->right->parent = y;
        }
        else
            x->parent = y;

        // Replace the node to be deleted with its successor
        this->Transplant(toDelete, y);
        y->left = toDelete->left;
        y->left->parent = y;
        y->color = toDelete->color;

        // Fix any violations of the Red-Black Tree properties after deletion
        if (y_original_color == BLACK)
            this->FixDelete(x);

        delete toDelete;
    }
}

// Display
void Red_Black_Tree::Display(int order = 1)
{
    // Check if the tree is empty
    if (this->root == NULL)
    {
        std::cout << "The tree is empty" << std::endl;
        return;
    }
    else
    {
        // Display the tree based on the specified order
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
    // Check if the tree is empty
    if (this->root == NIL)
    {
        std::cout << "Tree is Empty" << std::endl;
        return;
    }

    // Display information about the tree
    std::cout << "Root: " << this->root->data << std::endl;
    std::cout << "NIL: " << NIL->data << std::endl;
    std::cout << "Size: " << this->_size << std::endl;

    // Display the tree in different orders
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

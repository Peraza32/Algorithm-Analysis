/*
Header guards
Added in headers to avoid conflicts due to redeclaration or so called circular declaration error
checks if any of the imports or definitions have already been declared and avoid reimporting them.
*/
#ifndef BST_HPP // if not define then
#define BST_HPP // define this

// Node struct
// This struct is used to represent a node in the BST
struct Node
{
    int data;
    Node *left;
    Node *rigth;
    Node *parent;
};

// Binary Search Tree class
// This class is used to represent a BST

class BinarySearchTree
{
private:
    Node *root;
    int size;

public:
    // Constructors
    BinarySearchTree();          // default constructor
    BinarySearchTree(int *data); // constructor from an array of integers

    // Methods

    // Size getter
    int Size();

    // Queries
    int Minimum();
    int Maximum();
    int Successor(int data);
    int Predecessor(int data);
    int Search(int data);

    // Insertion
    void Insert(int data);

    // Deletion
    void Delete(int data);
};

#endif
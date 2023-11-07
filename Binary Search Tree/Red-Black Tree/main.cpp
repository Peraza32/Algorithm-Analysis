#include <iostream>
#include <ctime>
#include "rb_tree.hpp"

using namespace std;

int main()
{

    srand(time(NULL));

    int array[] = {12, 18, 5, 2, 9, 15, 19, 13, 17};

    Red_Black_Tree *tree = new Red_Black_Tree();
    Red_Black_Tree *tree2 = new Red_Black_Tree(array, 9);

    // Create 55 inserts with random data
    for (int i = 0; i < 55; i++)
    {
        int random = rand() % 100;
        tree->Insert(random);
    }

    /*
    cout << "[";
    cout << inorder
    cout
    cout
    cout << "]";
    */

    // Print the tree

    cout << "-------------------" << endl;
    tree->DisplayTreeShape();
    cout << "-------------------" << endl;
    tree2->DisplayTreeShape();
    cout << "-------------------" << endl;

    // Search for a value
    int value = 0;
    cout << "Enter a value to search for: ";
    cin >> value;
    cout << "-------------------" << endl;

    if (tree2->Search(value))
    {
        cout << "Found " << value << endl;
    }
    else
    {
        cout << "Not found " << value << endl;
    }

    // Delete a value
    cout << "Enter a value to delete: ";
    cin >> value;
    cout << "-------------------" << endl;
    tree->Delete(value);

    tree->DisplayTreeShape();
    cout << "-------------------" << endl;

    return 0;
}
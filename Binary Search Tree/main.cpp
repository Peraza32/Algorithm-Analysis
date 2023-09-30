#include <iostream>
#include <ctime>
#include "bts.hpp"
#include "data.hpp"

using namespace std;

int main()
{
    srand(time(NULL));
    int array[] = {12, 18, 5, 2, 9, 15, 19, 13, 17};

    BinarySearchTree *tree = new BinarySearchTree();
    BinarySearchTree *tree2 = new BinarySearchTree(array, 9);
    // Create 15 inserts with random data
    for (int i = 0; i < 15; i++)
    {
        int random = rand() % 100;
        tree->Insert(random);
    }
    // Print the tree
    tree2->Display();
    // tree->Display(2);
    // tree->Display(3);
    cout << "-------------------" << endl;

    // tree2->Display();
    // tree2->Display(2);
    // tree2->Display(3);

    // cout << "-------------------" << endl;
    // Search for a value
    int value = 0;
    cout << "Enter a value to search for: ";
    cin >> value;
    cout << "-------------------" << endl;


    if (tree2->TreeSearch(value))
    {
        cout << "Found " << value << endl;
    }
    else
    {
        cout << "Not found " << value << endl;
    }

    cout << tree2->Maximum()->data << endl;

    cout << tree2->Minimum()->data << endl;
    // cout << tree->Successor(15);
    // cout << tree->Predecessor(15);

    cout << "-------------------" << endl;
    
    // Delete a value
    cout << "Enter a value to delete: ";
    cin >> value;
    cout << "-------------------" << endl;
    tree2->Delete(value);
    tree2->Display();

    cout << "-------------------" << endl;
    // add a value
    cout << "Enter a value to add: ";
    cin >> value;
    cout << "-------------------" << endl;
    tree2->Insert(value);
    tree2->Display();

    return 0;
}
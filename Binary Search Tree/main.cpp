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
    tree->Display();
    tree->Display(2);
    tree->Display(3);
    cout << "-------------------" << endl;

    tree2->Display();
    tree2->Display(2);
    tree2->Display(3);

    cout << "-------------------" << endl;
    // Search for a value
    int value = 0;
    cout << "Enter a value to search for: ";
    cin >> value;
    cout << "-------------------" << endl;
    if (tree->TreeSearch(value)) 
    {
        cout << "Found " << value << endl;
    }
    else
    {
        cout << "Not found " << value << endl;
    }

    

    return 0;
}
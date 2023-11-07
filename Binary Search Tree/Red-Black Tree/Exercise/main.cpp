#include <iostream>
#include <ctime>
#include "rb_tree.hpp"
#include "utility.hpp"
#include "pcb.hpp"

using namespace std;

int main()
{
    int const size = 35;
    PCB array[size];
    for(int i = 0; i < size; i++)
    {
        array[i] = PCB();
    }

    Red_Black_Tree tree(array, size);
    tree.DisplayTreeShape();

    return 0;
}

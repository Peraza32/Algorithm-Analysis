#ifndef AVL_HPP
#define AVL_HPP

/*
Description of AVL tree:
    AVL tree is a self-balancing Binary Search Tree (BST) where the difference between heights of left and right subtrees cannot be more than one for all nodes.
    An Example Tree that is an AVL Tree
            30
           /  \
         20   40
        /  \     \
       10  25    50
    The above tree is AVL because differences between heights of left and right subtrees for every node is less than or equal to 1.
    An Example Tree that is NOT an AVL Tree
            30
           /  \
         20   40
        /  \     \
       10  25    50
      /
     9
    The above tree is not AVL because differences between heights of left and right subtrees for 30 and 20 is greater than 1.
    AVL trees are often compared with Red-Black Trees because both support the same set of operations and take O(Logn) time for the main operations.
    For lookup, insertion and deletion, AVL trees are better than Red-Black Trees as AVL trees are more balanced compared to Red-Black Trees.
    AVL trees store balance factor at each node. Balance factor of a node in an AVL tree is the difference between the height of the left subtree and that of the right subtree of that node (i.e. Balance Factor = (Height of Left Subtree - Height of Right Subtree) or (Height of Right Subtree - Height of Left Subtree)).
    The self-balancing property of an AVL tree is maintained by the balance factor. The value of balance factor should always be -1, 0 or 1. If at any time, the absolute value of a node’s balance factor is greater than 1 then the subtree rooted at that node is unbalanced, and we need to perform some operations to balance the tree which are called rotations.
    There are four possible AVL rotations: Left Rotation, Right Rotation, Left-Right Rotation, and Right-Left Rotation.
    Left Rotation:
        Let A be the unbalanced node, B be the right child of A, and C be the right child of B. Then, left rotation is performed as follows:
        1. Set A’s right child to B’s left child.
        2. If B has a left child, set B’s left child’s parent to A.
        3. Set B’s left child to A.

*/

#include <iostream>



#endif
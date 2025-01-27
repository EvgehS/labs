#include <iostream>
#include <string>
#include "binary_tree.hpp"


int main() {
    MyBinaryTree<int, int> tree;
    
    tree.push(1, 7);
    tree.push(2, 3);
    tree.push(-5, 7);
    tree.push(56, 2);
    
    std::cout << "Элементы дерева: " << tree << std::endl;
    
    return 0;
}
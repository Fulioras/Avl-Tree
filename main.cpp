#include <iostream>
#include <limits.h>


struct node {
    int data;
    node *left;
    node *right;
};


int main() {
    std::cout << "Hello, World!" << std::endl;


    return 0;
}

void insert(node *root, int data) {
    if (root == NULL) {
        root = new node();
        root->data = data;
        root->left = NULL;
        root->right = NULL;
        return;
    }

    
}



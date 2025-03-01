// Written by Augustinas Bickaitis in 2025
// Code is based on a geeks for geeks article
// https://www.geeksforgeeks.org/cpp-program-to-implement-avl-tree/

#include <iostream>
#include <algorithm>

struct avl_node {
    int data;
    int height = 1;
    avl_node *left = NULL;
    avl_node *right = NULL;
};


class Avl_Tree {
private:

    avl_node *root;

    avl_node* insert_Priv(avl_node* node, int data) {

        /// TRAVERSE UNTIL CORRECT NODE
        if (node == NULL) {
            node = new avl_node();
            node->data = data;
            return node;
        }
        if (data < node->data) {
            node = insert_Priv(node->left, data);
        }
        else if (data > node->data) {
            node = insert_Priv(node->right, data);
        }
        else
            return node;

        /// From this point on we are updating the avl tree starting with the new leaf up until the root
        /// UPDATE HEIGHTS
        node->height = 1 + std::max(height(node->left), height(node->right));

        /// CHECK BALANCE/ROTATE
        int balance = balance_Factor(node);

        if(balance > 1 && height(node->left) >= 0) {}
        //need functions for all 4 rotations

        return node;

    }

    int height(avl_node* node) {
        if (node == NULL)
            return 0;
        return node->height;
    }

    int balance_Factor(avl_node* node) {
        return height(node->left) - height(node->right);
    }

    /// ROTATION FUNCTIONS
    /// a - left node, b - right node;
    avl_node* right_Rotate(avl_node* node) {
        avl_node* a = node->left;
        avl_node* ab = a->right;

        a->right = node;
        node->left = ab;

        /// need to update heights

        return a;
    }

    avl_node* left_Rotate(avl_node* node) {
        avl_node* b = node->right;
        avl_node* ba = b->left;

        b->left = node;
        node->right = ba;

        /// need to update heights


        return b;
    }

    bool search_Priv(avl_node* node, int data) {
        if(data == node->data) {
            return true;
        }
        else if (data < node->data && node->left != NULL) {
            return search_Priv(node->left, data);
        }
        else if (data > node->data && node->right != NULL) {
            return search_Priv(node->right, data);
        }
        else {
            return false;
        }
    }

    void remove_Priv(avl_node* node, int data) {
        /// Code goes here
    }

    void display_Priv(avl_node* node) {
        if (node != NULL) {
            display_Priv(node->left);
            std::cout << node->data << " ";
            display_Priv(node->right);
        }
        else {
            std::cout << "NLL" << " ";
        }
    }

public:
    Avl_Tree() {
        root = NULL;
    }

    void insert( int data) {
        root = insert_Priv(root, data);
    }

    bool search(int data) {
        return search_Priv(root, data);
    }

    void remove(int data){
        remove_Priv(root, data);
    }

    void display() {
        display_Priv(root);
    }
};


int main() {
    Avl_Tree tree;
    tree.insert(4);
    std::cout << "Hello, World!" << std::endl;


    return 0;
}





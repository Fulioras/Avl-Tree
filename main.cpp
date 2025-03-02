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
            node->left = insert_Priv(node->left, data);
        }
        else if (data > node->data) {
            node->right = insert_Priv(node->right, data);
        }
        else
            return node;

        /// From this point on we are updating the avl tree starting with the new leaf up until the root
        /// UPDATE HEIGHTS
        node->height = 1 + std::max(height(node->left), height(node->right));

        /// CHECK BALANCE/ROTATE
        int balance = balance_Factor(node);


        /// ROTATIONS
        if(balance > 1 && balance_Factor(node->left) >= 0) {
            //LEFT
            return left_Rotate(node);
        }
        if(balance > 1 && balance_Factor(node->left) < 0) {
            //RIGHT LEFT
            node->left = right_Rotate(node->left);
            return left_Rotate(node);
        }
        if(balance < -1 && balance_Factor(node->right) < 0) {
            //RIGHT
            return right_Rotate(node);
        }
        if(balance < -1 && balance_Factor(node->right) >= 0) {
            //LEFT RIGHT
            node->right = left_Rotate(node->right);
            return right_Rotate(node);
        }
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

    /// Balances when tree is left-heavy
    avl_node* left_Rotate(avl_node* node) {
        avl_node* a = node->left; //needs height check 2)
        avl_node* ab = a->right;

        a->right = node; //needs height check 1)
        a->right->left = ab;


        ///update heights
        (a->right)->height = std::max(height((a->right)->left), height((a->right)->right)) + 1; //1)
        a->height = std::max(height(a->left), height(a->right)) + 1; //2)

        return a;
    }

    /// Balances when tree is right-heavy
    avl_node* right_Rotate(avl_node* node) {
        avl_node* b = node->right; //needs height check 2)
        avl_node* ba = b->left;

        b->left = node; //needs height check 1)
        b->left->right = ba;

        ///update heights
        (b->left)->height = std::max(height((b->left)->left), height((b->left)->right)) + 1; //1)
        b->height = std::max(height(b->left), height(b->right)) + 1; //2)

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

    avl_node* remove_Priv(avl_node* node, int data) {
        if(node == NULL) {
            return node;
        }

        if(data < node->data) {
            node->left = remove_Priv(node->left, data);
        }
        else if (data > node->data) {
            node->right = remove_Priv(node->right, data);
        }
        else {
            ///Two Cases:
            ///one or zero child nodes
            if(node->left == NULL || node->right == NULL) {
                avl_node* temp = NULL;

                if(node->left == NULL)
                    temp = node->right;
                else
                    temp = node->left;

                if(temp == NULL) {
                    temp = node;
                    node = NULL;
                }
                else {
                    *temp = *node;
                }

                delete temp;
            }
            else {///Two child nodes
                avl_node* temp = find_Smallest_Node(node->right);
                node->data = temp->data;
                node->right = remove_Priv(node->right, node->data);
            }
        }
        if(node == NULL) {
            return node;
        }

        /// BALANCING
        /// From this point on we are updating the avl tree starting with the new leaf up until the root
        /// UPDATE HEIGHTS
        node->height = 1 + std::max(height(node->left), height(node->right));

        /// CHECK BALANCE/ROTATE
        int balance = balance_Factor(node);


        /// ROTATIONS
        if(balance > 1 && balance_Factor(node->left) >= 0) {
            //LEFT
            return left_Rotate(node);
        }
        if(balance > 1 && balance_Factor(node->left) < 0) {
            //RIGHT LEFT
            node->left = right_Rotate(node->left);
            return left_Rotate(node);
        }
        if(balance < -1 && balance_Factor(node->right) < 0) {
            //RIGHT
            return right_Rotate(node);
        }
        if(balance < -1 && balance_Factor(node->right) >= 0) {
            //LEFT RIGHT
            node->right = left_Rotate(node->right);
            return right_Rotate(node);
        }
        return node;

    }

    avl_node* find_Smallest_Node(avl_node* node) {
        if(node->left == NULL) {
            return node;
        }
        else {
            node = find_Smallest_Node(node->left);
        }
        return node;
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
        root = remove_Priv(root, data);
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





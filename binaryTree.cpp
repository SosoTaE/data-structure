#include <iostream>
typedef int Object;

using namespace std;

struct Node {
    Object value;
    Node* left;
    Node* right;
    Node(): value(0), left(0), right(0) {};
    Node(Object value, Node* left = 0, Node* right = 0) : value(value), left(left), right(right) {}

};

class BinaryTree {
    private:
        Node* root;
        size_t length;

        void repeat(const char* chars, unsigned int quantity) {
            while (quantity > 0) {
                cout<<chars;
                quantity--;
            }
        } 

        void addRecursively(Node* node) {
        if (node != nullptr) {
            add(node->value);
            addRecursively(node->right);
            addRecursively(node->left);
        }
}

    public:
        BinaryTree(): root(0), length(0) {}

        void add(Object value) {
            Node* node = new Node(value);
            if (root == 0) {
                root = node;
            } 
            else {
                Node* copyOfRoot = root;
                while (copyOfRoot != 0) {
                    if (copyOfRoot -> value < value) {
                        
                        if (copyOfRoot -> right == 0) {
                            copyOfRoot -> right = node;
                            break;
                        }

                        copyOfRoot = copyOfRoot -> right;                        
                    }
                    else {

                        if (copyOfRoot -> left == 0) {
                            copyOfRoot -> left = node;
                            break;
                        }

                        copyOfRoot = copyOfRoot -> left;       
                    }
                }
            }  
        }

        void print(Node* root, unsigned int level, const char* prefix) {
            if (root == 0) {
                repeat(" ", 4 * level);
                cout<<prefix<<"Undifined"<<endl;
                return;
            }
            else {
                repeat(" ", 4 * level);
                cout<<prefix<<root -> value<<endl;
            }

            if (root->left != 0) {
                print(root->left, level + 1, "L----");
            }

            if (root->right != 0) {
                print(root->right, level + 1, "R----");
            }


        }

        void remove(Object value) {
            Node* right = 0;
            Node* left = 0;
            if (root == 0) {
                return; 
            } 
            else if (root -> value == value) {
                right = root -> right;
                left = root -> left;
                root -> left = 0;
                root -> right = 0;
                delete root;
                root = 0;
            }
            else {
                Node* copyOfRoot = root;
                while (copyOfRoot != 0) {
                    if (copyOfRoot -> value < value) {
                        
                        if (copyOfRoot -> right == 0) {
                            break;
                        }
                        else if (copyOfRoot -> right -> value == value) {
                            Node* copied = copyOfRoot -> right;
                            copyOfRoot -> right = 0;
                            right = copied -> right;
                            left = copied -> left;
                            copied -> right = 0;
                            copied -> left = 0;
                            delete copied;
                            break;
                        }

                        copyOfRoot = copyOfRoot -> right;            

                                    
                    }
                    else {
                        if (copyOfRoot -> left == 0) {
                            break;
                        }
                        else if (copyOfRoot -> left -> value == value) {
                            Node* copied = copyOfRoot -> left;
                            copyOfRoot -> left = 0;
                            right = copied -> right;
                            left = copied -> left;
                            copied -> right = 0;
                            copied -> left = 0;
                            delete copied;
                            break;
                        }

                        copyOfRoot = copyOfRoot -> left;       
                    }
                }
            } 
            addRecursively(right);
            addRecursively(left);
                
        }

        void displayTree() {
            print(root, 0, "Root:");
        }

        void displayLeftBranch() {
            print(root -> left, 0, "Left:");
        }

        void displayRightBranch() {
            print(root -> right, 0, "Right:");
        }
};

int main() {
    BinaryTree tree = BinaryTree();

    for (int i = 0;i < 5;i++) {
        tree.add(i);
    }

    for (int i = 0;i < 5;i++) {
        tree.add(i);
    }

    for (int i = 1;i < 5;i++) {
        tree.add(i * -1);
    }


    tree.displayTree();
    tree.remove(0);
    tree.displayTree();
    return 0;
}
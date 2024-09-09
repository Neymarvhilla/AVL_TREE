#include <iostream>


class AVL_TreeNode {
private:
    int data;
    AVL_TreeNode *left;
    AVL_TreeNode *right;

public:
    AVL_TreeNode() : data {0}, left {nullptr}, right {nullptr} {}
    AVL_TreeNode(int data) : data {data}, left {nullptr}, right {nullptr} {}
    int get_data() const {return this->data;}
    void set_data(int new_data) {this->data = new_data;}
    AVL_TreeNode *get_leftSubtree() const {return this->left;}
    void set_leftSubtree(AVL_TreeNode *new_left) {this->left = new_left;}
    AVL_TreeNode *get_rightSubtree() const {return this->right;}
    void set_rightSubtree(AVL_TreeNode *new_right) {this->right = new_right;}
    ~AVL_TreeNode(){};
};

class AVL_Tree {
private:
    void levelOrderDump(AVL_TreeNode *node, int level) {
        if (node == nullptr) {
            return;
        }
        if (level == 1) {
            std::cout << node->get_data() << std::endl;
        }
        levelOrderDump(node->get_leftSubtree(), level - 1);
        levelOrderDump(node->get_rightSubtree(), level - 1);
    }
    AVL_TreeNode *root;
    int _size() {
        return size(root);
    };
    void insert(int data) {
       root = insert(root, data);
    }
    AVL_TreeNode *LLRotation(AVL_TreeNode *nroot) {
        AVL_TreeNode *rl = nroot->get_leftSubtree();
        AVL_TreeNode *rlr = rl->get_rightSubtree();
        rl->set_rightSubtree(nroot);
        nroot->set_leftSubtree(rlr);
        // if passed node was the root, then update root to the new root
        if (this->root == nroot) {
            this->root = rl;
        }
        return rl;
    }

    AVL_TreeNode *LRRotation(AVL_TreeNode *nroot) {
        AVL_TreeNode *rl = nroot->get_leftSubtree();
        AVL_TreeNode *rlr = rl->get_rightSubtree();

        rl->set_rightSubtree(rlr->get_leftSubtree());
        rlr->set_leftSubtree(rl);
        nroot->set_leftSubtree(rlr->get_rightSubtree());
        rlr->set_rightSubtree(nroot);

        if (this->root == nroot) {
            this->root = rlr;
        }
        return rlr;
    }

    AVL_TreeNode *RRRotation(AVL_TreeNode *nroot) {
        AVL_TreeNode *lr = nroot->get_rightSubtree();
        AVL_TreeNode *lrl = lr->get_leftSubtree();
        lr->set_leftSubtree(nroot);
        nroot->set_rightSubtree(lrl);

        if (this->root == nroot) {
            this->root = lr;
        }
        return lr;
    }

    AVL_TreeNode *RLRotation(AVL_TreeNode *nroot) {
        AVL_TreeNode *rr = nroot->get_leftSubtree();
        AVL_TreeNode *rrl = rr->get_leftSubtree();

        rr->set_leftSubtree(rrl->get_rightSubtree());
        nroot->set_rightSubtree(rrl->get_leftSubtree());
        rrl->set_rightSubtree(rr);
        rrl->set_leftSubtree(nroot);

        if (this->root == nroot) {
            this->root = rrl;
        }
        return rrl;
    }

public:
    void levelOrderDump() {
        for (int i {1}; i <= height(root); i++) {
            levelOrderDump(root, i);
        }
    }
    void inorder_traversal(AVL_TreeNode *Node) {
        if (Node == nullptr) {
            return;
        }
        inorder_traversal(Node->get_leftSubtree());
        std::cout << Node->get_data() << " ";
        inorder_traversal(Node->get_rightSubtree());
    }

    void preorder_traversal(AVL_TreeNode *Node) {
        if (Node == nullptr) {
            return;
        }
        std::cout << Node->get_data() << " ";
        preorder_traversal(Node->get_leftSubtree());
        preorder_traversal(Node->get_rightSubtree());
    }

    void postorder_traversal(AVL_TreeNode *Node) {
        if (Node == nullptr) {
            return;
        }
        postorder_traversal(Node->get_rightSubtree());
        std::cout << Node->get_data() << " ";
        postorder_traversal(Node->get_rightSubtree());
    }
    AVL_TreeNode *insert(AVL_TreeNode *Node, int data) {
        if (Node == nullptr) {
            AVL_TreeNode *new_node = new AVL_TreeNode(data);
            return new_node;
        }
        if (data > Node->get_data()) {
            // Do rightSubtree recursion
            Node->set_rightSubtree(insert(Node->get_rightSubtree(), data));
            //return Node;
        }
        else {
            insert(Node->get_leftSubtree(), data);
        }

        // if there is a left-left imbalance
        if (balanceFactor(Node) == 2 && balanceFactor(Node->get_leftSubtree()) == 1) {
            return LLRotation(Node);
        }
        // if there is a left right imbalance
        else if (balanceFactor(Node) == 2 && balanceFactor(Node->get_leftSubtree()) == -1) {
             return LRRotation(Node);
        }

         // if there is a right-right rotation

        else if (balanceFactor(Node) == -2 && balanceFactor(Node->get_rightSubtree()) == -1) {
            return RRRotation(Node);
        }

        else if(balanceFactor(Node) == -2 && balanceFactor(Node->get_rightSubtree()) == 1) {
            return RLRotation(Node);
        }

         return Node;
    }

    bool find(int data, AVL_TreeNode *Node) {
        if (Node == nullptr) {
            return false;
        }
        if (Node->get_data() == data) {
            return true;
        }
        if (Node->get_data() < data) {
            return find(data, Node->get_rightSubtree());
        }
        else {
            return find(data, Node->get_leftSubtree());
        }
    }

    int size(AVL_TreeNode *Node) {
        if (Node == nullptr) {
            return 0;
        }
        return 1 + size(Node->get_leftSubtree()) + size(Node->get_rightSubtree());
    }

    int height(AVL_TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }
        int left = height(root->get_leftSubtree());
        int right = height(root->get_rightSubtree());
        if (left > right) {
            return left + 1;
        }
        return right + 1;
    }
    int balanceFactor(AVL_TreeNode *root) {
        int h_left{};
        int h_right{};
        // check if the root is not a nullptr
        if (root) {

            if (root->get_leftSubtree()) {
                h_left = height(root->get_leftSubtree());
            }
            else {
                h_left = 0;
            }
            if(root->get_rightSubtree()) {
                h_right = height(root->get_rightSubtree());
            }
            else {
                h_right = 0;
            }
        }
        return h_left - h_right;
    };




};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

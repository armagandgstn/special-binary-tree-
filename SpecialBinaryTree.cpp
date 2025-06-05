#include "SpecialBinaryTree.h"
#include "BinaryTreeNode.h"
#include <iostream>
#include <queue>
#include <stack>
#include <climits>

using namespace std;

SpecialBinaryTree::SpecialBinaryTree() : root(nullptr) {}

SpecialBinaryTree::~SpecialBinaryTree() {
    // Call a helper function to recursively delete nodes
    if (root != nullptr) {
        delete_tree(root);
    }
}
void SpecialBinaryTree::delete_tree(BinaryTreeNode* node) {
    if (node == nullptr) {
        return;
    }
    delete_tree(node->get_left());
    delete_tree(node->get_right());
    delete node;
}

bool SpecialBinaryTree::add_node(int new_value, int parent_value, bool is_left_child, bool is_right_child, bool is_root) {
    if (is_root) {
        if (root != nullptr) {
            return false; // Root already exists
        } else {
            root = new BinaryTreeNode();
            root->set_value(new_value);
            return true;
        }
    }

    if (root == nullptr) {
        return false; // Cannot add node if tree is empty
    }

    queue<BinaryTreeNode*> q;
    q.push(root);
    BinaryTreeNode* parent = nullptr;
    while (!q.empty()) {
        BinaryTreeNode* current = q.front();
        q.pop();
        if (current->get_value() == parent_value) {
            parent = current;
            break;
        }
        if (current->get_left() != nullptr) {
            q.push(current->get_left());
        }
        if (current->get_right() != nullptr) {
            q.push(current->get_right());
        }
    }

    if (parent == nullptr || ((parent->get_left() != nullptr && is_left_child) || (parent->get_right() != nullptr && is_right_child))) {
        return false;
    }

    BinaryTreeNode* new_node = new BinaryTreeNode();
    new_node->set_value(new_value);
    if (is_left_child) {
        parent->set_left(new_node);
    } else {
        parent->set_right(new_node);
    }
    return true;
}


bool SpecialBinaryTree::update_value(int previous_value, int new_value) {
    // Helper function to perform a BFS traversal and update the value
    queue<BinaryTreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        BinaryTreeNode* current = q.front();
        q.pop();
        if (current->get_value() == previous_value) {
            current->set_value(new_value);
            return true;
        }
        if (current->get_left() != nullptr) {
            q.push(current->get_left());
        }
        if (current->get_right() != nullptr) {
            q.push(current->get_right());
        }
    }
    // If previous value not found
    return false;
}


bool SpecialBinaryTree::remove_node(int value) {
    queue<BinaryTreeNode*> q;
    q.push(root);
    BinaryTreeNode* to_remove_parent = nullptr;
    BinaryTreeNode* to_remove = nullptr;
    while (!q.empty()) {
        BinaryTreeNode* current = q.front();
        q.pop();
        if (current->get_left() != nullptr && current->get_left()->get_value() == value) {
            to_remove_parent = current;
            to_remove = current->get_left();
            break;
        }
        if (current->get_right() != nullptr && current->get_right()->get_value() == value) {
            to_remove_parent = current;
            to_remove = current->get_right();
            break;
        }
        if (current->get_left() != nullptr) {
            q.push(current->get_left());
        }
        if (current->get_right() != nullptr) {
            q.push(current->get_right());
        }
    }

    if (to_remove == nullptr) {
        return false;
    }

    if (to_remove->get_left() == nullptr && to_remove->get_right() == nullptr) {
        if (to_remove_parent == nullptr) {
            delete root;
            root = nullptr;
            return true;
        }
        if (to_remove_parent->get_left() == to_remove) {
            to_remove_parent->set_left(nullptr);
        } else {
            to_remove_parent->set_right(nullptr);
        }
        delete to_remove;
        return true;
    }

    if (to_remove->get_left() == nullptr || to_remove->get_right() == nullptr) {
        BinaryTreeNode* child = (to_remove->get_left() != nullptr) ? to_remove->get_left() : to_remove->get_right();
        if (to_remove_parent == nullptr) {
            root = child;
            delete to_remove;
            return true;
        }
        if (to_remove_parent->get_left() == to_remove) {
            to_remove_parent->set_left(child);
        } else {
            to_remove_parent->set_right(child);
        }
        delete to_remove;
        return true;
    }

    BinaryTreeNode* successor = to_remove->get_right();
    BinaryTreeNode* successor_parent = to_remove;
    while (successor->get_left() != nullptr) {
        successor_parent = successor;
        successor = successor->get_left();
    }
    to_remove->set_value(successor->get_value());
    if (successor_parent->get_left() == successor) {
        successor_parent->set_left(successor->get_right());
    } else {
        successor_parent->set_right(successor->get_right());
    }
    delete successor;
    return true;
}


int SpecialBinaryTree::is_leaf_node(int value) {
    // Helper function to check if a node is a leaf
    queue<BinaryTreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        BinaryTreeNode* current = q.front();
        q.pop();
        if (current->get_value() == value) {
            if (current->get_left() == nullptr && current->get_right() == nullptr) {
                return 1; // Leaf node
            } else {
                return 0; // Non-leaf node
            }
        }
        if (current->get_left() != nullptr) {
            q.push(current->get_left());
        }
        if (current->get_right() != nullptr) {
            q.push(current->get_right());
        }
    }
    // If value not found
    return -1;
}

bool SpecialBinaryTree::does_exist_in_subtree(int subtree_root_value, int value_to_search) {
    // Helper function to check if a value exists in a subtree rooted at a given node
    queue<BinaryTreeNode*> q;
    q.push(root);
    BinaryTreeNode* subtree_root = nullptr;
    while (!q.empty()) {
        BinaryTreeNode* current = q.front();
        q.pop();
        if (current->get_value() == subtree_root_value) {
            subtree_root = current;
            break;
        }
        if (current->get_left() != nullptr) {
            q.push(current->get_left());
        }
        if (current->get_right() != nullptr) {
            q.push(current->get_right());
        }
    }
    if (subtree_root == nullptr) {
        return false; // Subtree root not found
    }
    // Perform BFS traversal in the subtree to find the value
    q.push(subtree_root);
    while (!q.empty()) {
        BinaryTreeNode* current = q.front();
        q.pop();
        if (current->get_value() == value_to_search) {
            return true;
        }
        if (current->get_left() != nullptr) {
            q.push(current->get_left());
        }
        if (current->get_right() != nullptr) {
            q.push(current->get_right());
        }
    }
    // Value not found in subtree
    return false;
}


int SpecialBinaryTree::find_depth(int value) {
    // Helper function to find the depth of a node
    queue<pair<BinaryTreeNode*, int>> q;
    q.push({root, 0});
    while (!q.empty()) {
        pair<BinaryTreeNode*, int> current = q.front();
        q.pop();
        if (current.first->get_value() == value) {
            return current.second;
        }
        if (current.first->get_left() != nullptr) {
            q.push({current.first->get_left(), current.second + 1});
        }
        if (current.first->get_right() != nullptr) {
            q.push({current.first->get_right(), current.second + 1});
        }
    }
    // If value not found
    return -1;
}

int SpecialBinaryTree::find_height(int value) {
    // Helper function to find the height of a node
    queue<BinaryTreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        BinaryTreeNode* current = q.front();
        q.pop();
        if (current->get_value() == value) {
            // Calculate height using DFS
            stack<pair<BinaryTreeNode*, int>> stk;
            stk.push({current, 0});
            int height = 0;
            while (!stk.empty()) {
                pair<BinaryTreeNode*, int> node = stk.top();
                stk.pop();
                height = max(height, node.second);
                if (node.first->get_left() != nullptr) {
                    stk.push({node.first->get_left(), node.second + 1});
                }
                if (node.first->get_right() != nullptr) {
                    stk.push({node.first->get_right(), node.second + 1});
                }
            }
            return height;
        }
        if (current->get_left() != nullptr) {
            q.push(current->get_left());
        }
        if (current->get_right() != nullptr) {
            q.push(current->get_right());
        }
    }
    // If value not found
    return -1;
}

void SpecialBinaryTree::preorder_traversal() {
    // Helper function to perform preorder traversal
    if (root == nullptr) {
        cout << "There is no node in the tree. " << endl;
        return;
    }
    stack<BinaryTreeNode*> stk;
    stk.push(root);
    while (!stk.empty()) {
        BinaryTreeNode* current = stk.top();
        stk.pop();
        cout << current->get_value() << " ";
        if (current->get_right() != nullptr) {
            stk.push(current->get_right());
        }
        if (current->get_left() != nullptr) {
            stk.push(current->get_left());
        }
    }
    cout << endl;
}

void SpecialBinaryTree::postorder_traversal() {
    // Helper function to perform postorder traversal
    if (root == nullptr) {
        cout << "There is no node in the tree. " << endl;
        return;
    }
    stack<pair<BinaryTreeNode*, bool>> stk;
    stk.push({root, false});
    while (!stk.empty()) {
        pair<BinaryTreeNode*, bool> current = stk.top();
        stk.pop();
        if (current.second) {
            cout << current.first->get_value() << " ";
        } else {
            stk.push({current.first, true});
            if (current.first->get_right() != nullptr) {
                stk.push({current.first->get_right(), false});
            }
            if (current.first->get_left() != nullptr) {
                stk.push({current.first->get_left(), false});
            }
        }
    }
    cout << endl;
}

void SpecialBinaryTree::inorder_traversal() {
    // Helper function to perform inorder traversal
    if (root == nullptr) {
        cout << "There is no node in the tree. " << endl;
        return;
    }
    stack<pair<BinaryTreeNode*, bool>> stk;
    BinaryTreeNode* current = root;
    while (current != nullptr || !stk.empty()) {
        while (current != nullptr) {
            stk.push({current, false});
            current = current->get_left();
        }
        pair<BinaryTreeNode*, bool> node = stk.top();
        stk.pop();
        cout << node.first->get_value() << " ";
        current = node.first->get_right();
    }
    cout << endl;
}

int SpecialBinaryTree::find_sum_of_values_in_subtree(int subtree_root_val) {
    // Helper function to find the sum of values in a subtree rooted at a given node
    queue<BinaryTreeNode*> q;
    q.push(root);
    BinaryTreeNode* subtree_root = nullptr;
    while (!q.empty()) {
        BinaryTreeNode* current = q.front();
        q.pop();
        if (current->get_value() == subtree_root_val) {
            subtree_root = current;
            break;
        }
        if (current->get_left() != nullptr) {
            q.push(current->get_left());
        }
        if (current->get_right() != nullptr) {
            q.push(current->get_right());
        }
    }
    if (subtree_root == nullptr) {
        return -1; // Subtree root not found
    }
    // Perform BFS traversal in the subtree to find sum of values
    int sum = 0;
    q.push(subtree_root);
    while (!q.empty()) {
        BinaryTreeNode* current = q.front();
        q.pop();
        sum += current->get_value();
        if (current->get_left() != nullptr) {
            q.push(current->get_left());
        }
        if (current->get_right() != nullptr) {
            q.push(current->get_right());
        }
    }
    return sum;
}

int SpecialBinaryTree::find_minimum_value_in_subtree(int subtree_root_val) {
    // Helper function to find the minimum value in a subtree rooted at a given node
    queue<BinaryTreeNode*> q;
    q.push(root);
    BinaryTreeNode* subtree_root = nullptr;
    while (!q.empty()) {
        BinaryTreeNode* current = q.front();
        q.pop();
        if (current->get_value() == subtree_root_val) {
            subtree_root = current;
            break;
        }
        if (current->get_left() != nullptr) {
            q.push(current->get_left());
        }
        if (current->get_right() != nullptr) {
            q.push(current->get_right());
        }
    }
    if (subtree_root == nullptr) {
        return -1; // Subtree root not found
    }
    // Perform BFS traversal in the subtree to find minimum value
    int min_val = INT_MAX;
    q.push(subtree_root);
    while (!q.empty()) {
        BinaryTreeNode* current = q.front();
        q.pop();
        min_val = min(min_val, current->get_value());
        if (current->get_left() != nullptr) {
            q.push(current->get_left());
        }
        if (current->get_right() != nullptr) {
            q.push(current->get_right());
        }
    }
    return min_val;
}

int SpecialBinaryTree::find_maximum_value_in_subtree(int subtree_root_val) {
    // Helper function to find the maximum value in a subtree rooted at a given node
    queue<BinaryTreeNode*> q;
    q.push(root);
    BinaryTreeNode
* subtree_root = nullptr;
    while (!q.empty()) {
        BinaryTreeNode* current = q.front();
        q.pop();
        if (current->get_value() == subtree_root_val) {
            subtree_root = current;
            break;
        }
        if (current->get_left() != nullptr) {
            q.push(current->get_left());
        }
        if (current->get_right() != nullptr) {
            q.push(current->get_right());
        }
    }
    if (subtree_root == nullptr) {
        return -1; // Subtree root not found
    }
    // Perform BFS traversal in the subtree to find maximum value
    int max_val = INT_MIN;
    q.push(subtree_root);
    while (!q.empty()) {
        BinaryTreeNode* current = q.front();
        q.pop();
        max_val = max(max_val, current->get_value());
        if (current->get_left() != nullptr) {
            q.push(current->get_left());
        }
        if (current->get_right() != nullptr) {
            q.push(current->get_right());
        }
    }
    return max_val;
}

#ifndef SPECIAL_BINARY_TREE_H
#define SPECIAL_BINARY_TREE_H

class BinaryTreeNode; // Forward declaration

class SpecialBinaryTree
{
private:
    BinaryTreeNode *root;

    // Helper function for destructor
    void delete_tree(BinaryTreeNode* node);

public:
    SpecialBinaryTree();
    ~SpecialBinaryTree();

    bool add_node(int new_value, int parent_value, bool is_left_child, bool is_right_child, bool is_root);
    bool update_value(int previous_value, int new_value);
    bool remove_node(int value);
    int is_leaf_node(int value);
    bool does_exist_in_subtree(int subtree_root_value, int value_to_search);
    int find_depth(int value);
    int find_height(int value);
    void preorder_traversal();
    void postorder_traversal();
    void inorder_traversal();
    int find_sum_of_values_in_subtree(int subtree_root_val);
    int find_minimum_value_in_subtree(int subtree_root_val);
    int find_maximum_value_in_subtree(int subtree_root_val);

    // New helper functions could be added here if needed
};

#endif // SPECIAL_BINARY_TREE_H

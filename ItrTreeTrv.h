#pragma once

typedef int value;

struct tree_node{
	value data;
	struct tree_node* left,* right;
};

typedef struct tree_node TreeNode;

extern void itr_inorder_traversal(TreeNode* root);

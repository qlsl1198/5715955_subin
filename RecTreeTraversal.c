#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode{
    int data;
    struct TreeNode* left, * right;
} TreeNode;

void Pre_Order_By_Pointer(TreeNode* np);
void In_Order_By_Pointer(TreeNode* np);
void Post_Order_By_Pointer(TreeNode* np);
void Pre_Order_in_Array(int* Tree, int index);

int main(){
    int Tree[8] = {-1, 10, 5, 9, 6, 3, -1, 7}; /* Tree in Array */
    
    TreeNode n1, n2, n3, n4, n5, n6;
    n1.data = 10, n1.left = &n2, n1.right = &n3;
    n2.data = 5, n2.left = &n4, n2.right = &n5;
    n3.data = 9, n3.left = NULL, n3.right = &n6;
    n4.data = 6, n4.left = NULL, n4.right = NULL;
    n5.data = 3, n5.left = NULL, n5.right = NULL;
    n6.data = 7, n6.left = NULL, n6.right = NULL;

    printf("전위순회 (포인터) : \n");
    Pre_Order_By_Pointer(&n1);
    printf("\n");
    
    printf("전위순회 (배열) : \n");
    Pre_Order_in_Array(Tree, 1);
    printf("\n");
    
    printf("중위순회 : \n");
    In_Order_By_Pointer(&n1);
    printf("\n");
    
    printf("후위순회 : \n");
    Post_Order_By_Pointer(&n1);
    printf("\n");

    return 0;
}

void Pre_Order_By_Pointer(TreeNode* np){
    if( np != NULL){
        printf("[%2d]", np->data);
        Pre_Order_By_Pointer(np->left);
        Pre_Order_By_Pointer(np->right);
    }
}

void Pre_Order_in_Array(int* Tree, int index){
    if (index < 8 && Tree[index] != -1){
        printf("[%2d]", Tree[index]);
        Pre_Order_in_Array(Tree, index*2);
        Pre_Order_in_Array(Tree, index*2+1);
    }
}

void In_Order_By_Pointer(TreeNode* np){
    if( np != NULL){
        In_Order_By_Pointer(np->left);
        printf("[%2d]", np->data);
        In_Order_By_Pointer(np->right);
    }
}

void Post_Order_By_Pointer(TreeNode* np){
    if( np != NULL){
        Post_Order_By_Pointer(np->left);
        Post_Order_By_Pointer(np->right);
        printf("[%2d]", np->data);
    }
}
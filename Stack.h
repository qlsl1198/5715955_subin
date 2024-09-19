#pragma once
#include "ItrTreeTrv.h"
typedef TreeNode* element;
typedef struct StackNode {
	element data;
	struct StackNode* link;
} StackNode;

typedef struct {
	StackNode* top;
} LinkedStackType;

extern void init(LinkedStackType* s);
extern int is_empty(LinkedStackType* s);
extern int is_full(LinkedStackType* s);
extern void push(LinkedStackType* s, element item);
extern void print_stack(LinkedStackType* s);
extern element pop(LinkedStackType* s);
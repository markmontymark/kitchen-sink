#ifndef __ORDERED_TREE_H_
#define __ORDERED_TREE_H_

typedef struct ordered_tree_str ordered_tree_str_t;
typedef struct ordered_tree ordered_tree_t;

struct ordered_tree_str
{
	char * str;
	int count;
	ordered_tree_str_t * left;
	ordered_tree_str_t * right;
};

struct ordered_tree
{
	void * data;
	ordered_tree_t * left;
	ordered_tree_t * right;
};


ordered_tree_str_t * ordered_tree_str_new(char * str);
void ordered_tree_str_free(ordered_tree_str_t * node);
void ordered_tree_str_add(ordered_tree_str_t * node,char * str);
void ordered_tree_str_traverse(ordered_tree_str_t * node,void (* func)(ordered_tree_str_t * node) );

ordered_tree_t * ordered_tree_new(void * data, void * ( *func_copy_ctor)(void * d));
void ordered_tree_free(ordered_tree_t * node, void (*func)(void * data));
void ordered_tree_add (ordered_tree_t * node, ordered_tree_t * new_node, int (* func_comparator)(void * a,void * b));
void ordered_tree_traverse(ordered_tree_t * node,void (* func)(void * node) );

#endif

#include <stdio.h>
#include "../../src/data/ordered_tree.h"

void print_ordered_tree_str( ordered_tree_str_t * node )
{
	printf("%s\n",node->str);
}

int main(int argc, char ** argv)
{
	ordered_tree_str_t * root = ordered_tree_str_new("middle");
	ordered_tree_str_add(root,"beginning");
	ordered_tree_str_add(root,"z end");
	ordered_tree_str_traverse(root, print_ordered_tree_str);
	ordered_tree_str_free(root);
	return 0;
}


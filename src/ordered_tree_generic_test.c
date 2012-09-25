#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ordered_tree.h"

struct book
{
	int n_pages;
	char * title;
};

void * book_copy_ctor( void * data )
{
	struct book * bk_to_copy = (struct book *) data;
	struct book * bk = malloc(sizeof(struct book));
	bk->title = strdup( bk_to_copy->title);
	bk->n_pages = bk_to_copy->n_pages;
	return bk;
}

void book_traverse( void * data )
{
	struct book * bk = (struct book *)data;
	printf("%s has %d pages\n",bk->title, bk->n_pages);
}

void book_free( void * data )
{
	if( data == NULL )
		return;
	struct book * bk = (struct book *)data;
	free(bk->title);
}

int book_comparator( void * a, void * b )
{
	struct book * bk_a = (struct book *) a;
	struct book * bk_b = (struct book *) b;
	return strcmp(bk_a->title,bk_b->title);
}


int main(int argc, char ** argv)
{
	struct book bk_root = {10,"ignore"};
	//struct book * bk_root = &bk;
	ordered_tree_t * root = ordered_tree_new( &bk_root,book_copy_ctor );
	bk_root.n_pages = 12;
	bk_root.title = "Title blah";
	ordered_tree_add(root,ordered_tree_new(&bk_root,book_copy_ctor), book_comparator);
	bk_root.n_pages = 14;
	bk_root.title = "aSasfsdfdsTitle blah";
	ordered_tree_add(root,ordered_tree_new(&bk_root,book_copy_ctor),book_comparator);
	ordered_tree_traverse(root, book_traverse );
	ordered_tree_free(root,book_free);
	return 0;
}


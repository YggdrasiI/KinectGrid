#ifndef MYBLOB_H
#define MYBLOB_H

#include <limits.h>

/* Set this env. variable to enable diagonal checks */
#define BLOB_DIAGONAL_CHECK

/* Eval vertiacal and horizontal dimension */
#define BLOB_DIMENSION

#include "tree.h"

/* Find Blobs. 
 * Parameter:
 * 	In: 
 * 		-unsigned char *data: Image data
 * 		-int w, int h: Dimension of image
 * 		-int thresh: Distinct values in x>thresh and x<=thresh.
 * 	Out:
 * 		-int *tree_size: Number of nodes. Use this to free the tree memory.
 * 	Return: 
 * 		node*: Pointer to array of nodes. It's the pointer to the root node, too.
 *
 * Requires: All Borderelements are Zeros. 
 *   0---0 
 * h | A |  }data
 *   0---0 
 *     w
 */
static Node* find_connection_components(
		const unsigned char *data,
		const int w, const int h,
		const unsigned char thresh,
		int* tree_size );

/* With region of interrest (roi) */
static Node* find_connection_components_with_roi(
		const unsigned char *data,
		const int w, const int h,
		const MyBlobRect roi,
		const unsigned char thresh,
		int* tree_size );


typedef enum { F_DEPTH_MIN=1, F_DEPTH_MAX=2, F_AREA_MIN=4, F_AREA_MAX=8 } FILTER;

typedef struct {
	int min_depth;
	int max_depth;
	int min_area;
	int max_area;
} Filter;

typedef struct {
	Node *tree; //root of tree
	int tree_size; //Size of underlying array of tree. 
	Filter filter;
	Node *it; //intern note for iteration
	int it_depth; //depth of it.
} Myblob;


/* Create blob struct. Use myblob_destroy to free mem. */
 Myblob *myblob_create();
 void myblob_destroy(Myblob *blob );
/* Main function to eval blobs */
 void myblob_find_blobs( Myblob *blob, 
		const unsigned char *data, 
		const int w, const int h,
		const MyBlobRect roi,
		const unsigned char thresh );
 void myblob_set_filter( Myblob *blob,const FILTER f,const int val);
/* Returns first node which matching the filter criteria.
 * or NULL */
 Node *myblob_first( Myblob *blob);
/* Returns next element under the given filters. 
 * or NULL */
 Node *myblob_next( Myblob *blob);


#endif

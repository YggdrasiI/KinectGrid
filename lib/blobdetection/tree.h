#ifndef TREE_H
#define TREE_H

#ifndef INLINE
#define INLINE extern inline
#endif

/*
 * Simple Treestructure with Nodes N={parent,next_silbing,child,data}
 *
 * */

#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <stdio.h>

#include "settings.h"

// Like opencvs Rect_<int>
typedef struct {
	int x,y,width,height;
} BlobtreeRect;

/* Minimal Node struct
 * Note: The height value stores the length of the longest path of successors, not
 * the depth to a (unknown) root node.
 * */
typedef struct Node Node;
 struct Node {
	Node *parent;
	Node *silbing;
	Node *child;/* second child reachable as silbing of first child and so on… */
	unsigned int height; /* height = maximal reachable depth */
	unsigned int width; /* number of children */
	void *data;
};
static const struct Node Leaf = { NULL,NULL,NULL,0,0, NULL };

/* The data struct for both algorithms.
 * Some functions, who operate on a tree
 * expect this data struct. This functions
 * should be recognizeable by its names. */
typedef struct Blob{
	unsigned int id;
	BlobtreeRect roi;
	unsigned int area;
#ifdef SAVE_DEPTH_MAP_VALUE
	unsigned char depth_level; 
#endif
#ifdef BLOB_BARYCENTER
	int barycenter[2];
#endif
} Blob;


typedef struct {
	Node *root; // root of tree. Required to release mem in tree_destroy(). 
	unsigned int size;//length of data and root array.
} Tree;

/* Allocate tree struct. If you use 
 * the data pointer of the nodes you has to 
 * setup/handle the storage for this data 
 * separatly */
Tree *tree_create(unsigned int size);

/* Dealloc tree. Attention, target of data pointer is not free'd. */
void tree_destroy(Tree **tree);

/* Eval height and number of children for each Node */
void gen_redundant_information(Node * const root, unsigned int *pheight, unsigned int *psilbings);

/* Eval height and number of children for each Node */
void gen_redundant_information_recursive(Node* root, unsigned int *pheight, unsigned int *psilbings);

void add_child(Node *parent, Node *child);

unsigned int number_of_nodes(Node *root);

/* Textual output of tree. Shift defines number of spaces at line beginning. */
void print_tree(Node *root, int shift);

/* Print only nodes with area>=minA */
void print_tree_filtered(Node *root, int shift, unsigned int minA);


/* 
 * Helper functions for sorting 
 * */
// Swap nodes with same parent
INLINE void swap_silbings(Node *a, Node *b);


/* returns 1, if a>b, and 0 otherwise. (do not use (1,0,-1) like strcmp ) */
INLINE int cmp(Node *a, Node *b);

INLINE void swap_pnode(Node **a, Node **b);

INLINE int successor(Node *parent, Node *child);

void quicksort_silbings(Node **begin, Node **end);

/*
 * End Helper functions for sorting
 * */


/* Sorting the nodes such that topological equal trees has
 * the same image. The algorithm sort rekursivly all children
 * and then the silbings with quicksort.
 *
 * */
void sort_tree(Node *root);

/* Generate unique id for sorting trees.
 * [DE] Wird ein Baum durchlaufen und für jeden Schritt angegeben, ob als nächstes ein
 * Kindknoten oder der nächste Geschwisterknoten auf x-ter Ebene ist, so entsteht eine
 * eindeutige Id eines Baumes. Diese kann später für vergleiche genutzt werdne.
 * Kann man das noch komprimieren, wenn man als Basis die maximale Tiefe wählt?!
 *
 * */
void _gen_tree_id(Node *root,unsigned int **id, unsigned int *d);


/* Generate Unique Number [xyz...] for node
 * Preallocate id-array with #nodes(root).
 * */
void gen_tree_id(Node *root, unsigned int* id, unsigned int size);

#ifdef BLOB_COUNT_PIXEL
unsigned int sum_areas(Node * const root, const unsigned int * const comp_size);
#ifdef BLOB_DIMENSION
void approx_areas(const Tree * const tree, Node * const startnode,
		const unsigned int * const comp_size,
		const unsigned int stepwidth, const unsigned int stepheight);
#endif
#endif

#ifdef BLOB_BARYCENTER
void eval_barycenters( Node *const start_node,
		const Node * const root,
		const unsigned int * const comp_size,
		BLOB_BARYCENTER_TYPE * const pixel_sum_X,
		BLOB_BARYCENTER_TYPE * const pixel_sum_Y
		);
#endif

#ifdef BLOB_DIMENSION
void set_area_prop(Node *root);
#endif

// Debug/Helper-Functions
char * debug_getline(void); 
void debug_print_matrix( unsigned int* data, unsigned int w, unsigned int h, BlobtreeRect roi, unsigned int gridw, unsigned int gridh);
void debug_print_matrix2(unsigned int* ids, unsigned int* data, unsigned int w, unsigned int h, BlobtreeRect roi, unsigned int gridw, unsigned int gridh, char twice);
void debug_print_matrix_char( unsigned char * data, unsigned int w, unsigned int h, BlobtreeRect roi, unsigned int gridw, unsigned int gridh);

#endif

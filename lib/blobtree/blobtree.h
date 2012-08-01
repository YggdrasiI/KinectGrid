#ifndef BLOBTREE_H
#define BLOBTREE_H

#include <limits.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 0, 1, 2(with stops) */
#define VERBOSE 0 

/* Sort tree by child node structure and area size. This provide 
	 some robustness on rotation for tree comparison. */
#define BLOB_SORT_TREE

/* Set this env. variable to enable diagonal checks */
#define BLOB_DIAGONAL_CHECK

/* Eval vertiacal and horizontal dimension */
#define BLOB_DIMENSION

/* Count pixels of each area. (Stored in node.data.area).
 * This is more accurate then
 * area.width*area.height but not calculable if stepwidth>1.
 * If stepwidth>1 and BLOB_DIMENSION is set,
 * the node.data.area value will set to
 * area.width * area.height.
 * Do not define BLOB_COUNT_PIXEL if you want use stepwidth>1
 * to cut of some operations.
 */
#define BLOB_COUNT_PIXEL

/* See README
 */
#define BLOB_SUBGRID_CHECK


#if VERBOSE > 0
#define VPRINTF(...) printf(__VA_ARGS__);
#else
#define VPRINTF(...) 
#endif

#include "tree.h"

/* Find Blobs. 
 *
 * Assumption: All border elements x fulfill 
 * 'x > thresh' or 'x <= thresh'
 *
 *   0---0 
 * h | A |  }data
 *   0---0 
 *     w
 *
 * Parameter:
 * 	In: 
 * 		-unsigned char *data: Image data
 * 		-int w, int h: Dimension of image
 * 		-int thresh: Distinct values in x>thresh and x<=thresh.
 * 	Out:
 * 		-int *tree_size: Number of nodes/ Length of the underlying array of the tree nodes. 
 * 	Return: 
 * 		-node*: Pointer to the array of nodes. 
 * 		 It's the pointer to the root node, too. If all assumtions fulfilled, node has
 * 		 exact one child which represent the full area.
 *
 */
static Node* find_connection_components(
		const unsigned char *data,
		const int w, const int h,
		const unsigned char thresh,
		int* tree_size );

 
/* Find Blobs. With region of interrest (roi).
 *
 * Assumption: All border elements x of roi fulfill 
 * 'x > thresh' or 'x <= thresh'
 *
 *  ____________________
 * |                    |
 * |            0---0   |
 * | roi.height | A |   |  } data
 * |            0---0   |
 * |         roi.width  |
 * |____________________|
 *
 * Parameter:
 * 	In: 
 * 		-unsigned char *data: Image data
 * 		-int w, int h: Dimension of image
 * 		-BlobtreeRect roi: Simple struct to describe roi, {x,y,width,height}.
 * 		-int thresh: Distinct values in x>thresh and x<=thresh.
 * 	Out:
 * 		-int *tree_size: Number of nodes/ Length of the underlying array of the tree nodes. 
 * 	Return: 
 * 		-node*: Pointer to the array of nodes. 
 * 		 It's the pointer to the root node, too. If all assumtions fulfilled, node has
 * 		 exact one child which represent the full area.
 *
 */
static Node* find_connection_components_roi(
		const unsigned char *data,
		const int w, const int h,
		const BlobtreeRect roi,
		const unsigned char thresh,
		int* tree_size );


/* Find Blobs. With flexible stepwidth and
 *  region of interrest (roi).
 *  Only an subset of all pixels (grid structure) will checked.
 *  Stepwidth and stepheight control the mesh size.
 *  Attention: The founded bounding box values are not exact.
 *
 * Assumption: All border elements x of roi fulfill 
 * 'x > thresh' or 'x <= thresh'
 *
 *  ____________________
 * |                    |
 * |            0---0   |
 * | roi.height | A |   |  } data
 * |            0---0   |
 * |         roi.width  |
 * |____________________|
 *
 * Parameter:
 * 	In: 
 * 		-unsigned char *data: Image data
 * 		-int w, int h: Dimension of image
 * 		-BlobtreeRect roi: Simple struct to describe roi, {x,y,width,height}.
 * 		-int thresh: Distinct values in x>thresh and x<=thresh.
 * 		-int stepwidth: 
 * 	Out:
 * 		-int *tree_size: Number of nodes/ Length of the underlying array of the tree nodes. 
 * 	Return: 
 * 		-node*: Pointer to the array of nodes. 
 * 		 It's the pointer to the root node, too. If all assumtions fulfilled, node has
 * 		 exact one child which represent the full area.
 *
 */
static Node* find_connection_components_coarse(
		const unsigned char *data,
		const int w, const int h,
		const BlobtreeRect roi,
		const unsigned char thresh,
		const int stepwidth,
		const int stepheight,
		int* tree_size );


#ifdef BLOB_SUBGRID_CHECK 
/* Find Blobs. With flexible stepwidth and
 *  region of interrest (roi).
 *  An subset of all pixels (grid structure) will checked.
 *  Stepwidth controls the mesh size. If an blob was detected
 *  the neighbourhood will regard to get the exact blob dimensions.
 *  Nevertheless, there is no quarantee to recognise fine structures.
 *
 * Assumption: All border elements x of roi fulfill 
 * 'x > thresh' or 'x <= thresh'
 *
 *  ____________________
 * |                    |
 * |            0---0   |
 * | roi.height | A |   |  } data
 * |            0---0   |
 * |         roi.width  |
 * |____________________|
 *
 * Parameter:
 * 	In: 
 * 		-unsigned char *data: Image data
 * 		-int w, int h: Dimension of image
 * 		-BlobtreeRect roi: Simple struct to describe roi, {x,y,width,height}.
 * 		-int thresh: Distinct values in x>thresh and x<=thresh.
 * 		-int stepwidth: 
 * 	Out:
 * 		-int *tree_size: Number of nodes/ Length of the underlying array of the tree nodes. 
 * 	Return: 
 * 		-node*: Pointer to the array of nodes. 
 * 		 It's the pointer to the root node, too. If all assumtions fulfilled, node has
 * 		 exact one child which represent the full area.
 *
 */

static Node* find_connection_components_subcheck(
		const unsigned char *data,
		const int w, const int h,
		const BlobtreeRect roi,
		const unsigned char thresh,
		const int stepwidth,
		int* tree_size );
#endif




typedef enum { F_DEPTH_MIN=1, F_DEPTH_MAX=2, F_AREA_MIN=4, F_AREA_MAX=8 } FILTER;

typedef struct {
	int width;
	int height;
} Grid;

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
	Grid grid; // width between compared pixels (Could leave small blobs undetected.)
	Node *it; //intern note for iteration
	int it_depth; //depth of it.
} Blobtree;


/* Create blob struct. Use blobtree_destroy to free mem. */
Blobtree *blobtree_create();
void blobtree_destroy(Blobtree *blob );
/* Main function to eval blobs */
void blobtree_find_blobs( Blobtree *blob, 
		const unsigned char *data, 
		const int w, const int h,
		const BlobtreeRect roi,
		const unsigned char thresh );
void blobtree_set_filter( Blobtree *blob,const FILTER f,const int val);
/* Set difference between compared pixels. Could ignore small blobs. */
void blobtree_set_grid(Blobtree *blob, const int gridwidth, const int gridheight );
/* Returns first node which matching the filter criteria.
 * or NULL */
Node *blobtree_first( Blobtree *blob);
/* Returns next element under the given filters. 
 * or NULL */
Node *blobtree_next( Blobtree *blob);

#ifdef __cplusplus
}
#endif


#endif

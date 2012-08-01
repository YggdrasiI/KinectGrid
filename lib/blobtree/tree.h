#ifndef TREE_H
#define TREE_H

/* Simple Treestructure with Nodes N={parent,next_silbing,child,data} */
#include <stdio.h>

// Like opencvs Rect_<int>
typedef struct {
	int x,y,width,height;
} BlobtreeRect;

/* The data struct */
typedef struct Blob{
	int id;
	BlobtreeRect roi;
//	int width;
//	int height;
	int area;
} Blob;

/* node struct */
typedef struct Node Node;
 struct Node {
	Node *parent;
	Node *silbing;
	Node *child;/* second child reachable as silbing of first child and so on… */
	int height; /* height = maximal reachable depth */
	int width; /* number of children */
	Blob data;
};

static struct Node Leaf = { NULL,NULL,NULL,0,0 };

/* Eval height and number of children for each Node */
static void gen_redundant_information(Node* root, int *pheight, int *psilbings){
	root->width = 0;
	if( root->child != NULL ){
		int height2=0;
		gen_redundant_information(root->child, &height2, &root->width);
		if( *pheight < height2+1 ) *pheight = height2+1;//update height of parent node
	}
	if( root->silbing != NULL ){
		*psilbings++;//update number of children for parent node
		gen_redundant_information(root->silbing,pheight,psilbings);
	}
}

static void add_child(Node *parent, Node *child){
	if( parent->child == NULL ){
		parent->child = child;
	}else{
		Node *cur = parent->child;
		while( cur->silbing != NULL ){
			cur = cur->silbing;
		}
		cur->silbing = child;
	}
	//set parent of child
	child->parent = parent;

	//update redundant information
	parent->width++;
	Node *p=parent, *c=child;
	while( p != NULL && p->height < c->height+1 ){
		p->height = c->height+1;
		c=p;
		p=p->parent;
	}
}

static int number_of_nodes(Node *root){
 int n = 1;
 Node *cur = root->child;
 while( cur != NULL ){
	 n++;
	 if( cur->child != NULL ) cur = cur->child;
	 else if( cur->silbing != NULL ) cur = cur->silbing;
	 else{
		 cur = cur->parent;
		 while(cur != root && cur->silbing == NULL) cur = cur->parent;
		 cur = cur->silbing;
	 }
 }
 return n;
}


static void print_tree_filtered(Node *root, int shift, int minA){
	int i;
	int shift2=0;
	//printf("• ");
	//printf("%i (%i) ",root->data.id, root->data.area);
	printf("%2i (w%i,h%i,a%2i) ",root->data.id, root->width, root->height, root->data.area);
	shift2+=12+4;
	if( root->data.area < minA){
		printf("\n");
		return;
	}
	if( root->child != NULL){
		printf("→");
		print_tree_filtered(root->child,shift+shift2,minA);
	}else{
		printf("\n");
	}

	if( root->silbing != NULL){
	//	printf("\n");
		for(i=0;i<shift-1;i++) printf(" ");
		printf("↘");
		print_tree_filtered(root->silbing,shift,minA);
	}
}

static void print_tree(Node *root, int shift){
	return print_tree_filtered(root,shift,-1);
}

/* 
 * Helper functions for sorting 
 * */
// Swap nodes with same parent
static inline void swap_silbings(Node *a, Node *b)
{
	Node *p = a->parent;
	Node *c = p->child;
	Node *d = p->child;
	//serach c,d with ...,c,a,...,d,b order
	if(c==a) c == NULL;
	else{
		while(c->silbing!=a) c=c->silbing;
	}
	if(d==b) d == NULL;
	else{
		while(d->silbing!=b) d=d->silbing;
	}

	//swap anchor of a and b
	if( c == NULL ) p->child = b;
	else c->silbing = b;
	if( d == NULL ) p->child = a;
	else d->silbing = a;
	
	//at least, swap silbings
	d = a->silbing;
	a->silbing = b->silbing;
	b->silbing = d;
}

/* returns 1, if a>b, and 0 otherwise. (do not use (1,0,-1) like strcmp ) */
static inline int cmp(Node *a, Node *b){
	if( a->height < b->height) return 0;
	if( a->height > b->height) return 1;
	if( a->width < b->width) return 0;
	if( a->width > b->width) return 1;

	/* Now assme, that children already sorted.
	 * Then for topological equalness only i-th child of a needs
	 * compared with i-th child of b.
	 * */
	int ret=0;
	Node *ca = a->child;
	Node *cb = b->child;
	while( ret == 0 && ca!=NULL ){
		ret = cmp(ca,cb);
		ca=ca->silbing;
		cb=cb->silbing;
	}
	return ret;
}

static inline void swap_pnode(Node **a, Node **b)
{
    Node *tmp = *a;
    *a = *b;
    *b = tmp;
}

static void quicksort_silbings(Node **begin, Node **end)
{
    Node **ptr;
    Node **split;
    if (end - begin <= 1)
        return;
    ptr = begin;
    split = begin + 1;
    while (++ptr != end) {
        //if ( **ptr < **begin ) {
				if ( cmp(*ptr,*begin)  ) {
            swap_pnode(ptr, split);
            ++split;
        }
    }
    swap_pnode(begin, split - 1);
    quicksort_silbings(begin, split - 1);
    quicksort_silbings(split, end);
}

/*
 * End Helper functions for sorting
 * */

/* Sorting the nodes such that topological equal trees has
 * the same image. The algorithm sort rekursivly all children
 * and then the silbings with quicksort.
 *
 * */
static void sort_tree(Node *root){
	 	if( root->width == 0) return;//leaf reached
	  /* Sort children and store pointer to this children */
	  Node** children = (Node**) malloc( root->width*sizeof(Node*) );
		Node** next = children;
		Node* c = root->child;
		while( c != NULL ){
			sort_tree(c);
			*next=c;
			c = c->silbing;
			next++;
		}
		//now, next points behind children array
		if( root->width > 1){
			Node** end = next;

			quicksort_silbings(children, end);

			//rearange children of root like sorted array propose.
			c = *children;
			root->child = c;
			next = children+1;
			while(next<end){
				c->silbing = *next;
				c=*next;
				next++;
			}
			c->silbing = NULL;//remove previous anchor in last child.
		}

		free( children );
 }

/* Generate unique id for sorting trees.
 * [DE] Wird ein Baum durchlaufen und für jeden Schritt angegeben, ob als nächstes ein
 * Kindknoten oder der nächste Geschwisterknoten auf x-ter Ebene ist, so entsteht eine
 * eindeutige Id eines Baumes. Diese kann später für vergleiche genutzt werdne.
 * Kann man das noch komprimieren, wenn man als Basis die maximale Tiefe wählt?!
 *
 * */
static void _gen_tree_id(Node *root,int **id, int *d){
	if( root->child != NULL ){
		//printf("o ");
		**id = 0;
		(*id)++;//set pointer to next array element
		_gen_tree_id(root->child, id, d);
	}else{
		*d = root->height;//store height of leaf.
	}
	if( root->silbing != NULL ){
		//print difference from last leaf and this node and add 1
		//printf("%i ", root->height -*d +1 );
		**id = (root->height - *d + 1);
		(*id)++;//set pointer to next array element
		*d=root->height;
		_gen_tree_id(root->silbing, id, d);
	}
}

/* Generate Unique Number [xyz...] for node
 * Preallocate id-array with #nodes(root).
 * */
static void gen_tree_id(Node *root, int* id, int size){
 int last_height=0;
 //store size of array in first element
 *id = size;
 id++;
 _gen_tree_id(root,&id,&last_height);
 printf("\n");
}


/* tree_hashval
 * Berechnet für einen Baum eine Id, die eindeutig ist, 
 * wenn die Bäume eine bestimmte Struktur einhalten.
 * Die Struktur der Bäume (z.B. max. Anzahl der Kinder)
 *  ist grob einstellbar.
 */
static const int TREE_CHILDREN_MAX = 5;
static const int TREE_DEPTH_MAX = 5;//height of root is 0.

static int tree_hashval( Node *root){
	return -1;
}


#endif

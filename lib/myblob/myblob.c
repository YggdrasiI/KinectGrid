#ifndef MYBLOB_C
#define MYBLOB_C

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "myblob.h"

#ifdef BLOB_DIMENSION 
#define NEW_COMPONENT \
	id++; \
*(iPi) = id; \
*(anchors+id) = dPi-dS; \
*(comp_same+id) = id; \
*(comp_size+id) = 1; \
*(left_index+id) = s; \
*(right_index+id) = s; \
*(bottom_index+id) = z; \
if( id>=max_comp ){ \
	max_comp = (int) ( (float)w*h*max_comp/(dPi-data) ); \
	anchors = realloc(anchors, max_comp*sizeof(int) ); \
	comp_size = realloc(comp_size, max_comp*sizeof(int) ); \
	comp_same = realloc(comp_same, max_comp*sizeof(int) ); \
	left_index = realloc(left_index, max_comp*sizeof(int) ); \
	right_index = realloc(right_index, max_comp*sizeof(int) ); \
	bottom_index = realloc(bottom_index, max_comp*sizeof(int) ); \
} 
#else
#define NEW_COMPONENT \
	id++; \
*(iPi) = id; \
*(anchors+id) = dPi-dS; \
*(comp_same+id) = id; \
*(comp_size+id) = 1; \
if( id>=max_comp ){ \
	max_comp = (int) ( (float)w*h*max_comp/(dPi-data) ); \
	anchors = realloc(anchors, max_comp*sizeof(int) ); \
	comp_size = realloc(comp_size, max_comp*sizeof(int) ); \
	comp_same = realloc(comp_same, max_comp*sizeof(int) ); \
} 
#endif

static int sum_areas(const Node *root, const int *comp_size){
	int *val=&root->data.area;
	*val = *(comp_size + root->data.id );
	if( root->child != NULL) *val += sum_areas(root->child,comp_size);
	if( root->silbing != NULL) return *val+sum_areas(root->silbing, comp_size);
	else return *val;
}

static Node* find_connection_components(
		const unsigned char *data,
		const int w, const int h,
		const unsigned char thresh,
		int* tree_size )
{
	const MyBlobRect roi = {0,0,w,h};
	return find_connection_components_with_roi(data,w,h,roi,thresh,tree_size);
}

/* With region of interrest (roi) */
static Node* find_connection_components_with_roi(
		const unsigned char *data,
		const int w, const int h,
		const MyBlobRect roi,
		const unsigned char thresh,
		int* tree_size )
{
	//init
	int r=w-roi.x-roi.width; //right border
  int b=h-roi.y-roi.height; //bottom border
	if( r<0 || b<0 ){
		fprintf(stderr,"[blob.c] MyBlobRect not matching.\n");
		*tree_size = 0;
		return NULL;
	}

	int id=-1;//id for next component
	int a1,a2; // for comparation of g(f(x))=a1,a2=g(f(y)) 
	int k; //loop variable
	int max_comp = w+h;//maximal number of components. If the value is reached some arrays will reallocate.

	int* ids = malloc( w*h*sizeof(int) ); // store ids: f(A(i,j)) = id
	//char** anchors = malloc( max_comp*sizeof(char*) ); //store positions of first elements with id.
	int* anchors = malloc( max_comp*sizeof(int) ); //store positions of first elements with id.
	int* comp_size = malloc( max_comp*sizeof(int) ); //store the size of each component. 
	int* comp_same = malloc( max_comp*sizeof(int) ); //map ids to unique ids g:{0,...,}->{0,....}

#ifdef BLOB_DIMENSION
	// most top element of an area is always the anchor element. => No "top_index" array required.
	int* left_index = malloc( max_comp*sizeof(int) ); //save column number of most left element of area.
	int* right_index = malloc( max_comp*sizeof(int) ); //save column number of most right element.
	int* bottom_index = malloc( max_comp*sizeof(int) ); //save row number of most bottom element.
	int s=roi.x,z=roi.y; //s-spalte, z-zeile
#endif

	const unsigned char* dS = data+w*roi.y+roi.x;
	unsigned char* dR = dS+roi.width; //Pointer to right border. Update on every line
	//char* dE = data + (roi.y+roi.height)*w+roi.x + roi.width;
	const unsigned char* dE = dR + (roi.height-1)*w;

//int i = w*roi.y+roi.x;
	unsigned char* dPi = dS; // Pointer to data+i //TODO
	int* iPi = ids+(dS-data); // Poiner to ids+i

	//top, left corner of MyBlobRect get first id.
	/*
	*(iPi) = id;
	*(anchors+id) = dPi-dS;
	*(comp_same+id) = id;
	*(comp_size+id) = 1;
	*/
	NEW_COMPONENT
//i++;
	++iPi; ++dPi;

#ifdef BLOB_DIMENSION
	s++;
#endif
	/* Spilt all logic to two cases: *(dPi)<=thresh, *(dpi)>thresh
	 * to avoid many 'x&&y || x|y==0' checks.
	 * */

	//top border
	for(;dPi<dR;++iPi,++dPi){
		if( *(dPi) > thresh ){
			if( *(dPi-1) > thresh ){//same component as left neighbour
				//*(iPi) = id;
				*(iPi) = *(iPi-1);
				//*(comp_size+id)+=1;
				*(comp_size+ *(iPi)) += 1; //increase counter of this id
#ifdef BLOB_DIMENSION
				//update dimension
				++*( right_index+*(iPi) );
#endif
			}else{//new component
				NEW_COMPONENT
			}
		}else{
			if( *(dPi-1) <= thresh ){//same component as left neighbour
				//*(iPi) = id;
				*(iPi) = *(iPi-1);
				//*(comp_size+id)+=1;
				*(comp_size+ *(iPi)) += 1; //increase counter of this id
#ifdef BLOB_DIMENSION
				//update dimension
				++*( right_index+*(iPi) );
#endif
			}else{//new component
				NEW_COMPONENT
			}
		}
#ifdef BLOB_DIMENSION
		s++;
#endif
		
//i++;

	}

//i+=r+roi.x;
	dPi+=r+roi.x;
	iPi+=r+roi.x;
	// data+i zeigt jetzt in die zweite Zeile, roi.x-te Spalte.
	dR += w; //rechter Randindex wird in nächste Zeile geschoben.
#ifdef BLOB_DIMENSION
	s=roi.x;
	z++;
#endif	

	//2nd,...,h-row
	//for(j=1;j<h;j++)
	for( ; dPi<dE ; dPi+=r+roi.x,iPi+=r+roi.x, dR+=w ){

		//left border
		if( *(dPi) > thresh ){
			if( *(dPi-w) > thresh ){//same component as top neighbour
				*(iPi) = *(iPi-w); //use same id
				*(comp_size+ *(iPi)) += 1; //increase counter of this id
#ifdef BLOB_DIMENSION
				//update dimension
				++*( bottom_index+*(iPi) );
#endif
#ifdef BLOB_DIAGONAL_CHECK
			}else if( *(dPi-w+1) > thresh ){//same component as diagonal neighbour
				*(iPi) = *(iPi-w+1); //use same id
				*(comp_size+ *(iPi)) += 1; //increase counter of this id
#ifdef BLOB_DIMENSION
				//update dimension
				++*( bottom_index+*(iPi) );
				--*( left_index+*(iPi) );
#endif
#endif
			}else{//new component
				NEW_COMPONENT
			}
		}else{
			if( *(dPi-w) <= thresh){//same component as top neighbour
				*(iPi) = *(iPi-w); //use same id
				*(comp_size+ *(iPi)) += 1; //increase counter of this id
#ifdef BLOB_DIMENSION
				//update dimension
				++*( bottom_index+*(iPi) );
#endif
#ifdef BLOB_DIAGONAL_CHECK
			}else if( *(dPi-w+1) <= thresh ){//same component as diagonal neighbour
				*(iPi) = *(iPi-w+1); //use same id
				*(comp_size+ *(iPi)) += 1; //increase counter of this id
#ifdef BLOB_DIMENSION
				//update dimension
				++*( bottom_index+*(iPi) );
				--*( left_index+*(iPi) );
#endif
#endif
			}else{//new component
				NEW_COMPONENT
			}
		}

//i++;
		++iPi; ++dPi;
#ifdef BLOB_DIMENSION
		s++;
#endif

		//inner elements
		//for(k=1;k<w-1;k++)
		for( ; dPi<dR-1; ++iPi, ++dPi ){
			if( *(dPi) > thresh ){
				if( *(dPi-w) > thresh ){//same component as top neighbour
					*(iPi) = *(iPi-w); //use same id
					*(comp_size+ *(iPi)) += 1; //increase counter of this id
#ifdef BLOB_DIMENSION
					//update dimension
					if( *( bottom_index+*(iPi) ) < z ) ++*( bottom_index+*(iPi) );
#endif

					/* check if left neighbour id can associate with top neigbour id.
					 * The diagonal and anti diagonal check is not ness. due to checks on top element.
					 * => g(f(x)) == g(f(y)) 
					 * */
					if( *(dPi-1) > thresh ){
						a1 = *(comp_same+*(iPi-1));
						a2 = *(comp_same+*(iPi  ));
						if( a1<a2 ){
							*(comp_same+*(iPi  )) = a1;
						}else if(a1>a2){
							*(comp_same+*(iPi-1)) = a2;
						}
					}
				}else	if( *(dPi-1) > thresh ){//same component as left neighbour
					*(iPi) = *(iPi-1); //use same id
					*(comp_size+ *(iPi)) += 1; //increase counter of this id
#ifdef BLOB_DIMENSION
					//update dimension
					if( *( right_index+*(iPi) ) < s ) ++*( right_index+*(iPi) );
#endif

#ifdef BLOB_DIAGONAL_CHECK
					/* check if left neighbour id can associate with diagonal neigbour id.
					 * */
					if( *(dPi-w+1) > thresh ){
						a1 = *(comp_same+*(iPi-w+1));
						a2 = *(comp_same+*(iPi    ));
						if( a1<a2 ){
							*(comp_same+*(iPi    )) = a1;
						}else if(a1>a2){
							*(comp_same+*(iPi-w+1)) = a2;
						}
					}
#endif

#ifdef BLOB_DIAGONAL_CHECK
				}else	if( *(dPi-w-1) > thresh ){//same component as anti diagonal neighbour
					*(iPi) = *(iPi-w-1); //use same id
					*(comp_size+ *(iPi)) += 1; //increase counter of this id
#ifdef BLOB_DIMENSION
					//update dimension
					if( *( right_index+*(iPi) ) < s ) ++*( right_index+*(iPi) );
					if( *( bottom_index+*(iPi) ) < z ) ++*( bottom_index+*(iPi) );
#endif

					/* check if diagonal neighbour id can associate with anti diagonal neigbour id.*/
					if( *(dPi-w+1) > thresh ){
						a1 = *(comp_same+*(iPi-w+1));
						a2 = *(comp_same+*(iPi    ));
						if( a1<a2 ){
							*(comp_same+*(iPi    )) = a1;
						}else if(a1>a2){
							*(comp_same+*(iPi-w+1)) = a2;
						}
					}
#endif

#ifdef BLOB_DIAGONAL_CHECK
				}else if( *(dPi-w+1) > thresh ){//same component as diagonal neighbour
					*(iPi) = *(iPi-w+1); //use same id
#ifdef BLOB_DIMENSION
					//update dimension
					if( *( left_index+*(iPi) ) > s ) --*( left_index+*(iPi) );
					if( *( bottom_index+*(iPi) ) < z ) ++*( bottom_index+*(iPi) );
#endif
					*(comp_size+ *(iPi)) += 1; //increase counter of this id
#endif				
				}else{//new component
					NEW_COMPONENT
				}
			}else{
				if( *(dPi-w) <= thresh ){//same component as top neighbour
					*(iPi) = *(iPi-w); //use same id
					*(comp_size+ *(iPi)) += 1; //increase counter of this id
#ifdef BLOB_DIMENSION
					//update dimension
					if( *( bottom_index+*(iPi) ) < z ) ++*( bottom_index+*(iPi) );
#endif

					/* check if left neighbour id can associate with top neigbour id.
					 * The diagonal and anti diagonal check is not ness. due to checks on top element.
					 * => g(f(x)) == g(f(y)) 
					 * */
					if( *(dPi-1) <= thresh ){
						a1 = *(comp_same+*(iPi-1));
						a2 = *(comp_same+*(iPi  ));
						if( a1<a2 ){
							*(comp_same+*(iPi  )) = a1;
						}else if(a1>a2){
							*(comp_same+*(iPi-1)) = a2;
						}
					}
				}else	if( *(dPi-1) <= thresh ){//same component as left neighbour
					*(iPi) = *(iPi-1); //use same id
					*(comp_size+ *(iPi)) += 1; //increase counter of this id
#ifdef BLOB_DIMENSION
					//update dimension
					if( *( right_index+*(iPi) ) < s ) ++*( right_index+*(iPi) );
#endif

#ifdef BLOB_DIAGONAL_CHECK
					/* check if left neighbour id can associate with diagonal neigbour id.
					 * */
					if( *(dPi-w+1) <= thresh ){
						a1 = *(comp_same+*(iPi-w+1));
						a2 = *(comp_same+*(iPi    ));
						if( a1<a2 ){
							*(comp_same+*(iPi    )) = a1;
						}else if(a1>a2){
							*(comp_same+*(iPi-w+1)) = a2;
						}
					}
#endif

#ifdef BLOB_DIAGONAL_CHECK
				}else	if( *(dPi-w-1) <= thresh ){//same component as anti diagonal neighbour
					*(iPi) = *(iPi-w-1); //use same id
					*(comp_size+ *(iPi)) += 1; //increase counter of this id
#ifdef BLOB_DIMENSION
					//update dimension
					if( *( right_index+*(iPi) ) < s ) ++*( right_index+*(iPi) );
					if( *( bottom_index+*(iPi) ) < z ) ++*( bottom_index+*(iPi) );
#endif

					/* check if diagonal neighbour id can associate with anti diagonal neigbour id.*/
					if( *(dPi-w+1) <= thresh ){
						a1 = *(comp_same+*(iPi-w+1));
						a2 = *(comp_same+*(iPi    ));
						if( a1<a2 ){
							*(comp_same+*(iPi    )) = a1;
						}else if(a1>a2){
							*(comp_same+*(iPi-w+1)) = a2;
						}
					}
#endif

#ifdef BLOB_DIAGONAL_CHECK
				}else if( *(dPi-w+1) <= thresh ){//same component as diagonal neighbour
					*(iPi) = *(iPi-w+1); //use same id
#ifdef BLOB_DIMENSION
					//update dimension
					if( *( left_index+*(iPi) ) > s ) --*( left_index+*(iPi) );
					if( *( bottom_index+*(iPi) ) < z ) ++*( bottom_index+*(iPi) );
#endif
					*(comp_size+ *(iPi)) += 1; //increase counter of this id
#endif				
				}else{//new component
					NEW_COMPONENT
				}
			}
#ifdef BLOB_DIMENSION
			s++;
#endif
//i++;			
		}

		//right border, not check diag element
		if( *(dPi) > thresh ){
			if( *(dPi-w) > thresh ){//same component as top neighbour
				*(iPi) = *(iPi-w); //use same id
				*(comp_size+ *(iPi)) += 1; //increase counter of this id
#ifdef BLOB_DIMENSION
				//update dimension
				if( *( bottom_index+*(iPi) ) < z ) ++*( bottom_index+*(iPi) );
#endif

				/* check if left neighbour id can associate with top neigbour id.
				 * The diagonal check is not ness. due to checks on other elements.
				 * => g(f(x)) == g(f(y)) 
				 * */
				if( *(dPi-1) > thresh ){
					a1 = *(comp_same+*(iPi-1));
					a2 = *(comp_same+*(iPi  ));
					if( a1<a2 ){
						*(comp_same+*(iPi  )) = a1;
					}else if(a1>a2){
						*(comp_same+*(iPi-1)) = a2;
					}
				}
			}else	if( *(dPi-1) > thresh ){//same component as left neighbour
				*(iPi) = *(iPi-1); //use same id
				*(comp_size+ *(iPi)) += 1; //increase counter of this id
#ifdef BLOB_DIMENSION
				//update dimension
				if( *( right_index+*(iPi) ) < s ) ++*( right_index+*(iPi) );
#endif
#ifdef BLOB_DIAGONAL_CHECK
			}else	if( *(dPi-w-1) > thresh ){//same component as anti diagonal neighbour
				*(iPi) = *(iPi-w-1); //use same id
				*(comp_size+ *(iPi)) += 1; //increase counter of this id
#ifdef BLOB_DIMENSION
				//update dimension
				if( *( right_index+*(iPi) ) < s ) ++*( right_index+*(iPi) );
				if( *( bottom_index+*(iPi) ) < z ) ++*( bottom_index+*(iPi) );
#endif
#endif
			}else {//new component
				NEW_COMPONENT
			}
		}else{
			if( *(dPi-w) <= thresh ){//same component as top neighbour
				*(iPi) = *(iPi-w); //use same id
				*(comp_size+ *(iPi)) += 1; //increase counter of this id
#ifdef BLOB_DIMENSION
				//update dimension
				if( *( bottom_index+*(iPi) ) < z ) ++*( bottom_index+*(iPi) );
#endif

				/* check if left neighbour id can associate with top neigbour id.
				 * The diagonal check is not ness. due to checks on other elements.
				 * => g(f(x)) == g(f(y)) 
				 * */
				if( *(dPi-1) <= thresh ){
					a1 = *(comp_same+*(iPi-1));
					a2 = *(comp_same+*(iPi  ));
					if( a1<a2 ){
						*(comp_same+*(iPi  )) = a1;
					}else if(a1>a2){
						*(comp_same+*(iPi-1)) = a2;
					}
				}
			}else	if( *(dPi-1) <= thresh ){//same component as left neighbour
				*(iPi) = *(iPi-1); //use same id
				*(comp_size+ *(iPi)) += 1; //increase counter of this id
#ifdef BLOB_DIMENSION
				//update dimension
				if( *( right_index+*(iPi) ) < s ) ++*( right_index+*(iPi) );
#endif
#ifdef BLOB_DIAGONAL_CHECK
			}else	if( *(dPi-w-1) <= thresh ){//same component as anti diagonal neighbour
				*(iPi) = *(iPi-w-1); //use same id
				*(comp_size+ *(iPi)) += 1; //increase counter of this id
#ifdef BLOB_DIMENSION
				//update dimension
				if( *( right_index+*(iPi) ) < s ) ++*( right_index+*(iPi) );
				if( *( bottom_index+*(iPi) ) < z ) ++*( bottom_index+*(iPi) );
#endif
#endif
			}else {//new component
				NEW_COMPONENT
			}
		}
//i++;//increment for new row.
		++iPi; ++dPi;
#ifdef BLOB_DIMENSION
	s=roi.x;
	z++;
#endif
//i+=r+roi.x 
	}

/* end of main algo */

//printf("Matrix of ids:\n");
//print_matrix(ids,w,h);

//printf("comp_same:\n");
//print_matrix(comp_same, id+1, 1);


/* Postprocessing.
 * Sum up all areas with connecteted ids.
 * Then create nodes and connect them. 
 * If BLOB_DIMENSION is set, detectet
 * maximal limits in [left|right|bottom]_index(*(real_ids+X)).
 * */
int nids = id+1; //number of ids
int tmp_id,tmp_id2, real_ids_size=0,l;
int found;
int* real_ids = calloc( nids,sizeof(int) ); //store join of ids.
int* real_ids_inv = calloc( nids,sizeof(int) ); //store for every id with position in real_id link to it's position.

	for(k=0;k<nids;k++){
		tmp_id = k;
		tmp_id2 = *(comp_same+tmp_id); 
		while( tmp_id2 != tmp_id ){
			//move area size to other id.
			*(comp_size+tmp_id2) += *(comp_size+tmp_id); 
			*(comp_size+tmp_id) = 0;
#ifdef BLOB_DIMENSION
			//update dimension
			if( *( left_index+tmp_id2 ) > *( left_index+tmp_id ) )
				*( left_index+tmp_id2 ) = *( left_index+tmp_id );
			if( *( right_index+tmp_id2 ) < *( right_index+tmp_id ) )
				*( right_index+tmp_id2 ) = *( right_index+tmp_id );
			if( *( bottom_index+tmp_id2 ) < *( bottom_index+tmp_id ) )
				*( bottom_index+tmp_id2 ) = *( bottom_index+tmp_id );
#endif
			tmp_id = tmp_id2; 
			tmp_id2 = *(comp_same+tmp_id); 
		}

		//check if area id already identified as real id
		found = 0;
		for(l=0;l<real_ids_size;l++){
			if( *(real_ids+l) == tmp_id ){
				found = 1;
				break;
			}
		}
		if( !found ){
			*(real_ids+real_ids_size) = tmp_id;
			*(real_ids_inv+tmp_id) = real_ids_size;//inverse function
			real_ids_size++;
		}
	}


/*
 * Generate tree structure
 */

	/* store for real_ids the index of the node in the tree array */
  int *tree_id_relation = malloc( (real_ids_size+1)*sizeof(int) );

  Node *tree = malloc( (real_ids_size+1)*sizeof(Node) );
	//init all node as leafs
	for(l=0;l<real_ids_size+1;l++) *(tree+l)=Leaf;

	Node *root = tree;
	Node *cur  = tree;
	int anchor, parent_id;
	int end = w*h;
	root->data.id = -1;
	MyBlobRect *rect;

	for(l=0;l<real_ids_size;l++){
		cur++;
		rect = &cur->data.roi;
		//cur->data.id = l+1;//*(real_ids+l);	//Set id of this blob. It's the index in the tree array.
		cur->data.id = *(real_ids+l);	//Set id of this blob.
//not useful?!
		anchor = *(anchors+*(real_ids+l)); //get anchor of this blob
#ifdef BLOB_DIMENSION
		rect->y = anchor/w + roi.y;
		rect->height = *(bottom_index + *(real_ids+l)) - rect->y + 1;
		rect->x = *(left_index + *(real_ids+l));
		rect->width = *(right_index + *(real_ids+l)) - rect->x + 1;
		printf("MyBlobRect of %i: x=%i y=%i w=%i h=%i\n",cur->data.id,
				rect->x, rect->y,
				rect->width, rect->height);
#endif
		/* check, if border element */
	/*	if( anchor<w || anchor+w>end || anchor%w==0 || anchor%w==w-1 ) //no, this do not work.*/
		/* check, if top element */
		//if( anchor<w ) 
		if( anchor<roi.width ){ 
		//if( anchor<roi.width || anchor%w==roi.x ) 
			/* Use root as parent node. */
			//cur->parent = root;
			add_child(root, cur );
		}else{
		/* search area/blob in left and top direction. It's the parent.*/
			tmp_id = *(ids+anchor-w);//parent id
			//find real id of parent id.
			tmp_id2 = *(comp_same+tmp_id); 
			while( tmp_id != tmp_id2 ){
				tmp_id = tmp_id2; 
				tmp_id2 = *(comp_same+tmp_id); 
			} 
			/*Now, tmp_id is in real_id array. And real_ids_inv is defined. */
			//cur->parent = root + 1/*root pos shift*/ + *(real_ids_inv+tmp_id );
			add_child( root + 1/*root pos shift*/ + *(real_ids_inv+tmp_id ),
					cur );
		}

	}

	//sum up node areas
	sum_areas(root->child, comp_size);

	sort_tree(root->child);

	//clean up
	free(tree_id_relation);
	//free(tree);
	free(real_ids);
	free(real_ids_inv);
	free(comp_same);
	free(comp_size);
	free(anchors);
	free(ids);
	free(left_index);
	free(right_index);
	free(bottom_index);

	//set output parameter
	*tree_size = real_ids_size+1;
	return tree;
}


//+++++++++++++++++++++++++++++
// Myblob functions
//+++++++++++++++++++++++++++++

Myblob *myblob_create(){
	Myblob *blob = malloc(sizeof(Myblob) );
	blob->tree = NULL;
	blob->tree_size = 0;
	Filter filter = {0,INT_MAX,0,INT_MAX};
	blob->filter = filter;
	return blob;
}

void myblob_destroy(Myblob *blob){
	if( blob->tree != NULL ){
		free(blob->tree);
		blob->tree = NULL;
		blob->tree_size = 0;
	}
	free(blob);
}

void myblob_set_filter(Myblob *blob, const FILTER f, const int val){
	switch(f){
		case F_DEPTH_MIN: blob->filter.min_depth=val;
											break;
		case F_DEPTH_MAX: blob->filter.max_depth=val;
											break;
		case F_AREA_MIN: blob->filter.min_area=val;
											break;
		case F_AREA_MAX: blob->filter.max_area=val;
											break;
	}
}

void myblob_find_blobs(Myblob *blob, const unsigned char *data, const int w, const int h, const MyBlobRect roi, const unsigned char thresh){
	//clear old tree
	if( blob->tree != NULL){
		free(blob->tree);
		blob->tree = NULL;
		blob->tree_size = 0;
	}
	//get new blob tree structure.
	blob->tree = find_connection_components_with_roi( data, w, h, roi, thresh, &blob->tree_size);
}

Node *myblob_first( Myblob *blob){
	blob->it = blob->tree;
	blob->it_depth = -1;
	return myblob_next(blob);
}

Node *myblob_next(Myblob *blob){
	//go to next element
	if( blob->it->child != NULL){
		blob->it = blob->it->child;
		blob->it_depth++;
	}else	if( blob->it->silbing != NULL ){
		blob->it = blob->it->silbing;
	}else{
		blob->it = blob->it->parent;
		blob->it_depth--;
	}

	//check criteria/filters.
	do{
		if( blob->it_depth < blob->filter.min_depth 
				|| blob->it->data.area > blob->filter.max_area ){
			if( blob->it->child != NULL){
				blob->it = blob->it->child;
				blob->it_depth++;
				continue;
			}
			if( blob->it->silbing != NULL ){
				blob->it = blob->it->silbing;
				continue;
			}
			blob->it = blob->it->parent;
			blob->it_depth--;
			continue;
		}
		if( blob->it_depth > blob->filter.max_depth ){
			blob->it = blob->it->parent;
			blob->it_depth--;
			continue;
		}
		if( blob->it->data.area < blob->filter.min_depth ){
			if( blob->it->silbing != NULL ){
				blob->it = blob->it->silbing;
				continue;
			}
			blob->it = blob->it->parent;
			blob->it_depth--;
			continue;
		}
		// All filters ok. Return node
		return blob->it;

	}while( blob->it != blob->tree );

	return NULL;
}

#endif

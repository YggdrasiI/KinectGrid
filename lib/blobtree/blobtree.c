#ifndef BLOBTREE_C
#define BLOBTREE_C

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h> //for memset

#include "blobtree.h"

#include "blobtree_macros.h"

char * debug_getline(void) {
    char * line = malloc(100), * linep = line;
    size_t lenmax = 100, len = lenmax;
    int c;

    if(line == NULL)
        return NULL;

    for(;;) {
        c = fgetc(stdin);
        if(c == EOF)
            break;

        if(--len == 0) {
            char * linen = realloc(linep, lenmax *= 2);
            len = lenmax;

            if(linen == NULL) {
                free(linep);
                return NULL;
            }
            line = linen + (line - linep);
            linep = linen;
        }

        if((*line++ = c) == '\n')
            break;
    }
    *line = '\0';
free(linep);
    return linep;
}

static void debug_print_matrix( int* data, int w, int h, BlobtreeRect roi, int gridw, int gridh){
	int i,j, wr, hr, w2, h2;
	int d;
	wr = (roi.width-1) % gridw;
	hr = (roi.height-1) % gridh;
	w2 = roi.width - wr;
	h2 = roi.height - hr;
	for(i=roi.y;i<roi.y+h2;i+=gridh){
		for(j=roi.x;j<roi.x+w2;j+=gridw){
			d = *(data+i*w+j);
			//printf("%i ",d);
			//printf("%s", d==0?"■⬛":"□");
			//printf("%s", d==0?"✘":" ");
			if(d>-1)
				printf("%s%i",d<10&&d>=0?" ":"", d);
			else
				printf("  ");
		}
		j-=gridw-wr;

		if(w2<roi.width){
			for(;j<roi.x+roi.width;j+=1){
				d = *(data+i*w+j);
				if(d>-1)
					printf("%s%i",d<10&&d>=0?" ":"", d);
				else
					printf("  ");
			}
		}
		
		printf("\n");
	}

	i-=gridh-hr;
	if( h2 < roi.height ){
		for( ;i<roi.y+roi.height;i+=1){
			for(j=roi.x;j<roi.x+w2;j+=gridw){
				d = *(data+i*w+j);
				if(d>-1)
					printf("%s%i",d<10&&d>=0?" ":"", d);
				else
					printf("  ");
			}
			j-=gridw-wr;

			if(w2<roi.width){
				for(;j<roi.x+roi.width;j+=1){
					d = *(data+i*w+j);
					if(d>-1)
						printf("%s%i",d<10&&d>=0?" ":"", d);
					else
						printf("  ");
				}
			}
			printf("\n");
		}
	}
	printf("\n");
}
static void debug_print_matrix2(int* ids, int* data, int w, int h, BlobtreeRect roi, int gridw, int gridh){
	int i,j, wr, hr, w2, h2;
	int d;
	wr = (roi.width-1) % gridw;
	hr = (roi.height-1) % gridh;
	w2 = roi.width - wr;
	h2 = roi.height - hr;
	for(i=roi.y;i<roi.y+h2;i+=gridh){
		for(j=roi.x;j<roi.x+w2;j+=gridw){
			if( *(ids+i*w+j) > -1 ){
				d = *(data+*(ids+i*w+j));
				printf("%s%i",d<10&&d>=0?" ":"", d);
			}else{
				printf("  ");
			}
		}
		j-=gridw-wr;

		if(w2<roi.width){
			for(;j<roi.x+roi.width;j+=1){
				if( *(ids+i*w+j) > -1 ){
					d = *(data+*(ids+i*w+j));
					printf("%s%i",d<10&&d>=0?" ":"", d);
				}else{
					printf("  ");
				}
			}
		}
		
		printf("\n");
	}

	i-=gridh-hr;
	if( h2 < roi.height ){
		for( ;i<roi.y+roi.height;i+=1){
			for(j=roi.x;j<roi.x+w2;j+=gridw){
				if( *(ids+i*w+j) > -1 ){
					d = *(data+*(ids+i*w+j));
					printf("%s%i",d<10&&d>=0?" ":"", d);
				}else{
					printf("  ");
				}
			}
			j-=gridw-wr;

			if(w2<roi.width){
				for(;j<roi.x+roi.width;j+=1){
					if( *(ids+i*w+j) > -1 ){
						d = *(data+*(ids+i*w+j));
						printf("%s%i",d<10&&d>=0?" ":"", d);
					}else{
						printf("  ");
					}
				}
			}
			printf("\n");
		}
	}
	printf("\n");
}

#ifdef BLOB_COUNT_PIXEL
static int sum_areas(const Node *root, const int *comp_size){
	int *val=&root->data.area;
	*val = *(comp_size + root->data.id );
	if( root->child != NULL) *val += sum_areas(root->child,comp_size);
	if( root->silbing != NULL) return *val+sum_areas(root->silbing, comp_size);
	else return *val;
}
#endif

#ifdef BLOB_DIMENSION
/* Todo: Remove recursion. */
static void set_area_prop(Node *root){
	root->data.area = root->data.roi.width * root->data.roi.height;
	if( root->child != NULL) set_area_prop(root->child);
	if( root->silbing != NULL) set_area_prop(root->silbing);
}
#endif

static Node* find_connection_components(
		const unsigned char *data,
		const int w, const int h,
		const unsigned char thresh,
		int* tree_size )
{
	const BlobtreeRect roi = {0,0,w,h};
	return find_connection_components_coarse(data,w,h,roi,thresh,1,1,tree_size);
}

 
static Node* find_connection_components_roi(
		const unsigned char *data,
		const int w, const int h,
		const BlobtreeRect roi,
		const unsigned char thresh,
		int* tree_size )
{
	return find_connection_components_coarse(data,w,h,roi,thresh,1,1,tree_size);
}

/* now include the old algo without subchecks ( find_connection_components_coarse ) */
#include "blobtree_old.c"


#ifdef BLOB_SUBGRID_CHECK 
#define STEPHEIGHT stepwidth
static Node* find_connection_components_subcheck(
		const unsigned char *data,
		const int w, const int h,
		const BlobtreeRect roi,
		const unsigned char thresh,
		const int stepwidth,
		int* tree_size )
{
/* With region of interrest (roi)
 * and fixed stepwidth.
 * A - stepwidth - B
 * |               |
 * |           stepwidth
 * |               |
 * C ------------- D
 * */
/* Marks of ι Cases:
 *  x - stepwidth, y - stepwidth, swr - (w-1)%x, shr - (h-1)%y
 * <----------------------- w --------------------------------->
 * |        <-- roi.width -------------->
 * |        <- roi.width-stepwidth-swr -->
 * | 
 * | | |    A ←x→ B ←x→ … B ←x→ C ←swr+stepwidth→ C
 * | | roi  ↑                   ↑                 ↑
 * h | hei  y                   y                 y
 * | r ght  ↓                   ↓                 ↓
 * | o -    E ←x→ F ←x→ … F ←x→ G ←swr+stepwidth→ H
 * | i ste  ↑                   ↑                 ↑
 * | . pwi  y                   y                 y
 * | h dth  ↓                   ↓                 ↓
 * | e -    E ←x→ F ←x→ … F ←x→ G ←swr+stepwidth→ H
 * | i shr  …                   …                 …
 * | g |    E ←x→ F ←x→ … F ←x→ G ←swr+stepwidth→ H
 * | h      ↑                   ↑                 ↑
 * | t     	1                   1                 1
 * | |      ↓                   ↓                 ↓
 * h |      L ←x→ M ←x→ … M ←x→ N ←swr+stepwidth→ P
 * | |      ↑                   ↑                 ↑
 * | |     	1                   1                 1
 * | |      ↓                   ↓                 ↓
 * h |      L ←x→ M ←x→ … M ←x→ N ←swr+stepwidth→ P
 * |  
 * |  
 * | 
 *
 */
	if( stepwidth < 2){
		return find_connection_components_coarse(data,w,h,roi,thresh,1,1,tree_size);
	}

	//init
	int r=w-roi.x-roi.width; //right border
  int b=h-roi.y-roi.height; //bottom border
	if( r<0 || b<0 ){
		fprintf(stderr,"[blob.c] BlobtreeRect not matching.\n");
		*tree_size = 0;
		return NULL;
	}

	int swr = (roi.width-1)%stepwidth; // remainder of width/stepwidth;
	int shr = (roi.height-1)%STEPHEIGHT; // remainder of height/stepheight;
	int sh = STEPHEIGHT*w;
	int sh1 = (STEPHEIGHT-1)*w;
	int sh2 = shr*w;

	int id=-1;//id for next component
	int a1,a2; // for comparation of g(f(x))=a1,a2=g(f(y)) 
	int k; //loop variable
	int max_comp = w+h;//maximal number of components. If the value is reached some arrays will reallocate.

	int* ids = malloc( w*h*sizeof(int) ); // store ids: f(A(i,j)) = id
//	int* anchors = malloc( max_comp*sizeof(int) ); //store positions of first elements with id.
#ifdef BLOB_COUNT_PIXEL
	int* comp_size = malloc( max_comp*sizeof(int) ); //store the size of each component. 
#endif
	int* comp_same = malloc( max_comp*sizeof(int) ); //map ids to unique ids g:{0,...,}->{0,....}

	int* prob_parent = malloc( max_comp*sizeof(int) ); //store id of left (or top in some cases!) element. Required to find parent and generate tree structure.

#ifdef BLOB_DIMENSION
	int* top_index = malloc( max_comp*sizeof(int) ); //save row number of most top element of area.
	int* left_index = malloc( max_comp*sizeof(int) ); //save column number of most left element of area.
	int* right_index = malloc( max_comp*sizeof(int) ); //save column number of most right element.
	int* bottom_index = malloc( max_comp*sizeof(int) ); //save row number of most bottom element.
	int s=roi.x,z=roi.y; //s-spalte, z-zeile
#else
	const int s=-1,z=-1; //Should not be used.
#endif

	//unsigned int triangle = 0; //1 =halve of next quad already done. 
	const int triwidth = (roi.width-1)/stepwidth ;
	unsigned char* const triangle = malloc(
			(triwidth+1)* ( (roi.height-1)/STEPHEIGHT + 1)
			* sizeof(unsigned char) );
	// set values to 0 for toprow
	memset(triangle, 0, triwidth*sizeof(char) );
	unsigned char* tri = triangle + triwidth;
#if VERBOSE > 0
	printf("triwidth: %i\n", triwidth);
#endif

	const unsigned char* dS = data+w*roi.y+roi.x;
	unsigned char* dR = dS+roi.width; //Pointer to right border. Update on every line
	//unsigned char* dR2 = swr>0?dR-swr-stepwidth-stepwidth:dR; //cut last indizies.
	unsigned char* dR2 = dR-swr-stepwidth; //cut last indizies.

	const unsigned char* dE = dR + (roi.height-1)*w;
	const unsigned char* dE2 = dE - shr*w;//remove last lines.

//int i = w*roi.y+roi.x;
	unsigned char* dPi = dS; // Pointer to data+i 
	int* iPi = ids+(dS-data); // Poiner to ids+i

#if VERBOSE > 0
//debug: prefill array
	memset(ids,-1, w*h*sizeof(int));
#endif

	/**** A,A'-CASE *****/
	//top, left corner of BlobtreeRect get first id.
	NEW_COMPONENT(-1);
	iPi += stepwidth;
	dPi += stepwidth;

#ifdef BLOB_DIMENSION
	s += stepwidth;
#endif

	/* Split all logic to two subcases:
	 * *(dPi)<=thresh (marked as B,C,…),
	 * *(dPi)>thresh (marked as B',C',…)
	 * to avoid many 'x&&y || x|y==0' checks.
	 * */

	//top border
	for(;dPi<dR2;iPi += stepwidth,dPi += stepwidth){
		if( *(dPi) > thresh ){
			/**** B-CASE *****/
			if( *(dPi-stepwidth) > thresh ){//same component as left neighbour
				LEFT_CHECK(stepwidth)
			}else{//new component
				SUBCHECK_ROW(dPi,iPi,stepwidth,w,sh,s,z,0);
			}
		}else{
			/**** B'-CASE *****/
			if( *(dPi-stepwidth) <= thresh ){//same component as left neighbour
				LEFT_CHECK(stepwidth)
			}else{//new component
				SUBCHECK_ROW(dPi,iPi,stepwidth,w,sh,s,z,0);
			}
		}
#ifdef BLOB_DIMENSION
		s += stepwidth;
#endif
	}

	//now process last, bigger, cell.
	//SUBCHECK_ROW(dPi,iPi,stepwidth,w,sh,s,z,swr);
	SUBCHECK_ROW(dPi,iPi,stepwidth,w,sh,s,z,swr);
	/* Pointer is stepwidth+swr+1 behind currrent element.
	 * Move pointer to 'next' row.*/
	dPi += r+roi.x+sh1;
	iPi += r+roi.x+sh1;

	dR += sh; // Move right border to next row.
	dR2 += sh;
#ifdef BLOB_DIMENSION
	s=roi.x;
	z += STEPHEIGHT;
#endif	

	//2nd,...,(h-shr)-row
	for( ; dPi<dE2 ; ){

#if VERBOSE > 1
		debug_print_matrix( ids, w, h, roi, 1, 1);
		printf("Z:%i, S:%i, I:%i %i, tri: %i\n",z,s,dPi-dS, iPi-ids-(dS-data), (tri-triangle) );
		debug_getline();
#endif

		//left border
		if( *(dPi) > thresh ){
			/**** E-CASE *****/
			if( *(dPi-sh) > thresh ){//same component as top neighbour
				TOP_CHECK(STEPHEIGHT, sh);
				*(tri) = 0;
			}else{
				SUBCHECK_PART2b(dPi,iPi,stepwidth,w,sh,s,z);
				*(tri) = 2;
			}
		}else{
			/**** E'-CASE *****/
			if( *(dPi-sh) <= thresh ){//same component as top neighbour
				TOP_CHECK(STEPHEIGHT, sh);
				*(tri) = 0;
			}else{
				SUBCHECK_PART2b(dPi,iPi,stepwidth,w,sh,s,z);
				*(tri) = 2;
			}
		}

		iPi += stepwidth;
		dPi += stepwidth;
#ifdef BLOB_DIMENSION
		s += stepwidth;
#endif
		++tri;

		/*inner elements till last colum before dR2 reached.
		 * => Lefthand tests with -stepwidth
		 * 		Righthand tests with +stepwidth
		 */
		for( ; dPi<dR2; ){

			/* Bit order: 
			 * 0 2 3
			 * 1 
			 */
			/*const*/ unsigned char casenbr = ( *(dPi) > thresh )? \
				( (( *(dPi-sh+stepwidth) <= thresh ) << 3)
				| (( *(dPi-sh) <= thresh ) << 2)
				| (( *(dPi-stepwidth) <= thresh ) << 1)
				| (( *(dPi-sh-stepwidth) <= thresh ) << 0)): \
				(	(( *(dPi-sh+stepwidth) > thresh ) << 3)
				| (( *(dPi-sh) > thresh ) << 2)
				| (( *(dPi-stepwidth) > thresh ) << 1)
				| (( *(dPi-sh-stepwidth) > thresh ) << 0));

#if VERBOSE > 1
		debug_print_matrix( ids, w, h, roi, 1, 1);
		printf("F, casenbr: %i, *tri: %i %i %i\n",casenbr, *(tri-1), *(tri-1-triwidth), *(tri-triwidth));
		debug_getline();
#endif
			if( dPi+stepwidth>=dR2 ){
				//set bit do avoid PART1c/PART1d calls for this column.
				//Could be unrolled...
				casenbr = casenbr | 0x08;
			}
			if( dPi+sh>=dE2 ){
				//set bit do force PART4 calls for this row.
				casenbr = casenbr | 0x02;
			}

			if( *(tri-1) > 1 ){
				switch( casenbr) {
					case 0:
					case 8: {
										TOP_CHECK(STEPHEIGHT, sh);
										TOP_LEFT_COMP(stepwidth);
										*(tri) = 1; //tri filled, quad not.
										break;
									}
					case 1:{
									 SUBCHECK_PART1cd(dPi,iPi,stepwidth,w,sh,s,z);
									 SUBCHECK_PART3b(dPi,iPi,stepwidth,w,sh,s,z);
										*(tri) = 2;
									 SUBCHECK_PART4b(dPi,iPi,stepwidth,w,sh,s,z);
									 break;
								 }
					case 2:{
									 SUBCHECK_PART1cd(dPi,iPi,stepwidth,w,sh,s,z);
									 SUBCHECK_PART3b(dPi,iPi,stepwidth,w,sh,s,z);
									 *(tri) = 2;
									 SUBCHECK_PART4a(dPi,iPi,stepwidth,w,sh,s,z);
									 break;
								 }
					case 3:{
									 SUBCHECK_PART1cd(dPi,iPi,stepwidth,w,sh,s,z);
									 SUBCHECK_PART3b(dPi,iPi,stepwidth,w,sh,s,z);
									 *(tri) = 2;
									 SUBCHECK_PART4a(dPi,iPi,stepwidth,w,sh,s,z);
									 break;
								 }
					case 4:{
									 SUBCHECK_PART3b(dPi,iPi,stepwidth,w,sh,s,z);
									 *(tri) = 2;
									 SUBCHECK_PART4b(dPi,iPi,stepwidth,w,sh,s,z);
									 break;
								 }
					case 5:{
									 SUBCHECK_PART3b(dPi,iPi,stepwidth,w,sh,s,z);
									 *(tri) = 2;
									 SUBCHECK_PART4b(dPi,iPi,stepwidth,w,sh,s,z);
									 break;
								 }
					case 6:{
									 SUBCHECK_PART3b(dPi,iPi,stepwidth,w,sh,s,z);
									 *(tri) = 2;
									 SUBCHECK_PART4a(dPi,iPi,stepwidth,w,sh,s,z);
									 break;
								 }
					case 7:{
									 SUBCHECK_PART3b(dPi,iPi,stepwidth,w,sh,s,z);
									 *(tri) = 2;
									 SUBCHECK_PART4a(dPi,iPi,stepwidth,w,sh,s,z);
									 break;
								 }
					case 9:{
									 SUBCHECK_PART3b(dPi,iPi,stepwidth,w,sh,s,z);
									 *(tri) = 2;
									 SUBCHECK_PART4b(dPi,iPi,stepwidth,w,sh,s,z);
									 break;
								 }
					case 10:{
										SUBCHECK_PART3b(dPi,iPi,stepwidth,w,sh,s,z);
										*(tri) = 2;
										SUBCHECK_PART4a(dPi,iPi,stepwidth,w,sh,s,z);
										break;
									}
					case 11:{
										SUBCHECK_PART3b(dPi,iPi,stepwidth,w,sh,s,z);
										*(tri) = 2;
										SUBCHECK_PART4a(dPi,iPi,stepwidth,w,sh,s,z);
										break;
									}
					case 12:{
										SUBCHECK_PART1cd(dPi,iPi,stepwidth,w,sh,s,z);
										SUBCHECK_PART3b(dPi,iPi,stepwidth,w,sh,s,z);
										*(tri) = 2;
										SUBCHECK_PART4b(dPi,iPi,stepwidth,w,sh,s,z);
										break;
									}
					case 13:{
										SUBCHECK_PART1cd(dPi,iPi,stepwidth,w,sh,s,z);
										SUBCHECK_PART3b(dPi,iPi,stepwidth,w,sh,s,z);
										*(tri) = 2;
										SUBCHECK_PART4b(dPi,iPi,stepwidth,w,sh,s,z);
										break;
									}
					case 14:{
										SUBCHECK_PART1cd(dPi,iPi,stepwidth,w,sh,s,z);
										SUBCHECK_PART3b(dPi,iPi,stepwidth,w,sh,s,z);
										*(tri) = 2;
										SUBCHECK_PART4a(dPi,iPi,stepwidth,w,sh,s,z);
										break;
									}
					case 15:{
										SUBCHECK_PART1cd(dPi,iPi,stepwidth,w,sh,s,z);
										SUBCHECK_PART3b(dPi,iPi,stepwidth,w,sh,s,z);
										*(tri) = 2;
										SUBCHECK_PART4a(dPi,iPi,stepwidth,w,sh,s,z);
										break;
									}
				}
			}else{
				switch( casenbr ){
					case 0:
					case 8: {
										TOP_CHECK(STEPHEIGHT, sh);
										TOP_LEFT_COMP(stepwidth);
										*(tri) = 0;
										break;
									}
					case 1:{
									 SUBCHECK_PART1cd(dPi,iPi,stepwidth,w,sh,s,z);
									 SUBCHECK_PART3a(dPi,iPi,stepwidth,w,sh,s,z);
									 *(tri) = 2;
									 SUBCHECK_PART4b(dPi,iPi,stepwidth,w,sh,s,z);
									 break;
								 }
					case 2:{
									 SUBCHECK_PART1ab(dPi,iPi,stepwidth,w,sh,s,z);
									 SUBCHECK_PART1cd(dPi,iPi,stepwidth,w,sh,s,z);
									 SUBCHECK_PART3a(dPi,iPi,stepwidth,w,sh,s,z);
									 *(tri) = 2;
									 SUBCHECK_PART4a(dPi,iPi,stepwidth,w,sh,s,z);
									 break;
								 }
					case 3:{
									 SUBCHECK_PART1cd(dPi,iPi,stepwidth,w,sh,s,z);
									 SUBCHECK_PART3a(dPi,iPi,stepwidth,w,sh,s,z);
									 *(tri) = 2;
									 SUBCHECK_PART4a(dPi,iPi,stepwidth,w,sh,s,z);
									 break;
								 }
					case 4:{
									 SUBCHECK_PART3a(dPi,iPi,stepwidth,w,sh,s,z);
									 *(tri) = 2;
									 SUBCHECK_PART4b(dPi,iPi,stepwidth,w,sh,s,z);
									 break;
								 }
					case 5:{
									 SUBCHECK_PART1ab(dPi,iPi,stepwidth,w,sh,s,z);
									 SUBCHECK_PART3a(dPi,iPi,stepwidth,w,sh,s,z);
									 *(tri) = 2;
									 SUBCHECK_PART4b(dPi,iPi,stepwidth,w,sh,s,z);
									 break;
								 }
					case 6:{
									 SUBCHECK_PART3a(dPi,iPi,stepwidth,w,sh,s,z);
									 *(tri) = 2;
									 SUBCHECK_PART4a(dPi,iPi,stepwidth,w,sh,s,z);
									 break;
								 }
					case 7:{
									 SUBCHECK_PART1ab(dPi,iPi,stepwidth,w,sh,s,z);
									 SUBCHECK_PART3a(dPi,iPi,stepwidth,w,sh,s,z);
									 *(tri) = 2;
									 SUBCHECK_PART4a(dPi,iPi,stepwidth,w,sh,s,z);
									 break;
								 }
					case 9:{
									 SUBCHECK_PART3a(dPi,iPi,stepwidth,w,sh,s,z);
									 *(tri) = 2;
									 SUBCHECK_PART4b(dPi,iPi,stepwidth,w,sh,s,z);
									 break;
								 }
					case 10:{
										SUBCHECK_PART1ab(dPi,iPi,stepwidth,w,sh,s,z);
										SUBCHECK_PART3a(dPi,iPi,stepwidth,w,sh,s,z);
										*(tri) = 2;
										SUBCHECK_PART4a(dPi,iPi,stepwidth,w,sh,s,z);
										break;
									}
					case 11:{
										SUBCHECK_PART3a(dPi,iPi,stepwidth,w,sh,s,z);
										*(tri) = 2;
										SUBCHECK_PART4a(dPi,iPi,stepwidth,w,sh,s,z);
										break;
									}
					case 12:{
										SUBCHECK_PART1cd(dPi,iPi,stepwidth,w,sh,s,z);
										SUBCHECK_PART3a(dPi,iPi,stepwidth,w,sh,s,z);
										*(tri) = 2;
										SUBCHECK_PART4b(dPi,iPi,stepwidth,w,sh,s,z);
										break;
									}
					case 13:{
										SUBCHECK_PART1ab(dPi,iPi,stepwidth,w,sh,s,z);
										SUBCHECK_PART1cd(dPi,iPi,stepwidth,w,sh,s,z);
										SUBCHECK_PART3a(dPi,iPi,stepwidth,w,sh,s,z);
										*(tri) = 2;
										SUBCHECK_PART4b(dPi,iPi,stepwidth,w,sh,s,z);
										break;
									}
					case 14:{
										SUBCHECK_PART1cd(dPi,iPi,stepwidth,w,sh,s,z);
										SUBCHECK_PART3a(dPi,iPi,stepwidth,w,sh,s,z);
										*(tri) = 2;
										SUBCHECK_PART4a(dPi,iPi,stepwidth,w,sh,s,z);
										break;
									}
					case 15:{
										SUBCHECK_PART1ab(dPi,iPi,stepwidth,w,sh,s,z);
										SUBCHECK_PART1cd(dPi,iPi,stepwidth,w,sh,s,z);
										SUBCHECK_PART3a(dPi,iPi,stepwidth,w,sh,s,z);
										*(tri) = 2;
										SUBCHECK_PART4a(dPi,iPi,stepwidth,w,sh,s,z);
										break;
									}
				}

			}


			dPi += stepwidth;
			iPi += stepwidth;
#ifdef BLOB_DIMENSION
			s += stepwidth;
#endif
			++tri;
		}

#if VERBOSE > 2 
		debug_print_matrix( ids, w, h, roi, 1, 1);
		printf("G *tri: %i %i %i\n", *(tri-1), *(tri-1-triwidth), *(tri-triwidth));
		debug_getline();
#endif

		/* now process last, bigger, cell.
		 * There exists only two cases:
		 * triangle=0 or triangle=1. Top border was always evaluated
		 * and bottom border should evaluated, too.
		 */

		if( *(tri-1) > 1 ){
			SUBCHECK_PART6b(dPi,iPi,stepwidth,w,sh,s,z,swr); 
		}else{
			SUBCHECK_PART6a(dPi,iPi,stepwidth,w,sh,s,z,swr); 
		}
		*(tri) = 2;

		/* Pointer is still on currrent element.
		 * Move pointer to 'next' row.*/
		dPi += r+roi.x+sh1+swr+1; 
		iPi += r+roi.x+sh1+swr+1;
		dR += sh; // Move border indizes to next row.
		dR2 += sh;
#ifdef BLOB_DIMENSION
		s=roi.x;
		z += STEPHEIGHT;
#endif	
		++tri;

#if VERBOSE > 2 
		debug_print_matrix( ids, w, h, roi, 1, 1);
		printf("Z:%i, S:%i, I:%i %i\n",z,s,dPi-dS, iPi-ids-(dS-data) );
		debug_getline();
#endif

	} //row loop

	//correct pointer of last for loop step
	iPi -= sh1;
	dPi -= sh1;
	dR -= sh1;
	dR2 -= sh1;
#ifdef BLOB_DIMENSION
	z -= STEPHEIGHT-1;
#endif

#if VERBOSE > 1
		debug_print_matrix( ids, w, h, roi, 1, 1);
		printf("Z:%i, S:%i, I:%i %i\n",z,s,dPi-dS, iPi-ids-(dS-data) );
		debug_getline();
#endif

	if( dE2 != dE ){
		//Process elementwise till end of ROI reached.
		for( ; dPi<dE ; ){
			SUBCHECK_TOPDIAG(dPi,iPi,stepwidth,w,sh,s,z);
			++dPi; ++iPi;
#ifdef BLOB_DIMENSION
			++s;
#endif
			for( ; dPi<dR-1 ; ){
				SUBCHECK_ALLDIR(dPi,iPi,stepwidth,w,sh,s,z);
				++dPi; ++iPi;
#ifdef BLOB_DIMENSION
				++s;
#endif
			}
			//right border
			SUBCHECK_TOPLEFT(dPi,iPi,stepwidth,w,sh,s,z);
			//move pointer to 'next' row
			dPi += r+roi.x+1; 
			iPi += r+roi.x+1;
#ifdef BLOB_DIMENSION
			s = roi.x;
			++z;
#endif
			dR += w;
			//dR2 += w; //not ness.
			
#if VERBOSE > 1
			debug_print_matrix( ids, w, h, roi, 1, 1);
			printf("Z:%i, S:%i, I:%i %i\n",z,s,dPi-dS, iPi-ids-(dS-data) );
			debug_getline();
#endif
		}
	}//end of if(dE2<dE)



/* end of main algo */

#if VERBOSE > 0 
//printf("Matrix of ids:\n");
//print_matrix(ids,w,h);

//printf("comp_same:\n");
//print_matrix(comp_same, id+1, 1);
debug_print_matrix( ids, w, h, roi, 1, 1);
debug_print_matrix2( ids, comp_same, w, h, roi, 1, 1);
if( stepwidth*STEPHEIGHT >1 ){
	debug_print_matrix( ids, w, h, roi, stepwidth, STEPHEIGHT);
	//printf("\n\n");
	debug_print_matrix2( ids, comp_same, w, h, roi, stepwidth, STEPHEIGHT);
}
#endif

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
#if VERBOSE > 1
printf("%i: (%i->%i) ",k,tmp_id,tmp_id2);
#endif
		while( tmp_id2 != tmp_id ){
#ifdef BLOB_COUNT_PIXEL
			//move area size to other id.
			*(comp_size+tmp_id2) += *(comp_size+tmp_id); 
			*(comp_size+tmp_id) = 0;
#endif
			tmp_id = tmp_id2; 
			tmp_id2 = *(comp_same+tmp_id); 
#if VERBOSE > 1
printf("(%i->%i) ",tmp_id,tmp_id2);
#endif
		}
#if VERBOSE > 1
printf("\n");
#endif

#ifdef BLOB_DIMENSION
			//update dimension
			if( *( top_index+tmp_id2 ) > *( top_index+k ) )
				*( top_index+tmp_id2 ) = *( top_index+k );
			if( *( left_index+tmp_id2 ) > *( left_index+k ) )
				*( left_index+tmp_id2 ) = *( left_index+k );
			if( *( right_index+tmp_id2 ) < *( right_index+k ) )
				*( right_index+tmp_id2 ) = *( right_index+k );
			if( *( bottom_index+tmp_id2 ) < *( bottom_index+k ) )
				*( bottom_index+tmp_id2 ) = *( bottom_index+k );
#endif

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
	int parent_id /*, anchor */;
	int end = w*h;
	root->data.id = -1;
	BlobtreeRect *rect;

	for(l=0;l<real_ids_size;l++){
		cur++;
		rect = &cur->data.roi;
		//cur->data.id = l+1;//*(real_ids+l);	//Set id of this blob. It's the index in the tree array.
		cur->data.id = *(real_ids+l);	//Set id of this blob.
//not useful?!
//		anchor = *(anchors+*(real_ids+l)); //get anchor of this blob
#ifdef BLOB_DIMENSION
		rect->y = *(top_index + *(real_ids+l));
		rect->height = *(bottom_index + *(real_ids+l)) - rect->y + 1;
		rect->x = *(left_index + *(real_ids+l));
		rect->width = *(right_index + *(real_ids+l)) - rect->x + 1;
#endif

		tmp_id = *(prob_parent+*(real_ids+l)); //get id of parent (or child) area. 
		if( tmp_id < 0 ){
			/* Use root as parent node. */
			//cur->parent = root;
			add_child(root, cur );
		}else{
		/* search area/blob in left direction. It's the parent.*/
			/* a- anchor, p - parent
			 * 0000
			 * 0000
			 * 0pa0
			 */
			//tmp_id = *(ids+anchor-1);//parent id

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

#ifdef BLOB_COUNT_PIXEL
	//sum up node areas
	sum_areas(root->child, comp_size);
#endif
#ifdef BLOB_DIMENSION
	if(stepwidth > 1){
		/* comp_size values not useable */
		set_area_prop(root->child);
	}
#endif

#ifdef BLOB_SORT_TREE
	//sort_tree(root->child);
	sort_tree(root);
#endif

	//clean up
	free(tree_id_relation);
	//free(tree);
	free(real_ids);
	free(real_ids_inv);
	free(comp_same);
	free(triangle);
#ifdef BLOB_COUNT_PIXEL
	free(comp_size);
#endif
//	free(anchors);
	free(prob_parent);
	free(ids);
#ifdef BLOB_DIMENSION
	free(top_index);
	free(left_index);
	free(right_index);
	free(bottom_index);
#endif

	//set output parameter
	*tree_size = real_ids_size+1;
	return tree;
}

#undef STEPHEIGHT
#endif


//+++++++++++++++++++++++++++++
// Blobtree functions
//+++++++++++++++++++++++++++++

Blobtree *blobtree_create(){
	Blobtree *blob = malloc(sizeof(Blobtree) );
	blob->tree = NULL;
	blob->tree_size = 0;
	Filter filter = {0,INT_MAX,0,INT_MAX};
	blob->filter = filter;
	Grid grid = {1,1};
	blob->grid = grid;
	return blob;
}

void blobtree_destroy(Blobtree *blob){
	if( blob->tree != NULL ){
		free(blob->tree);
		blob->tree = NULL;
		blob->tree_size = 0;
	}
	free(blob);
}

void blobtree_set_filter(Blobtree *blob, const FILTER f, const int val){
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

void blobtree_set_grid(Blobtree *blob, const int gridwidth, const int gridheight ){
	blob->grid.width = gridwidth;
	blob->grid.height =  gridheight;
}

void blobtree_find_blobs(Blobtree *blob, const unsigned char *data, const int w, const int h, const BlobtreeRect roi, const unsigned char thresh){
	//clear old tree
	if( blob->tree != NULL){
		free(blob->tree);
		blob->tree = NULL;
		blob->tree_size = 0;
	}
	//get new blob tree structure.
#ifdef BLOB_SUBGRID_CHECK
	blob->tree = find_connection_components_subcheck(
			data, w, h, roi, thresh,
			blob->grid.width,
			&blob->tree_size );
#else
	blob->tree = find_connection_components_coarse(
			data, w, h, roi, thresh,
			blob->grid.width, blob->grid.height,
			&blob->tree_size );
#endif
}

Node *blobtree_first( Blobtree *blob){
	blob->it = blob->tree;
	blob->it_depth = -1;
	return blobtree_next(blob);
}

/* This method throws an NULL pointer exception
 * if it's has return NULL and called again */
Node *blobtree_next(Blobtree *blob){
	//go to next element
	Node *it = blob->it; 
	int it_depth = blob->it_depth;

	if( it->child != NULL){
		it = it->child;
		it_depth++;
	}else	if( it->silbing != NULL ){
		it = it->silbing;
	}else{
		while( 1 ){
			it = it->parent;
			it_depth--;
			if(it->silbing != NULL){
				it = it->silbing;
				break;
			}
			if( it_depth < 0 ){
				blob->it = NULL;
				blob->it_depth=it_depth;
				return NULL;
			}
		}
	}

	//check criteria/filters.
	do{
		if( it_depth < blob->filter.min_depth 
				|| it->data.area > blob->filter.max_area ){
			if( it->child != NULL){
				it = it->child;
				it_depth++;
				continue;
			}
			if( it->silbing != NULL ){
				it = it->silbing;
				continue;
			}
			while( 1 ){
				it = it->parent;
				it_depth--;
				if(it->silbing != NULL){
					it = it->silbing;
					break;
				}
				if( it_depth < 0 ){
					blob->it = NULL;
					blob->it_depth = it_depth;
					return NULL;
				}
			}
			continue;
		}
		if( it_depth > blob->filter.max_depth ){
			while( 1 ){
				it = it->parent;
				it_depth--;
				if(it->silbing != NULL){
					it = it->silbing;
					break;
				}
				if( it_depth < 0 ){
					blob->it = NULL;
					blob->it_depth = it_depth;
					return NULL;
				}
			}
			continue;
		}
		if( it->data.area < blob->filter.min_area ){
			if( it->silbing != NULL ){
				it = it->silbing;
				continue;
			}
			while( 1 ){
				it = it->parent;
				it_depth--;
				if(it->silbing != NULL){
					it = it->silbing;
					break;
				}
				if( it_depth < 0 ){
					blob->it = NULL;
					blob->it_depth = it_depth;
					return NULL;
				}
			}
			continue;
		}
		// All filters ok. Return node
		blob->it = it;
		blob->it_depth = it_depth;
		return it;

	}while( it != blob->tree );

	//should never reached
	blob->it = NULL;
	blob->it_depth = -1;
	return NULL;
}

#endif

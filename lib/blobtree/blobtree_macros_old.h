
#define NEW_COMPONENT_OLD \
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



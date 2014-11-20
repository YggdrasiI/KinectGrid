/* ONLY RUDIMENTS and NEVER FINISHED */

/* This algorithm based on the blobtree algorithm and
 * allows the detection of subblobs.
 * This can be used to detect finger tips.
 *
 * Requires '#define BLOB_DIMENSION ' in blobtree.h
 *
 *
 *
 * */


typedef struct {
	//Node *childroot; //root of tree of children relation.
    size_t subblobs_length;
	Blobtree **subblobs ;// list of blobstructs
    Tree *childblobs;
    Tree *leafblobs;
} Subblobtree;


/* Was wird übergeben?!
 *
 * • Ein Node für den es angewendet werden soll
 * • Filter filterparameter, die sub-blobgröße nach unten einschränken.
 *
 * Was wird zurückgegeben:
 * • Eine Struktur mit folgenden Inhalten:
 * • Array mit den Thresholds für jede erstellte Ebene. Derzeit o.B.d.A einfach [T, T+1,....,254].
 * • Baum für jeden Threshold.
 * • Baum, der Kindrelation zwischen Baum(T) und Baum(T+1) abbildet.
 * • Baum, der Blattrelation abbildet. (sofern ich den on the fly erstellen kann.)
 * */

/* Es werden dann noch hilfsfunktionen benötigt, mit denen analog zu den Hilfsfunktionen von
 * Blobtree die Knoten durchlaufen werden können.
 * */

Subblobtree* subblobtree_create(){
    Subblobtree *sub = malloc( sizeof(Subblobtree*) );
    sub->subblobs_length = 0;
    sub->subblobs = NULL;
    sub->childblobs = NULL;
    sub->leafblobs = NULL;
    return sub;
}

void subblobtree_clear(Subblobtree *sub){
        int i=sub->subblobs_length;
        while( i-- ){
            blobtree_destroy( sub->subblobs[i] );
            sub->subblobs[i] = NULL; 
        }
        sub->subblobs_length = 0;
        tree_destroy( sub->childblobs );
        tree_destroy( sub->leafblobs );
}

void subblobtree_destroy(Subblobtree *sub){
    if( sub != NULL ){
        subblobtree_clear(sub);
        free(sub);
        sub = NULL;
    }
}

void subblobtree_eval( Subblobtree *sub,
		const unsigned char *data, 
		const int w, const int h,
        const Blobtree *blobs,
        const Blob *baseblob,
		//const BlobtreeRect subroi,
		const unsigned char startthresh  /* should be thresh of blobs. */
        ){

    BlobtreeRect *subroi = baseblob->roi;

    subblobtree_clear(sub);
    sub->subblobs_length = 255-1-startthresh;
    //this calloc call requires NULL == 0 (bitwise).
    calloc(sub->subblobs, NULL, sizeof(Blob*) * sub->subblobs_length);

    //Eval Blobs for each thresh>startthresh
    //Break, if no subblobs found.
    int i=0;
    unsigned char thresh = startthresh;
    for( ; i<sub->subblobs_length; i++ ){
        Blobtree *blob = blobtree_create();
        blobtree_set_grid(blob, 1,1);
        thresh++;

        blobtree_find_blobs(blob, sw, w, h, subroi, thresh);

        blobtree_set_filter(blob, F_DEPTH_MIN, 1);
        blobtree_set_filter(blob, F_AREA_MIN, 4);
        blobtree_set_filter(blob, F_DEPTH_MAX, 1);

        //check if tree is empty.
	    if( blobtree_first(blob) == NULL ) break;

        sub->subblobs[i] = blob; 
    }
    const unsigned char endthresh = thresh;//index behind the end...

    //Connect subblobs of the array list.

    Node *nodes = malloc( (real_ids_size+1)*sizeof(Node) );
    Tree *tree = malloc( sizeof(Tree) );
    tree->root = nodes;
    tree->size = real_ids_size + 1;

}

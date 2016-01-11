#ifndef _lcthw_sarray_h
#define _lcthw_sarray_h

typedef struct SuffixArray {
	char *source; 
	int length; 
	int *indices; 
} SuffixArray; 

SuffixArray *SuffixArray_create(char *data, int length); 

void SuffixArray_destroy(SuffixArray *sarray); 

int SuffixArray_find_suffix(SuffixArray *sarray, char *data, int length); 

#define SuffixArray_substr(S, I) ((S)->source + (S)->indices[I])

#endif
#ifndef _lcthw_graph_h
#define _lcthw_graph_h

#include <lcthw/darray.h> 

typedef struct Graph {
    int count; 
    DArray *nodes; 
} Graph; 

typedef struct GraphNode {
    void *value; 
    DArray *links; 
    int directed; // 0 if undirected
} GraphNode; 
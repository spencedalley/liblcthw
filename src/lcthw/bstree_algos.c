#include <lcthw/bstree.h> 
#include <lcthw/bstrlib.h> 
#include <lcthw/queue.h> 

BSTreeNode *BSTree_BFS(BSTree * map, void * val)
{
	Queue *q = Queue_create(); 
	BSTreeNode *node = NULL; 
	Queue_unshift(map->root); 

	do {
		node = Queue_pop(q); 
		if(node->data == val) {
			break; 
		} else if(node->left || node->right) {
			if (node->left) Queue_unshift(q, node->left); 
			if (node->right) Queue_unshift(q, node->right); 
		} else {
			node = NULL;  
		}
	} while(node); 

	// Free up memory 
	Queue_clear_destroy(q); 

	return node; 
}

BSTreeNode *BSTree_DFS(BSTreeNode *node, void *val)
{
	if(node->data == val) return node;

	if(node->left) {
		node = BSTree_DFS(node->left, val); 
		if (node != NULL) return node; 
	}
	if(node->right) {
		node = BSTree_DFS(node->right, val); 
		if(node != NULL) return node; 
	}

	return NULL; 
}

void BSTree_invert(BSTree *map)
{
	check(map != NULL, "Tree is NULL"); 

	BSTreeNode *node1, *node2; 
	void *tmp; 
	Queue *q = Queue_create(); 
	if(map->root->left) Queue_unshift(map->root->left); 
	if(map->root->right) Queue_unshift(map->root->right); 

	do {
		node1 = Queue_pop(q); 
		node2 = Queue_pop(q); 

		if(node1 != NULL && node2 != NULL) {
			tmp = node1->data; 
			node1->data = node2->data; 
			node2->data = tmp; 
		} 

	} while(node1 != NULL || node2 != NULL); 
}


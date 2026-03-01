#include <stdio.h>
#include <assert.h>
#include "graph.h"

typedef struct edge
{
    vertex_t start;
    vertex_t end;
}edge_t;

void test_dfs_traversal();
void test_bfs_traversal();

int main()
{
    graph_t* gr = NULL;

    vertex_t V[] = {1, 2, 3, 4, 5, 6};
    edge_t E[] = { {1, 2}, {1, 6}, {2, 6}, {2, 5}, {2, 3}, {3, 4}, {3, 6}, {3, 5}, {4, 5}, {5, 6} };

    int i;
    status_t status;

    gr = create_graph();
    for(i = 0; i < sizeof(V)/sizeof(vertex_t); ++i)
    {
        status = insert_vertex(gr, V[i]);
        assert(status == SUCCESS);
    }
    for(i = 0; i < sizeof(E)/sizeof(edge_t); ++i)
    {
        status = insert_edge(gr, E[i].start, E[i].end);
        assert(status == SUCCESS);
    }
    
    show_graph(gr, "Initial State");

 	status = remove_edge(gr, 2, 5); 
	assert(status == SUCCESS); 
	status = remove_edge(gr, 2, 3);
	assert(status == SUCCESS);
	status = remove_edge(gr, 6, 2);
	assert(status == SUCCESS);
	status = remove_edge(gr, 6, 5);
	assert(status == SUCCESS);
		
	show_graph(gr, "After removing edges, (2, 5), (2, 3), (6, 2), (6, 5):");    

	status = remove_vertex(gr, 3); 
	assert(status == SUCCESS); 

	show_graph(gr, "After removing vertex: 3"); 

	status = destroy_graph(&gr); 
	assert(status == SUCCESS && gr == NULL); 

    test_dfs_traversal();  

    test_bfs_traversal();

	return (0);     
}

void test_dfs_traversal()
{
 graph_t* gr = NULL;

    //vertex_t V[] = {1, 2, 3, 4, 5, 6};
    //edge_t E[] = { {1, 2}, {1, 6}, {2, 6}, {2, 5}, {2, 3}, {3, 4}, {3, 6}, {3, 5}, {4, 5}, {5, 6} };
    
    vertex_t V[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    edge_t E[] = {{1, 2}, {2, 3}, {3, 1}, {4, 5}, {6, 7}, {7, 8}, {8, 9}, {9, 6}};
    
    int i;
    status_t status;

    gr = create_graph();
    for(i = 0; i < sizeof(V)/sizeof(vertex_t); ++i)
    {
        status = insert_vertex(gr, V[i]);
        assert(status == SUCCESS);
    }
    for(i = 0; i < sizeof(E)/sizeof(edge_t); ++i)
    {
        status = insert_edge(gr, E[i].start, E[i].end);
        assert(status == SUCCESS);
    }

    show_graph(gr, "Initial State");
    dfs(gr);
}

void test_bfs_traversal()
{
    graph_t* gr = NULL;

    vertex_t V[] = {1, 2, 3, 4, 5, 6};
    edge_t E[] = { {1, 2}, {1, 6}, {2, 6}, {2, 5}, {2, 3}, {3, 4}, {3, 6}, {3, 5}, {4, 5}, {5, 6} };
    
    //vertex_t V[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    //edge_t E[] = {{1, 2}, {2, 3}, {3, 1}, {4, 5}, {6, 7}, {7, 8}, {8, 9}, {9, 6}};
    
    int i;
    status_t status;

    gr = create_graph();
    for(i = 0; i < sizeof(V)/sizeof(vertex_t); ++i)
    {
        status = insert_vertex(gr, V[i]);
        assert(status == SUCCESS);
    }
    for(i = 0; i < sizeof(E)/sizeof(edge_t); ++i)
    {
        status = insert_edge(gr, E[i].start, E[i].end);
        assert(status == SUCCESS);
    }

    show_graph(gr, "Initial State");

    for(vnode_t* pv_run = gr->pv_vertex_head_node->next; pv_run != gr->pv_vertex_head_node; pv_run = pv_run -> next)
    {
        status = bfs(gr, pv_run->v);
    }
}

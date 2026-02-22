#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"

/*Graph related function*/
graph_t* create_graph(void)
{
    graph_t* new_graph = (graph_t*)xmalloc(sizeof(graph_t));
    new_graph->pv_vertex_head_node = v_create_list();
    new_graph->nr_vertices = 0;
    new_graph->nr_edges = 0;
    return new_graph;
}

status_t insert_vertex(graph_t* gr, vertex_t _v)
{
    if(v_search_node(gr->pv_vertex_head_node, _v) != NULL)
        return G_EXISTING_VERTEX;
    status_t status = v_insert_end(gr->pv_vertex_head_node, _v);
    assert(status == SUCCESS);
    gr->nr_vertices += 1;
    return status;
}

status_t insert_edge(graph_t* gr, vertex_t start, vertex_t end)
{
    int incosistent_flag = 0;
    status_t status;

    vnode_t* pv_start_vertex = v_search_node(gr->pv_vertex_head_node, start);
    if(pv_start_vertex == NULL)
        return G_INVALID_VERTEX;

    vnode_t* pv_end_vertex = v_search_node(gr->pv_vertex_head_node, end);    
    if(pv_end_vertex == NULL)
        return G_INVALID_VERTEX;

    hnode_t* ph_start_in_end = h_search_node(pv_end_vertex->ph_edges_head_node, start);
    if(ph_start_in_end)
        incosistent_flag |= 0x01; //

    hnode_t* ph_end_in_start = h_search_node(pv_start_vertex->ph_edges_head_node, end);
    if(ph_end_in_start)
        incosistent_flag |= 0x10; //

    if(incosistent_flag == 0x11){

        return G_EXISTING_EDGE;
    }
    else if(incosistent_flag >= 0x01 && incosistent_flag <= 0X10)
    {

        return G_INCINSISTENT_EDGE;
    }

    status = h_insert_end(pv_start_vertex->ph_edges_head_node, end);
    assert(status == SUCCESS);
    status = h_insert_end(pv_end_vertex->ph_edges_head_node, start);
    assert(status == SUCCESS);

    gr->nr_edges += 1;
    
    return SUCCESS;
}

status_t remove_vertex(graph_t* gr, vertex_t _v)
{
    vnode_t* pv_delete_vertex = v_search_node(gr->pv_vertex_head_node, _v);
    if(pv_delete_vertex == NULL)
        return G_INVALID_VERTEX;

    hnode_t* ph_run = pv_delete_vertex->ph_edges_head_node -> next;
    hnode_t* ph_run_next = NULL;
    hnode_t* ph_delete_hnode_in_adj_vnode = NULL;

    vnode_t* pv_adj_vnode = NULL;

    while(ph_run != pv_delete_vertex->ph_edges_head_node)
    {
        ph_run_next = ph_run->next;
        pv_adj_vnode = v_search_node(gr->pv_vertex_head_node, ph_run->v);
        ph_delete_hnode_in_adj_vnode = h_search_node(pv_adj_vnode->ph_edges_head_node, _v);
        h_generic_delete(ph_delete_hnode_in_adj_vnode);
        free(ph_run);
        gr->nr_edges -= 1;
        ph_run = ph_run_next;        
    }
    free(pv_delete_vertex->ph_edges_head_node);
    v_generic_delete(pv_delete_vertex);
    gr->nr_vertices -= 1;
    
    return SUCCESS;
}
status_t remove_edge(graph_t* gr, vertex_t start, vertex_t end)
{
    vnode_t* pv_start = v_search_node(gr->pv_vertex_head_node, start);
    if(pv_start == NULL)
        return G_INVALID_VERTEX;

    vnode_t* pv_end = v_search_node(gr->pv_vertex_head_node, end);
    if(pv_end == NULL)
        return G_INVALID_VERTEX;
    
    hnode_t* ph_start_in_end = h_search_node(pv_end->ph_edges_head_node, start);
    if(ph_start_in_end == NULL)
        return G_INVALID_EDGE;

    hnode_t* ph_end_in_start = h_search_node(pv_start->ph_edges_head_node, end);
    if(ph_end_in_start == NULL)
        return G_INVALID_EDGE;
        
    h_generic_delete(ph_start_in_end);
    h_generic_delete(ph_end_in_start);

    return SUCCESS;
}

status_t show_graph(graph_t* gr, const char* msg)
{
    if(msg)
        puts(msg);
    
    vnode_t* pv_run = gr->pv_vertex_head_node->next;
    hnode_t* ph_run = NULL;

    for(; pv_run != gr->pv_vertex_head_node; pv_run = pv_run ->next)
    {
        printf("[%d]\t<->\t", pv_run->v);
        for(ph_run = pv_run->ph_edges_head_node->next; ph_run != pv_run->ph_edges_head_node; ph_run = ph_run->next)
        {
            printf("[%d]<->", ph_run->v);
        }
        puts("[END]");
    }
    puts("--------------------------------------------------------------"); 
}

status_t destroy_graph(graph_t** _gr)
{
    graph_t* gr = *_gr;
    vnode_t* pv_run = gr->pv_vertex_head_node->next;
    vnode_t* pv_run_next = NULL;

    hnode_t* ph_run = NULL;
    hnode_t* ph_run_next = NULL;

    for(; pv_run != gr->pv_vertex_head_node; pv_run = pv_run_next)
    {
        pv_run_next = pv_run->next;

        for(ph_run = pv_run->ph_edges_head_node->next; ph_run != pv_run->ph_edges_head_node; ph_run = ph_run_next)
        {
            ph_run_next = ph_run->next;
            free(ph_run);
        }
        free(pv_run->ph_edges_head_node);
        free(pv_run);
    }
    free(gr->pv_vertex_head_node);
    free(gr);
    *_gr = NULL;

    return SUCCESS;
}

/*Function to maintain vertices list*/
vlist_t* v_create_list(void)
{
    vnode_t* head_node = v_get_vlist_node(-1);
    head_node->next = head_node;
    head_node->prev = head_node;
    return head_node;    
}
status_t v_insert_end(vlist_t* pv_list, vertex_t v)
{
    v_generic_insert(pv_list->prev, v_get_vlist_node(v), pv_list);
    return SUCCESS;
}
void v_generic_insert(vnode_t* beg, vnode_t* mid, vnode_t* end)
{
    mid->next = end;
    mid->prev = beg;
    beg->next = mid;
    end->prev = mid;
}
void v_generic_delete(vnode_t* delete_node)
{
    delete_node->prev->next = delete_node->next;
    delete_node->next->prev = delete_node->prev;
    free(delete_node);
}
vnode_t* v_search_node(vlist_t* pv_list, vertex_t _v)
{
    vnode_t* run = NULL;
    for(run = pv_list->next; run != pv_list; run = run -> next)
    {
        if(run->v == _v)
            return run;
    }
    return NULL;
}
vnode_t* v_get_vlist_node(vertex_t _v)
{
    vnode_t* new_node = (vnode_t*)xmalloc(sizeof(vnode_t));
    new_node -> v = _v;
    new_node->ph_edges_head_node = h_create_list();
    new_node -> next = NULL;
    new_node -> prev = NULL;    
}

/*Function to maintain vertices list*/
hlist_t* h_create_list(void)
{
    hnode_t* head_node = h_get_hlist_node(-1);
    head_node->next = head_node;
    head_node->prev = head_node;
    return head_node;
}

status_t h_insert_end(hlist_t* ph_list, vertex_t v)
{
    h_generic_insert(ph_list->prev, h_get_hlist_node(v), ph_list);
    return SUCCESS;
}

void h_generic_insert(hnode_t* beg, hnode_t* mid, hnode_t* end)
{
    mid->next = end;
    mid->prev = beg;
    beg->next = mid;
    end->prev = mid;

}
void h_generic_delete(hnode_t* delete_node)
{
    delete_node->prev->next = delete_node->next;
    delete_node->next->prev = delete_node->prev;
    free(delete_node);
}

hnode_t* h_search_node(hlist_t* ph_list, vertex_t _v)
{
    hnode_t* run = NULL;
    for(run = ph_list->next; run != ph_list; run = run -> next)
    {
        if(run->v == _v)
            return run;
    }
    return NULL;
}

hnode_t* h_get_hlist_node(vertex_t _v)
{
    hnode_t* new_node = (hnode_t*)xmalloc(sizeof(hnode_t));
    new_node -> v = _v;
    new_node -> next = NULL;
    new_node -> prev = NULL;
}

void* xmalloc(unsigned long nr_bytes)
{
    void* p = NULL;
    p = malloc(nr_bytes);
    if(p == NULL)
    {
        fprintf(stderr, "Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    return p;
}

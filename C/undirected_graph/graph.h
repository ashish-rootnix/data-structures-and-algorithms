#ifndef _GRAPH_H
#define _GRAPH_H

typedef int vertex_t;
typedef struct hnode hnode_t;
typedef struct vnode vnode_t;
typedef struct graph graph_t;
typedef vnode_t vlist_t;
typedef hnode_t hlist_t;
typedef enum STATUS status_t;

enum STATUS
{
    G_INVALID_VERTEX            =   -1,
    G_EXISTING_VERTEX           =   -2,    
    G_INCINSISTENT_EDGE         =   -3,
    G_EXISTING_EDGE             =   -4,
    G_INVALID_EDGE              =   -5,

    SUCCESS                     =   1,
    TRUE                        =   1,
    FALSE                       =   0
};

struct hnode
{
    vertex_t v;
    struct hnode* next;
    struct hnode* prev;
};

struct vnode
{
    vertex_t v;
    hnode_t* ph_edges_head_node;
    struct vnode* next;
    struct vnode* prev;
};

struct graph
{
    vnode_t* pv_vertex_head_node;
    unsigned long nr_vertices;
    unsigned long nr_edges;
};

/*Graph related function*/
graph_t* create_graph(void);
status_t insert_vertex(graph_t* gr, vertex_t _v);
status_t insert_edge(graph_t* gr, vertex_t start, vertex_t end);
status_t remove_vertex(graph_t* gr, vertex_t _v);
status_t remove_edge(graph_t* gr, vertex_t start, vertex_t end);
status_t show_graph(graph_t* gr, const char* msg);
status_t destroy_graph(graph_t** gr);

/*Function to maintain vertices list*/
vlist_t* v_create_list(void);
status_t v_insert_end(vlist_t* pv_list, vertex_t v);
void v_generic_insert(vnode_t* beg, vnode_t* mid, vnode_t* end);
void v_generic_delete(vnode_t* delete_node);
vnode_t* v_search_node(vlist_t* pv_list, vertex_t _v);
vnode_t* v_get_vlist_node(vertex_t _v);

/*Function to maintain vertices list*/
hlist_t* h_create_list(void);
status_t h_insert_end(hlist_t* ph_list, vertex_t v);
void h_generic_insert(hnode_t* beg, hnode_t* mid, hnode_t* end);
void h_generic_delete(hnode_t* delete_node);
hnode_t* h_search_node(hlist_t* ph_list, vertex_t _v);
hnode_t* h_get_hlist_node(vertex_t _v);

void* xmalloc(unsigned long nr_bytes);

#endif

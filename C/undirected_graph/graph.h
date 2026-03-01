#ifndef _GRAPH_H
#define _GRAPH_H

typedef int vertex_t;
typedef struct hnode hnode_t;
typedef struct vnode vnode_t;
typedef struct graph graph_t;
typedef vnode_t vlist_t;
typedef hnode_t hlist_t;
typedef enum STATUS status_t;
typedef enum COLOR color_t;
typedef struct queue_node queue_node_t;

enum STATUS
{
    G_INVALID_VERTEX            =   -1,
    G_EXISTING_VERTEX           =   -2,    
    G_INCINSISTENT_EDGE         =   -3,
    G_EXISTING_EDGE             =   -4,
    G_INVALID_EDGE              =   -5,
    G_QUEUE_EMPTY               =   -6,

    SUCCESS                     =   1,
    TRUE                        =   1,
    FALSE                       =   0
};

enum COLOR
{
    WHITE = 0,
    GREY,
    BLACK
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
    color_t color;
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

struct queue_node
{
    vnode_t* pv_node;
    struct queue_node* q_next;
    struct queue_node* q_prev;
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

/* Traversal DFS and BFS*/
void dfs(graph_t* gr);
status_t bfs(graph_t* gr, vertex_t v);

/*DFS helper funtions*/
void reset(graph_t* gr);
void dfs_visit(graph_t* gr, vnode_t* pv);

/*BFS helper functions*/
queue_node_t* create_queue(void);
status_t enqueue(queue_node_t* p_queue, vnode_t* pv_node);
status_t dequeue(queue_node_t* p_queue, vnode_t** pp_node);
int is_queue_empty(queue_node_t* p_queue);
status_t destroy_queue(queue_node_t* pv_node);
void q_generic_insert(queue_node_t* p_beg, queue_node_t* p_mid, queue_node_t* p_end);
void q_generic_delete(queue_node_t* p_delete_node);
queue_node_t* q_get_node(vnode_t* pv_node);

#endif

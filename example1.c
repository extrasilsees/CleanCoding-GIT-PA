#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
}NODE;

typedef struct grafic {
    int vertices;
    int *visited;
    struct Node **adj_list;
}GRAFIC;

typedef struct stack {
    int top;
    int capacity;
    int *array;
}STACK;

NODE *create_node(int value)
{
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

void add_edge(GRAFIC *graph, int source, int destination)
{
    NODE *new_node = create_node(destination);
    new_node->next = graph->adj_list[source];
    graph->adj_list[source] = new_node;
    new_node = create_node(source);
    new_node->next = graph->adj_list[destination];
    graph->adj_list[destination] = new_node;
}

GRAFIC *create_g(int vertices)
{
    GRAFIC *graph = malloc(sizeof(GRAFIC));
    graph->vertices = vertices;
    graph->adj_list = malloc(sizeof(NODE *) * vertices);
    graph->visited = malloc(sizeof(int) * vertices);

    for (int i = 0; i < vertices; i++)
    {
        graph->adj_list[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

STACK *create_s(int capacity)
{
    STACK *stack = malloc(sizeof(STACK));
    stack->array = malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;

    return stack;
}

void push(int push_element, STACK *stack)
{
    stack->top = stack->top + 1;
    stack->array[stack->top] = push_element;
}

void DFS(GRAFIC *graph, STACK *stack, int vertex_number)
{
    NODE *adj_list = graph->adj_list[vertex_number];
    NODE *aux = adj_list;
    graph->visited[vertex_number] = 1;
    printf("%d ", vertex_number);
    push(vertex_number, stack);

    while (aux != NULL)
    {
        int connected_vertex = aux->data;

        if (graph->visited[connected_vertex] == 0)
        {
            DFS(graph,stack, connected_vertex);
        }

        aux = aux->next;
    }
}

void insert_edges(GRAFIC *graph, int edge_number, int number_vertices)
{
    int source, destination, i;
    printf("Adauga %d munchii (de la 1 la %d)\n", edge_number,number_vertices);

    for (i = 0; i < edge_number; i++)
    {
        scanf("%d%d", &source, &destination);
        add_edge(graph, source, destination);
    }
}

void i_can_reach(GRAFIC *graph,int number_vertices,STACK *stack)
{
    int answear = 1;
    DFS(graph,stack,0);

    for(int i=0;i<number_vertices;i++)
    {
        if(graph->visited[i]==0)
        {
            answear = 0;
            break;
        }
    }
    printf("\nPoate fi strabatut %s \n",answear ?"dap":"nope");
}

int main() {

    int number_vertices;
    int edge_number;

    printf("cate noduri are graful?");
    scanf("%d", &number_vertices);

    printf("cate muchii are graful?");
    scanf("%d", &edge_number);

    GRAFIC *graph = create_g(number_vertices);
    STACK *stack = create_s(2 * number_vertices);

    insert_edges(graph, edge_number, number_vertices);

    i_can_reach(graph, number_vertices,stack);

    return 0;
}

#ifndef DSL_H_
#define DSL_H_

/// @brief DSL collection

#define OPERATION(op, node1, node2)       \
    new_node(OPERATION, op, node1, node2)

#define ADD_(node1, node2)  new_node ( OPERATION, ADD,    node1, node2                 ) /// <add node1 data and node2 data
#define SUB_(node1, node2)  new_node ( OPERATION, ADD,    node1, MUL_(NUM_(-1), node2) ) /// <subtract node2 data from node1 data
#define MUL_(node1, node2)  new_node ( OPERATION, MUL,    node1, node2                 ) /// <multiply node1 data on node2 data
#define DIV_(node1, node2)  new_node ( OPERATION, DIV,    node1, node2                 ) /// <divide node1 data on node2 data
#define SIN_(node1       )  new_node ( OPERATION, SIN,    node1, NULL                  ) /// <sin function of node1 data
#define COS_(node1       )  new_node ( OPERATION, COS,    node1, NULL                  ) /// <cos function of node1 data
#define TG_(node1        )  new_node ( OPERATION, TG,     node1, NULL                  ) /// <tg function of node1 data
#define CTG_(node1       )  new_node ( OPERATION, CTG,    node1, NULL                  ) /// <ctg function of node1 data
#define ARCSIN(node1     )  new_node ( OPERATION, ARCSIN, node1, NULL                  ) /// <arcsin function of node1 data
#define ARCCOS(node1     )  new_node ( OPERATION, ARCCOS, node1, NULL                  ) /// <arccos function of node1 data
#define NUM_(value       )  new_node ( OBJECT,    value,  NULL,  NULL                  ) /// <make node of number
#define X_                  new_node ( VARIABLE,  0,      NULL,  NULL                  ) /// <make node of variable

//TODO несколько переменных

#endif

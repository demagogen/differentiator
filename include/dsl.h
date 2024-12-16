#ifndef DSL_H_
#define DSL_H_

//-----------------------------------------------------------------------------------------------------------------------------
//!                                                      DSL COLLECTION
//-----------------------------------------------------------------------------------------------------------------------------

/// @brief DSL collection

#define OPERATION(op, node1, node2) \
    new_node (OPERATION, op, left_node, right_node)

#define ADD_(node1, node2)  new_node ( OPERATION, ADD,    node1, node2                 ) /// <add left_node data and right_node data
#define SUB_(node1, node2)  new_node ( OPERATION, ADD,    node1, MUL_(NUM_(-1), node2) ) /// <subtract right_node data from left_node data
#define MUL_(node1, node2)  new_node ( OPERATION, MUL,    node1, node2                 ) /// <multiply left_node data on right_node data
#define DIV_(node1, node2)  new_node ( OPERATION, DIV,    node1, node2                 ) /// <divide left_node data on right_node data
#define SIN_(node1       )  new_node ( OPERATION, SIN,    node1, NULL                  ) /// <sin function of left_node data
#define COS_(node1       )  new_node ( OPERATION, COS,    node1, NULL                  ) /// <cos function of left_node data
#define LN_(node1        )  new_node ( OPERATION, LN,     node1, NULL                  ) /// <ln function of left_node data
#define TG_(node1        )  new_node ( OPERATION, TG,     node1, NULL                  ) /// <tg function of left_node data
#define POW_(node1, node2)  new_node ( OPERATION, POW,    node1, node2                 ) /// <pow function of left_node data
#define CTG_(node1       )  new_node ( OPERATION, CTG,    node1, NULL                  ) /// <ctg function of left_node data
#define ARCSIN_(node1    )  new_node ( OPERATION, ARCSIN, node1, NULL                  ) /// <arcsin function of left_node data
#define ARCCOS_(node1    )  new_node ( OPERATION, ARCCOS, node1, NULL                  ) /// <arccos function of left_node data
#define NUM_(value       )  new_node ( OBJECT,    value,  NULL,  NULL                  ) /// <make node of number
#define X_                  new_node ( VARIABLE,  0,      NULL,  NULL                  ) /// <make node of variable

//TODO more variables than one x

#endif

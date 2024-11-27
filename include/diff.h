#ifndef DIFF_H_
#define DIFF_H_

#include "diff_tree.h"

#define ADD_(node1, node2)  new_node ( OPERATION, ADD,    node1, node2 )
#define SUB_(node1, node2)  new_node ( OPERATION, SUB,    node1, node2 )
#define MUL_(node1, node2)  new_node ( OPERATION, MUL,    node1, node2 )
#define DIV_(node1, node2)  new_node ( OPERATION, DIV,    node1, node2 )
#define SIN_(node1       )  new_node ( OPERATION, SIN,    node1, NULL  )
#define COS_(node1       )  new_node ( OPERATION, COS,    node1, NULL  )
#define TG_ (node1       )  new_node ( OPERATION, TG,     node1, NULL  )
#define CTG_(node1       )  new_node ( OPERATION, CTG,    node1, NULL  )
#define ARCSIN(node1     )  new_node ( OPERATION, ARCSIN, node1, NULL  )
#define ARCCOS(node1     )  new_node ( OPERATION, ARCCOS, node1, NULL  )
#define NUM_(value       )  new_node ( OBJECT,    value,  NULL,  NULL  )
#define X_                  new_node ( VARIABLE,  0,      NULL,  NULL  )

#endif

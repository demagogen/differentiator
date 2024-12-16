#ifndef DIFF_H_
#define DIFF_H_

#include <math.h>

#include "differentiator_utils.h"
#include "differentiator_tree.h"

/// @brief differentiating function
/// @param tree's root
/// @return node on new tree

NODE* differentiate (TREE* tree, NODE* node);

/// @brief parse operations
/// @param pointer on node
/// @return node changed after operation

NODE* take_node_derivative (TREE* tree, NODE* node);

/// @brief optimize tree
/// @param pointer on tree structure

//TODO return good or bad status after ending

void optimization (NODE* node, bool* detector);

/// @brief change tree nodes
/// @param start node
/// @param pointer on indicator

void recursive_constant_propagation (NODE* node, bool* indicator);

/// @brief recursive remove
/// @param pointer on operation node

void recursive_remove_trivials (NODE** node, bool* indicator);

/// @brief random phrase
/// @param phrases array
/// @return phrase

const char* random_phrase ();

#endif

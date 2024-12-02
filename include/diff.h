#ifndef DIFF_H_
#define DIFF_H_

#include "diff_tree.h"

/// @brief differentiating function
/// @param tree's root
/// @return node on new tree

NODE* differentiate(NODE* node);

/// @brief optimize tree
/// @param pointer on tree structure

//TODO return good or bad status after ending

void optimization(TREE* tree);

/// @brief change tree nodes
/// @param start node
/// @param pointer on indicator

void recursive_constant_propagation(NODE* node, bool* indicator);

/// @brief recursive remove
/// @param pointer on operation node

void recursive_remove_trivials(NODE* node, bool* indicator);

#endif

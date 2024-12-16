#ifndef DIFF_TREE_H_
#define DIFF_TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>

#include "differentiator_typedefs.h"
#include "dsl.h"

//-----------------------------------------------------------------------------------------------------------------------------
//!                                                         MAIN TREE FUNCTIONS
//-----------------------------------------------------------------------------------------------------------------------------

/// @brief initialize new tree structure
/// @param pointer on structure with information about tree
/// @return tree error code

TREE_ERROR tree_ctor (TREE* tree);

/// @brief delete all information in tree structure
/// @param pointer on structure with information about tree
/// @return tree error code

TREE_ERROR tree_dtor (TREE* tree);

/// @brief create new node in tree, which get right and left subnodes
/// @param new node data type
/// @param new node data
/// @param new node left node
/// @param new node right node
/// @return pointer on new node

NODE* new_node (NODE_ELEMENT_TYPE type, NodeData_t data, NODE* left, NODE* right);

/// @brief relink nodes. Put newNode on oldNode place
/// @param pointer on old node
/// @param pointer on new node
/// @return TREE_ERROR

TREE_ERROR relink_node (NODE* oldNode, NODE* newNode);

/// @brief copy node
/// @param node, which required to copy
/// @return pointer on new node

NODE* copy_node (NODE* node);

/// @brief delete node by pointer
/// @param pointer on required node
/// @return tree error code

TREE_ERROR node_dtor (NODE* node);

/// @brief recursive print tree in prefix format in file
/// @param file pointer for output
/// @param pointer on node structure
/// @return error code

TREE_ERROR prefix_print (FILE* file, NODE* node);

/// @brief recursive print tree in easy infix format in file
/// @param file pointer for output
/// @param pointer on node structure
/// @return error code

TREE_ERROR infix_print (FILE* file, NODE* node);

/// @brief recursive print tree in bad TeX format (skip \frac {}{})
/// @param file for output
/// @param pointer on node structure

TREE_ERROR bad_tex_print (FILE* file, NODE* node);

//-----------------------------------------------------------------------------------------------------------------------------
//!                                                         TREE DUMP FUNCTIONS
//-----------------------------------------------------------------------------------------------------------------------------

/// @brief make dotfile with tree graph
/// @param pointer on tree structure

void dump_tree (TREE* tree);

/// @brief recursive node dump
/// @param pointer on dotfile structure
/// @param pointer on node index value
/// @param pointer on node structure

void dump_all_nodes (FILE* dotfile, size_t* index, NODE* node);

/// @brief print node information in dotfile
/// @param pointer on dotfile structure
/// @param pointer on node index value
/// @param pointer on node structure

void dump_node_vertex (FILE* dotfile, size_t* index, NODE* node);

/// @brief print arrow between nodes in nodefile
/// @param pointer on dotfile structure
/// @param first node index value
/// @param second node index value
/// @param pointer on first node structure

void dump_node_edge (FILE* dotfile, size_t first_node_index, size_t second_node_index, NODE* node);

#endif

#ifndef DIFF_TREE_H_
#define DIFF_TREE_H_

#include "diff_typedefs.h"

/* TODO think about tree_enum.h */

/// @brief tree errors codes

enum TREE_ERROR
{
    TREE_NODE_DED_INSIDE              = -3, /// <deleted node status
    TREE_DED_INSIDE                   = -2, /// <deleted tree status
    TREE_POISON                       = -1, /// <poison tree data status
    TREE_NONE                         =  0, /// <no error
    TREE_STRUCT_ALLOCATION_ERROR      =  1, /// <null pointer on tree structure
    TREE_NODE_ALLOCATION_ERROR        =  2, /// <null pointer on node structure in tree
    TREE_INVALID_CAPACITY             =  3, /// <invalid capacity value
    TREE_OVERSIZE                     =  4, /// <requested capacity is bigger than tree capacity
    TREE_MISSING_IP                   =  5, /// <invalid node ip value
    TREE_ROOT_ALLOCATION_ERROR        =  6, /// <null pointer on tree root
    TREE_LEFT_CHILD_ALLOCATION_ERROR  =  7, /// <null pointer on left node
    TREE_RIGHT_CHILD_ALLOCATION_ERROR =  8, /// <null pointer on right node
    TREE_PARENT_ALLOCATION_ERROR      =  9, /// <null pointer on parent node
    TREE_NODE_NOT_LEAF                = 11, /// <marker, that node is leaf
    TREE_ERROR_SIDE                   = 12, /// <invalid side enum value
    TREE_NULL_NODE                    = 13, /// <null pointer on node
    TREE_NODE_TYPE_ERROR              = 14, /// <node type error
};

/// @brief new node add rule

enum NODE_RULE
{
    RULE_POISON = -1, /// <no rule for add
    ROOT        =  0, /// <add data in root
    RIGHT       =  1, /// <add new right node
    LEFT        =  2, /// <add new left node
};

/// @brief data type information

enum NODE_ELEMENT_TYPE
{
    TYPE_POISON = -1, /// <no valid data type
    OBJECT      =  1, /// <type of object (value)
    OPERATION   =  2, /// <type of operation
    VARIABLE    =  3, /// <type of variable
};

/// @brief operation enum

enum OPERATIONS
{
    ADD = 1, ///  <add two numbers in nodes
    SUB = 2, ///  <subtract right node number from left node number
    MUL = 3, ///  <multiply two numbers in nodes
    DIV = 4, ///  <divide left node number on right node number
    POW = 5, ///  <raise left node number to a power of right node number
};

typedef double NodeData_t; /// <node data type typedef

/// @brief constants

const size_t StartTreeCapacity = 0; /// <start tree capacity

/// @brief node structure

struct NODE
{
    NODE_RULE         side;      /// <information about how the node relates to the previous one

    NODE*             parent;    /// <pointer on parent node
    NODE*             left;      /// <pointer on left node
    NODE*             right;     /// <pointer on right node

    NODE_ELEMENT_TYPE type;      /// <information about data type in node
    NodeData_t        data;      /// <node data
};

/// @brief tree structure

struct TREE
{
    NODE*      root;     /// <pointer on root node
    size_t     capacity; /// <tree capacity value
    TREE_ERROR error;    /// <tree status
};

/// @brief initialize new tree structure
/// @param pointer on structure with information about tree
/// @return tree error code

TREE_ERROR tree_ctor(TREE* tree);

/// @brief delete all information in tree structure
/// @param pointer on structure with information about tree
/// @return tree error code

TREE_ERROR tree_dtor(TREE* tree);

/// @brief add new node in tree
/// @param pointer on structure with information about tree
/// @param pointer on structure with information about node
/// @param enum with rule, which explain where we will add new node
/// @param enum with information about tree data type
/// @param data, which we will put in new node
/// @return tree error code

TREE_ERROR tree_add(TREE* tree, NODE* node, NODE_RULE rule, NODE_ELEMENT_TYPE node_type, NodeData_t data);

/// @brief delete node in tree
/// @param pointer on tree structure
/// @param pointer on node structure
/// @return tree error code

TREE_ERROR tree_delete(TREE* tree, NODE* node);

/// @brief make dotfile with tree graph
/// @param pointer on tree structure

void tree_graphic_dump(TREE* tree);

/// @brief recursive node dump
/// @param pointer on dotfile structure
/// @param pointer on node index value
/// @param pointer on node structure

void node_graphic_dump (FILE* dotfile, size_t* index, NODE* node);

/// @brief print node information in dotfile
/// @param pointer on dotfile structure
/// @param pointer on node index value
/// @param pointer on node structure

void node_print_node (FILE* dotfile, size_t* index, NODE* node);

/// @brief print arrow between nodes in nodefile
/// @param pointer on dotfile structure
/// @param first node index value
/// @param second node index value
/// @param pointer on first node structure

void node_print_edge(FILE* dotfile, size_t first_node_index, size_t second_node_index, NODE* node);

#endif

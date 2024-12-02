#ifndef DIFF_TREE_H_
#define DIFF_TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>

#include "dsl.h"

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
    POISON = -1, /// <poison operation value
    ADD    =  1, /// <add two numbers in nodes
    SUB    =  2, /// <subtract right node number from left node number
    MUL    =  3, /// <multiply two numbers in nodes
    DIV    =  4, /// <divide left node number on right node number
    POW    =  5, /// <raise left node number to a power of right node number
    COS    =  6, /// <cos of left node value
    SIN    =  7, /// <sin of left node value
    TG     =  8, /// <tg of left node value
    CTG    =  9, /// <ctg of left node value
    SH     = 10, /// <sh of left node value
    CH     = 11, /// <ch of left node value
    TH     = 12, /// <th of left node value
    CTH    = 13, /// <cth of left node value
    ARCCOS = 14, /// <arccos of left node value
    ARCSIN = 15, /// <arcsin of left node value
    ARCTG  = 16, /// <arctg of left node value
    ARCCTG = 17, /// <arcctg of left node value
    ARCSH  = 18, /// <arcsh of left node value
    ARCCH  = 19, /// <arcch of left node value
    ARCTH  = 20, /// <arcth of left node value
    ARCCTH = 21, /// <arccth of left node value
    LOG    = 22, /// <log with base of right value and argument in left node value
    LN     = 23, /// <ln with argument in left node value
};

typedef double NodeData_t; /// <node data type typedef

/// @brief constants

const size_t StartTreeCapacity   =  0; /// <start tree capacity
const size_t EdgeColorStringSize = 11; /// <edge color string size

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

/// @brief create new node in tree, which get right and left subnodes
/// @param new node data type
/// @param new node data
/// @param new node left node
/// @param new node right node
/// @return pointer on new node

NODE* new_node(NODE_ELEMENT_TYPE type, NodeData_t data, NODE* left, NODE* right);

/// @brief copy node
/// @param node, which required to copy
/// @return pointer on new node

NODE* copy_node(NODE* node);

/// @brief delete node by pointer
/// @param pointer on required node
/// @return tree error code

TREE_ERROR tree_node_dtor(NODE* node);

/// @brief recursive print tree in prefix format in file
/// @param file pointer for output
/// @param pointer on node structure
/// @return error code

TREE_ERROR prefix_print(FILE* file, NODE* node);

/// @brief recursive print tree in easy infix format in file
/// @param file pointer for output
/// @param pointer on node structure
/// @return error code

TREE_ERROR infix_print(FILE* file, NODE* node);

/// @brief recursive print tree in bad TeX format (skip \frac {}{})
/// @param file for output
/// @param pointer on node structure

TREE_ERROR bad_tex_print(FILE* file, NODE* node);

//___________________________________________________RECURSIVE COUNTER______________________________________________________

NODE* get_number();
NODE* get_p();
NODE* get_grammar();
NODE* get_e();
NODE* get_t();
NODE* syntax_error();

//___________________________________________________TREE DUMP FUNCTIONS____________________________________________________

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

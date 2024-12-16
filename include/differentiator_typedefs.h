#ifndef DIFFERENTIATOR_TYPEDEFS
#define DIFFERENTIATOR_TYPEDEFS

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>

#include "dsl.h"

/* TODO think about tree_enum.h */

//-----------------------------------------------------------------------------------------------------------------------------
//!                                                         ENUMS
//-----------------------------------------------------------------------------------------------------------------------------

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
    TREE_ERROR_SIDE                   = 12, /// <invalid rule enum value
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
    POISON        = -1, /// <poison operation value
    ADD           =  1, /// <add two numbers in nodes
    SUB           =  2, /// <subtract right node number from left node number
    MUL           =  3, /// <multiply two numbers in nodes
    DIV           =  4, /// <divide left node number on right node number
    POW           =  5, /// <raise left node number to a power of right node number
    COS           =  6, /// <cos of left node value
    SIN           =  7, /// <sin of left node value
    LN            = 23, /// <ln with argument in left node value
    OPEN_BRACKET  = 24, /// <open bracket in parsing
    CLOSE_BRACKET = 25, /// <close bracket in parsing
    END           = 26, /// <end flag in parsing
};

//-----------------------------------------------------------------------------------------------------------------------------
//!                                                          TYPEDEFS
//-----------------------------------------------------------------------------------------------------------------------------

typedef double NodeData_t; /// <node data type typedef

/// @brief constants

const size_t StartTreeCapacity   =  0; /// <start tree capacity
const size_t EdgeColorStringSize = 11; /// <edge color string size

//-----------------------------------------------------------------------------------------------------------------------------
//!                                                          DEFINES
//-----------------------------------------------------------------------------------------------------------------------------

#define PARENT node->parent
#define DED node->parent->parent

//-----------------------------------------------------------------------------------------------------------------------------
//!                                                         STRUCTURES
//-----------------------------------------------------------------------------------------------------------------------------

/// @brief node structure

struct NODE
{
    NODE_RULE         rule;      /// <information about how the node relates to the previous one

    NODE*             parent;    /// <pointer on parent node
    NODE*             left;      /// <pointer on left node
    NODE*             right;     /// <pointer on right node

    NODE_ELEMENT_TYPE type;      /// <information about data type in node
    NodeData_t        data;      /// <node data
};

/// @brief tree structure

struct TREE
{
    NODE*      diffNode;
    FILE*      latex_dump_file;
    NODE*      root;     /// <pointer on root node
    size_t     capacity; /// <tree capacity value
    TREE_ERROR error;    /// <tree status
};

#endif

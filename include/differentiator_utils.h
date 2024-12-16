#ifndef DIFF_UTILS_H_
#define DIFF_UTILS_H_

#include "differentiator.h"
#include "differentiator_utils.h"
#include "differentiator_tree.h"

//-----------------------------------------------------------------------------------------------------------------------------
//!                                                         DEFINES
//-----------------------------------------------------------------------------------------------------------------------------

#define DIFF_LEFT  differentiate  ( tree, node->left  )
#define DIFF_RIGHT differentiate  ( tree, node->right )
#define COPY_LEFT  copy_node     ( node->left  )
#define COPY_RIGHT copy_node     ( node->right )

#define CUT_CHILDS_AND_SAVE_VALUE(value)  \
    node->left  = NULL;                  \
    node->right = NULL;                  \
                                         \
    node->type = OBJECT;                 \
    node->data = value;

#define VERIFY_SEGMENT_STATEMENT(node)               \
    if (!node || !(*node)->left || !(*node)->right) \
    {                                               \
        return;                                     \
    }

#define NODE_PTR (*node)

#define PARSE_NODES(node1, node2)    \
    objectNode = node1;             \
    otherNode  = node2;

#define DEBUG_NODES_DUMP                                                         \
    printf("operationNode: %s\n", return_operation_string (operationNode->data)); \
    printf("objectNode:    %lf\n", objectNode->data);                           \
    printf("otherNode:     %lf\n", otherNode->data);

//-----------------------------------------------------------------------------------------------------------------------------
//!                                                CONSTANTS PROPAGATION UTILS
//-----------------------------------------------------------------------------------------------------------------------------

/// @brief check for having variable in subtree
/// @param pointer on node
/// @return true or false

bool have_variable (NODE* node);

/// @brief check, that two child nodes are objects
/// @param pointer on parent node
/// @return true or false

bool two_childs_are_objects (NODE* parentNode);

/// @brief check, that exists object with zero value
/// @param pointer on parent node
/// @return true or false

bool check_one_object_is_zero (NODE* parentNode);

/// @brief check operation node for having only one object child
/// @param pointer on node
/// @return true or false

bool check_for_basic_trivials_statement (NODE* node);

//-----------------------------------------------------------------------------------------------------------------------------
//!                                                  REMOVE TRIVIALS UTILS
//-----------------------------------------------------------------------------------------------------------------------------

/// @brief check, that operation is add, and object is zero
/// @param pointer on operation node
/// @param pointer on object node
/// @return true or false

bool trivials_add_zero (NODE* operationNode, NODE* objectNode);

/// @brief check, that operation is mul, and object in one
/// @param pointer on operation node
/// @param pointer on object node
/// @return true or false

bool trivials_mul_one (NODE* operationNode, NODE* objectNode);

//-----------------------------------------------------------------------------------------------------------------------------
//!                                                  TREE UTILS FUNCTIONS
//-----------------------------------------------------------------------------------------------------------------------------

/// @brief print TREEP_ERROR enum name as string
/// @param required TREE_ERROR enum
/// @return TREE_ERROR enum name string

const char* return_tree_error_enum_name_string (TREE_ERROR enum_param);

/// @brief print NODE_RULE enum name as string
/// @param required NODE_RULE enum
/// @return NODE_RULE enum name string

const char* return_node_rule_enum_name_string (NODE_RULE enum_param);

/// @brief print NODE_ELEMENT_TYPE enum name as string
/// @param required NODE_ELEMENT_TYPE enum
/// @return NODE_ELEMENT_TYPE enum name string

const char* return_type_string (NODE_ELEMENT_TYPE enum_param);

/// @brief function for print OPERATIONS enum name as string
/// @param required OPERATIONS enum
/// @return OPERATIONS enum name string

const char* return_operation_string (NodeData_t data);

/// @brief return OPERATIONS enum value
/// @param pointer on node structure
/// @return OPERATIONS enum value

OPERATIONS return_operation_code (NODE* node);

/// @brief function for read line from buffer
/// @param line, which will be filled
/// @param pointer on line start in buffer
/// @return int error code

int read_line (char** line, char** base_ip);

/// @brief compare enum values

enum COMPARE
{
    LESS  = -1, /// <left value is less than right
    EQUAL =  0, /// <values are equal
    MORE  =  1, /// <left value is more than right
};

/// @brief compare function for two double values
/// @param first value
/// @param second value
/// @return COMPARE enum value

COMPARE compare_values (NodeData_t value1, NodeData_t value2);

#endif

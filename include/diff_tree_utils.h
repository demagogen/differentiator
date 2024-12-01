#ifndef TREE_UTILS_H_
#define TREE_UTILS_H_

#include "diff_tree.h"

/// @brief function for print TREEP_ERROR enum name as string
/// @param required TREE_ERROR enum
/// @return TREE_ERROR enum name string

const char* return_tree_error_enum_name_string(TREE_ERROR enum_param);

/// @brief function for print NODE_RULE enum name as string
/// @param required NODE_RULE enum
/// @return NODE_RULE enum name string

const char* return_node_rule_enum_name_string(NODE_RULE enum_param);

/// @brief function for print NODE_ELEMENT_TYPE enum name as string
/// @param required NODE_ELEMENT_TYPE enum
/// @return NODE_ELEMENT_TYPE enum name string

const char* return_node_element_type_enum_name_string(NODE_ELEMENT_TYPE enum_param);

/// @brief function for print OPERATIONS enum name as string
/// @param required OPERATIONS enum
/// @return OPERATIONS enum name string

const char* return_operation_enum(NodeData_t data);

/// @brief function for read line from buffer
/// @param line, which will be filled
/// @param pointer on line start in buffer
/// @return int error code

int read_line(char** line, char** base_ip);

#endif

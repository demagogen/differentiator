#include "diff_tree_utils.h"

    #define DESCRIPTION_(_error)    \
        case _error: return #_error \

const char* return_tree_error_enum_name_string(TREE_ERROR enum_param)
{
    switch(enum_param)
    {
        DESCRIPTION_ ( TREE_NODE_DED_INSIDE              );
        DESCRIPTION_ ( TREE_DED_INSIDE                   );
        DESCRIPTION_ ( TREE_POISON                       );
        DESCRIPTION_ ( TREE_NONE                         );
        DESCRIPTION_ ( TREE_STRUCT_ALLOCATION_ERROR      );
        DESCRIPTION_ ( TREE_NODE_ALLOCATION_ERROR        );
        DESCRIPTION_ ( TREE_INVALID_CAPACITY             );
        DESCRIPTION_ ( TREE_OVERSIZE                     );
        DESCRIPTION_ ( TREE_MISSING_IP                   );
        DESCRIPTION_ ( TREE_ROOT_ALLOCATION_ERROR        );
        DESCRIPTION_ ( TREE_LEFT_CHILD_ALLOCATION_ERROR  );
        DESCRIPTION_ ( TREE_RIGHT_CHILD_ALLOCATION_ERROR );
        DESCRIPTION_ ( TREE_PARENT_ALLOCATION_ERROR      );
        DESCRIPTION_ ( TREE_NODE_NOT_LEAF                );
        DESCRIPTION_ ( TREE_ERROR_SIDE                   );
        DESCRIPTION_ ( TREE_NULL_NODE                    );
        DESCRIPTION_ ( TREE_NODE_TYPE_ERROR              );

        default:
            return "error print error";
    }
}

const char* return_node_rule_enum_name_string(NODE_RULE enum_param)
{
    switch(enum_param)
    {
        DESCRIPTION_ ( RULE_POISON );
        DESCRIPTION_ ( ROOT        );
        DESCRIPTION_ ( RIGHT       );
        DESCRIPTION_ ( LEFT        );

        default:
            return "error print error";
    }
}

const char* return_node_element_type_enum_name_string(NODE_ELEMENT_TYPE enum_param)
{
    switch(enum_param)
    {
        DESCRIPTION_ ( TYPE_POISON );
        DESCRIPTION_ ( OBJECT      );
        DESCRIPTION_ ( OPERATION   );
        DESCRIPTION_ ( VARIABLE    );

        default:
            return "error print error";
    }
}

const char* return_operations_enum_name_string(OPERATIONS enum_param)
{
    switch(enum_param)
    {
        DESCRIPTION_ ( ADD );
        DESCRIPTION_ ( SUB );
        DESCRIPTION_ ( MUL );
        DESCRIPTION_ ( DIV );
        DESCRIPTION_ ( POW );

        default:
            return "error print error";
    }
}

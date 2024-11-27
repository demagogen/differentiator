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

const char* return_operation_enum(OPERATIONS enum_param)
{
    switch(enum_param)
    {
        case ( ADD    ): return "+";      break;
        case ( SUB    ): return "-";      break;
        case ( MUL    ): return "*";      break;
        case ( DIV    ): return "/";      break;
        case ( POW    ): return "^";      break;
        case ( COS    ): return "cos";    break;
        case ( SIN    ): return "sin";    break;
        case ( TG     ): return "tg";     break;
        case ( CTG    ): return "ctg";    break;
        case ( SH     ): return "sh";     break;
        case ( CH     ): return "ch";     break;
        case ( TH     ): return "th";     break;
        case ( CTH    ): return "cth";    break;
        case ( ARCCOS ): return "arccos"; break;
        case ( ARCSIN ): return "arcsin"; break;
        case ( ARCTG  ): return "arctg";  break;
        case ( ARCCTG ): return "arcctg"; break;
        case ( ARCSH  ): return "arcsh";  break;
        case ( ARCCH  ): return "arcch";  break;
        case ( ARCTH  ): return "arcth";  break;
        case ( ARCCTH ): return "arccth"; break;
        case ( LOG    ): return "log";    break;
        case ( LN     ): return "ln";     break;

        default:
            return "error print error";
    }
}

int read_line(char** line, char** base_ip)
{
    if (!base_ip)
    {
        return -1;
    }

    *line = *base_ip;
    size_t offset = 0;
    while (*(*base_ip + 1) != '{' && *(*base_ip + 1) != '}')
    {
        (*line)[offset] = **base_ip;
        (*base_ip)++;
        offset++;
    }
    *(*line + offset) = '\0';

    return 0;
}

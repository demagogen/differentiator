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

//TODO territory

/// @brief optimize when numerator is zero
/// @param pointer on operation node
/// @return pointer on changed node

NODE* div_numerator_is_zero(NODE* node);

/// @brief optimize when denominator is one
/// @param pointer on operation node
/// @return pointer on changed node

NODE* div_denominator_is_one(NODE* node);

/// @brief optimize when one of factors is zero
/// @param pointer on operation node
/// @return pointer on changed node

NODE* mul_factor_is_zero(NODE* node);

/// @brief optimize when one of factors is one
/// @param pointer on operation node
/// @return pointer on changed node

NODE* mul_factor_is_one(NODE* node);

/// @brief optimize when one of terms is zero
/// @param pointer on operation node
/// @return pointer on changed node

NODE* add_term_is_zero(NODE* node);

/// @brief add two terms in neighboring nodes
/// @param pointer on operation node
/// @param pointer on changed node

NODE* add_two_terms(NODE* node);

/// @brief mul two factors in neighboring nodes
/// @param pointer on operation node
/// @param pointer on changed node

NODE* mul_two_factors(NODE* node);

/// @brief check div numerator on zero
/// @param pointer on operation node
/// @return boolean value

bool check_div_numerator_is_zero(NODE* node);

/// @brief check div denominator on one
/// @param pointer on operation node
/// @return boolean value

bool check_div_denominator_is_one(NODE* node);

/// @brief check mul factors on zero
/// @param pointer on operation node
/// @return boolean value

bool check_mul_factor_is_zero(NODE* node);

/// @brief check mul factors on one
/// @param pointer on operation node
/// @return boolean value

bool check_mul_factor_is_one(NODE* node);

/// @brief check sum terms on zero
/// @param pointer on operation node
/// @return boolean value

bool check_add_term_is_zero(NODE* node);

/// @brief check two neighboring objects
/// @param pointer on operation node
/// @return boolean value

bool check_two_neighboring_objects(NODE* node);

#endif

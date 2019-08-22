#ifndef FDS_FILTER_EVALUATOR_FUNCTIONS_H
#define FDS_FILTER_EVALUATOR_FUNCTIONS_H

#include <libfds.h>
#include "filter.h"

#define DECLARE_FUNC(NAME) \
void \
NAME(struct fds_filter *filter, struct eval_node *node);

DECLARE_FUNC(f_add_uint)
DECLARE_FUNC(f_sub_uint)
DECLARE_FUNC(f_mul_uint)
DECLARE_FUNC(f_div_uint)
DECLARE_FUNC(f_eq_uint)
DECLARE_FUNC(f_ne_uint)
DECLARE_FUNC(f_lt_uint)
DECLARE_FUNC(f_gt_uint)
DECLARE_FUNC(f_le_uint)
DECLARE_FUNC(f_ge_uint)
DECLARE_FUNC(f_cast_uint_to_float)
DECLARE_FUNC(f_cast_uint_to_bool)
DECLARE_FUNC(f_add_int)
DECLARE_FUNC(f_sub_int)
DECLARE_FUNC(f_mul_int)
DECLARE_FUNC(f_div_int)
DECLARE_FUNC(f_eq_int)
DECLARE_FUNC(f_ne_int)
DECLARE_FUNC(f_lt_int)
DECLARE_FUNC(f_gt_int)
DECLARE_FUNC(f_le_int)
DECLARE_FUNC(f_ge_int)
DECLARE_FUNC(f_minus_int)
DECLARE_FUNC(f_cast_int_to_uint)
DECLARE_FUNC(f_cast_int_to_float)
DECLARE_FUNC(f_cast_int_to_bool)
DECLARE_FUNC(f_add_float)
DECLARE_FUNC(f_sub_float)
DECLARE_FUNC(f_mul_float)
DECLARE_FUNC(f_div_float)
DECLARE_FUNC(f_eq_float)
DECLARE_FUNC(f_ne_float)
DECLARE_FUNC(f_lt_float)
DECLARE_FUNC(f_gt_float)
DECLARE_FUNC(f_le_float)
DECLARE_FUNC(f_ge_float)
DECLARE_FUNC(f_minus_float)
DECLARE_FUNC(f_cast_float_to_bool)
DECLARE_FUNC(f_concat_str)
DECLARE_FUNC(f_eq_str)
DECLARE_FUNC(f_ne_str)
DECLARE_FUNC(f_cast_str_to_bool)
DECLARE_FUNC(f_eq_ip_address)
DECLARE_FUNC(f_ne_ip_address)
DECLARE_FUNC(f_eq_mac_address)
DECLARE_FUNC(f_ne_mac_address)
DECLARE_FUNC(f_in_uint)
DECLARE_FUNC(f_in_int)
DECLARE_FUNC(f_in_float)
DECLARE_FUNC(f_in_str)
DECLARE_FUNC(f_in_mac_address)
DECLARE_FUNC(f_in_ip_address)
DECLARE_FUNC(f_cast_list_uint_to_float)
DECLARE_FUNC(f_cast_list_int_to_uint)
DECLARE_FUNC(f_cast_list_int_to_float)
DECLARE_FUNC(f_ip_address_in_trie)
DECLARE_FUNC(f_ip_address_not_in_trie)
DECLARE_FUNC(f_and)
DECLARE_FUNC(f_or)
DECLARE_FUNC(f_not)
DECLARE_FUNC(f_const)
DECLARE_FUNC(f_identifier)
DECLARE_FUNC(f_any)
DECLARE_FUNC(f_exists)
DECLARE_FUNC(f_add_uint)
DECLARE_FUNC(f_eq_uint)
DECLARE_FUNC(f_cast_uint_to_float)
DECLARE_FUNC(f_add_int)
DECLARE_FUNC(f_eq_int)
DECLARE_FUNC(f_minus_int)
DECLARE_FUNC(f_add_float)
DECLARE_FUNC(f_eq_float)
DECLARE_FUNC(f_minus_float)
DECLARE_FUNC(f_concat_str)
DECLARE_FUNC(f_eq_ip_address)
DECLARE_FUNC(f_eq_mac_address)
DECLARE_FUNC(f_and)
DECLARE_FUNC(f_in_uint)
DECLARE_FUNC(f_ip_address_in_trie)
DECLARE_FUNC(f_bitand)
DECLARE_FUNC(f_bitor)
DECLARE_FUNC(f_bitxor)
DECLARE_FUNC(f_bitnot)
DECLARE_FUNC(f_flagcmp)

#undef DECLARE_FUNC

#endif // FDS_FILTER_EVALUATOR_FUNCTIONS_H
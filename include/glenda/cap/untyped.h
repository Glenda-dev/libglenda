#ifndef GLENDA_CAP_UNTYPED_H
#define GLENDA_CAP_UNTYPED_H

#include <glenda/cap.h>
#include <glenda/error.h>

glenda_error_t glenda_untyped_retype(glenda_cap_ptr_t untyped, glenda_cap_type_t type, size_t size_bits, glenda_cap_ptr_t root, size_t node_index, size_t node_depth, size_t node_offset, size_t num_caps);

#endif

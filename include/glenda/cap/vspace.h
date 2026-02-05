#ifndef GLENDA_CAP_VSPACE_H
#define GLENDA_CAP_VSPACE_H

#include <glenda/cap.h>
#include <glenda/error.h>

glenda_error_t glenda_vspace_map(glenda_cap_ptr_t vspace, glenda_cap_ptr_t frame, size_t vaddr, glenda_cap_rights_t rights, size_t cache_policy);
glenda_error_t glenda_vspace_unmap(glenda_cap_ptr_t vspace, size_t vaddr);
glenda_error_t glenda_vspace_map_table(glenda_cap_ptr_t vspace, glenda_cap_ptr_t table, size_t vaddr);

#endif

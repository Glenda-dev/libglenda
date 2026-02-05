#ifndef GLENDA_CAP_CNODE_H
#define GLENDA_CAP_CNODE_H

#include <glenda/cap.h>
#include <glenda/error.h>

glenda_error_t glenda_cnode_mint(glenda_cap_ptr_t cnode, glenda_cap_ptr_t src, glenda_cap_ptr_t dest, glenda_badge_t badge, glenda_cap_rights_t rights);
glenda_error_t glenda_cnode_copy(glenda_cap_ptr_t cnode, glenda_cap_ptr_t src, glenda_cap_ptr_t dest, glenda_cap_rights_t rights);
glenda_error_t glenda_cnode_delete(glenda_cap_ptr_t cnode, glenda_cap_ptr_t slot);
glenda_error_t glenda_cnode_revoke(glenda_cap_ptr_t cnode, glenda_cap_ptr_t slot);
glenda_error_t glenda_cnode_debug_print(glenda_cap_ptr_t cnode);

#endif

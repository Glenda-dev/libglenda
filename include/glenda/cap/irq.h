#ifndef GLENDA_CAP_IRQ_H
#define GLENDA_CAP_IRQ_H

#include <glenda/cap.h>
#include <glenda/error.h>

glenda_error_t glenda_irq_set_notification(glenda_cap_ptr_t irq_handler, glenda_cap_ptr_t notification);
glenda_error_t glenda_irq_ack(glenda_cap_ptr_t irq_handler);

#endif

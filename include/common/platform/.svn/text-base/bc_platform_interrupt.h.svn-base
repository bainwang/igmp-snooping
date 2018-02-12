

#ifndef __bc_platform_interrupt_h__
#define __bc_platform_interrupt_h__

#include "bc_common_defs.h"
#include "bc_modules.h"
#include "bc_err.h"
typedef enum {
	BC_PLATFORM_INTERRUPT_IRQ0 = 0,	
	BC_PLATFORM_INTERRUPT_IRQ1,
	BC_PLATFORM_INTERRUPT_IRQ2,
	BC_PLATFORM_INTERRUPT_IRQ3,
	BC_PLATFORM_INTERRUPT_IRQ4,
	BC_PLATFORM_INTERRUPT_IRQ5,
	BC_PLATFORM_INTERRUPT_IRQ6,
	BC_PLATFORM_INTERRUPT_MAX = 127,
}bc_platform_interrupt_type_e;

/*typedef struct {
	int slot_id;
}bc_platform_interrupt_msg_t;
*/
//typedef int			bc_platform_interrupt_num;
typedef void(*bc_platform_interrupt_notify_cb)(bc_platform_interrupt_type_e*);

extern bc_err_e bc_platform_interrupt
(
	bc_platform_interrupt_type_e interrupt_num
);
extern bc_err_e bc_platform_interrupt_reg
(
	bc_modules_e module_id,
	bc_platform_interrupt_type_e interrupt_num,
	bc_platform_interrupt_notify_cb cb
); 

extern bc_err_e bc_platform_interrupt_unreg
(
	bc_modules_e module_id,
	bc_platform_interrupt_type_e interrupt_num,
	bc_platform_interrupt_notify_cb cb
); 

extern bc_err_e bc_platform_interrupt_init(void);

#endif

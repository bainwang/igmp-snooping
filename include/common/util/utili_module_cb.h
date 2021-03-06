/*******************************************************************************
  [File name]	: utili_blcok.c
  [Author]     	: bain.wang@outlook.com
  [Version]    	: 1.0
  [Date]       	: 2017-04-04
  [Description]	:
	block use
  [Others]     	:
	NULL
  [Function List]:  
    1. ....
    2. ....
  [History]:
	 Date       	Modification 							 Initials
	---------- 	--------------                                        ----------
	2017-04-04  	Created								 bain.wang@outlook.com
*******************************************************************************/

#ifndef __UTILI_MODULE_CB_H__
#define __UTILI_MODULE_CB_H__

#include <string.h>
#include "bc_common_defs.h"
#include "bc_modules.h"
#include "bc_modules_com_para.h"
#include "bc_err.h"

typedef struct {
	void *cb;
	
	bc_uint32 in_cnt;
	bc_uint32 out_cnt;

	void *data;
} utili_module_cb_node_t;

typedef struct {
	bc_modules_e module_id;
	bc_char name[BC_MODULE_NAME_LENGTH];
	bc_uint32 data_size;

	utili_module_cb_node_t *nodes;
} utili_module_cb_t;

#define UTILI_MODULE_MAX_DATA_SIZE (1*1024)

extern bc_err_e utili_module_cb_init(utili_module_cb_t *module_db, bc_modules_e module_id, bc_char desc[BC_MODULE_NAME_LENGTH], bc_uint32 data_size);

extern bc_err_e utili_module_cb_reg(utili_module_cb_t *module_db, bc_modules_e module_id, void *cb, void *data);
extern bc_err_e utili_module_cb_dereg(utili_module_cb_t *module_db, bc_modules_e module_id);

typedef void (*utili_module_cb_dump_title)(void);
typedef void (*utili_module_cb_dump_line)(void* data);
extern void utili_module_cb_dump(utili_module_cb_t *module_db, utili_module_cb_dump_title title, utili_module_cb_dump_line line);

#define utili_module_cb_scan_start(module_db, cb, cb_type, data_p, data_type) \
				do \
				{ \
					int utili_module_cb_i; \
					for (utili_module_cb_i = 0; utili_module_cb_i < BC_MODULES_NUM; utili_module_cb_i++) \
					{ \
						if ((module_db)->nodes[utili_module_cb_i].cb == NULL) \
							continue; \
						cb = (cb_type)((module_db)->nodes[utili_module_cb_i].cb); \
						if ((module_db)->data_size != 0) \
							data_p = (data_type)((module_db)->nodes[utili_module_cb_i].data);

#define utili_module_cb_scan_in_inc(module_db) (module_db)->nodes[utili_module_cb_i].in_cnt++;

#define utili_module_cb_scan_out_inc(module_db) (module_db)->nodes[utili_module_cb_i].out_cnt++;

#define utili_module_cb_scan_end(module_db) \
					} \
				} while (0) \


#endif


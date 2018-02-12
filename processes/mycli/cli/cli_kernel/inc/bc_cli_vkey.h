
#ifndef __BC_CLI_VKEY_H__
#define __BC_CLI_VKEY_H__

/*
 * ASCII code : keystroke
 */
/*
 * jash law , 2016-05-22 ,	
 *
 * keys: BACKSPACE, DEL
 */
#define  CLI_VKEY_BACKSPACE 	0x7F
#define  CLI_VKEY_DEL       	0xFF

#define  CLI_VKEY_TAB       	0x09
#define  CLI_VKEY_FUN4         	0x0c
#define  CLI_VKEY_CR        	0x0d
#define  CLI_VKEY_ESC       	0x1b
#define  CLI_VKEY_SPACE     	0x20
#define  CLI_VKEY_BRACKET   	0x5b

#define  CLI_VKEY_LOWERCASE_Q  	0x71

#define  CLI_VKEY_LF 			0x0a
#define  CLI_VKEY_CTRL_J 		0x0a
#define  CLI_VKEY_CTRL_ENTER 	0x0a

#define  CLI_VKEY_CTRL_A 		0x01
#define  CLI_VKEY_CTRL_B 		0x02
#define  CLI_VKEY_CTRL_C 		0x03
#define  CLI_VKEY_CTRL_D 		0x04
#define  CLI_VKEY_CTRL_E 		0x05
#define  CLI_VKEY_CTRL_H 		0x08
#define  CLI_VKEY_CTRL_I 		0x09
#define  CLI_VKEY_CTRL_K 		0x0b
#define  CLI_VKEY_CTRL_L 		0x0c
#define  CLI_VKEY_CTRL_M 		0x0D
#define  CLI_VKEY_CTRL_N 		0x0E
#define  CLI_VKEY_CTRL_P 		0x10
#define  CLI_VKEY_CTRL_R 		0x12
#define  CLI_VKEY_CTRL_U 		0x15
#define  CLI_VKEY_CTRL_V 		0x16
#define  CLI_VKEY_CTRL_X 		0x18
#define  CLI_VKEY_CTRL_Z 		0x1a


#define CLI_VKEY_EDIT_KEY_BASE 	(0x100L)

/* Function Keys
ESC[11~     F1
ESC[12~     F2
ESC[13~     F3
ESC[14~     F4
ESC[16~     F5
ESC[17~     F6
ESC[18~     F7
ESC[19~     F8

ESC[20~     F9
ESC[21~     F10
ESC[23~     F11
ESC[24~     F12
*/
#define  CLI_VKEY_F1     		(CLI_VKEY_EDIT_KEY_BASE + 11L)
#define  CLI_VKEY_F2     		(CLI_VKEY_EDIT_KEY_BASE + 12L)
#define  CLI_VKEY_F3     		(CLI_VKEY_EDIT_KEY_BASE + 13L)
#define  CLI_VKEY_F4     		(CLI_VKEY_EDIT_KEY_BASE + 14L)

#define  CLI_VKEY_F5     		(CLI_VKEY_EDIT_KEY_BASE + 15L)
#define  CLI_VKEY_F6     		(CLI_VKEY_EDIT_KEY_BASE + 17L)
#define  CLI_VKEY_F7     		(CLI_VKEY_EDIT_KEY_BASE + 18L)
#define  CLI_VKEY_F8     		(CLI_VKEY_EDIT_KEY_BASE + 19L)

#define  CLI_VKEY_F9     		(CLI_VKEY_EDIT_KEY_BASE + 20L)
#define  CLI_VKEY_F10    		(CLI_VKEY_EDIT_KEY_BASE + 21L)
#define  CLI_VKEY_F11    		(CLI_VKEY_EDIT_KEY_BASE + 23L)
#define  CLI_VKEY_F12    		(CLI_VKEY_EDIT_KEY_BASE + 24L)

/*
 * jash law , 2016-05-22 ,  
 *
 * Edit keys
 */
#define  CLI_VKEY_INSERT 		(CLI_VKEY_EDIT_KEY_BASE + 0x02L)
#define  CLI_VKEY_HOME   		(CLI_VKEY_EDIT_KEY_BASE + 0x01L)
#define  CLI_VKEY_PAGEUP 		(CLI_VKEY_EDIT_KEY_BASE + 0x05L)
#define  CLI_VKEY_DELETE 		(CLI_VKEY_EDIT_KEY_BASE + 0x03L)
#define  CLI_VKEY_END    		(CLI_VKEY_EDIT_KEY_BASE + 0x04L)
#define  CLI_VKEY_PAGEDOWN 		(CLI_VKEY_EDIT_KEY_BASE + 0x06L)

/*
 * The definition of Cursor movement
 */
#define  CLI_VKEY_LEFT   		(CLI_VKEY_EDIT_KEY_BASE + 0x44L)
#define  CLI_VKEY_RIGHT  		(CLI_VKEY_EDIT_KEY_BASE + 0x43L)
#define  CLI_VKEY_UP     		(CLI_VKEY_EDIT_KEY_BASE + 0x41L)
#define  CLI_VKEY_DOWN   		(CLI_VKEY_EDIT_KEY_BASE + 0x42L)

/* Other keys */
#define  CLI_VKEY_OP     		(CLI_VKEY_EDIT_KEY_BASE + 0x50L)
#define  CLI_VKEY_OQ     		(CLI_VKEY_EDIT_KEY_BASE + 0x51L)
#define  CLI_VKEY_OR     		(CLI_VKEY_EDIT_KEY_BASE + 0x52L)
#define  CLI_VKEY_OS     		(CLI_VKEY_EDIT_KEY_BASE + 0x53L)

/*
 * The definition for I/O event
 */
#define CLI_VKEY_IO_CLOSED  	(-1)
/*this value should be same as UTL_COM_CONSOLE_TIMEOUT utl_com.h, define as following to avoid duplicate with JAPAN code. */
#define CLI_VKEY_IO_TIMEOUT 	(-1282)
#define CLI_VKEY_IO_NOACTION 	(-1283)
#define CLI_VKEY_IO_EXITCMD  	(-1284)
#define CLI_VKEY_IO_NOTIFY  	(-1285)
#define CLI_VKEY_IO_WRONGVALUE 	(-5)



#endif /* __BC_CLI_VKEY_H__ */


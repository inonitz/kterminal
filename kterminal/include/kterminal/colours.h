#ifndef __KTERM_TERMINAL_EMULATOR_COLOUR_DEFINITION__
#define __KTERM_TERMINAL_EMULATOR_COLOUR_DEFINITION__

/*
    Force a single implementation of all kernel console colours
    If someone defines these macros there will be issues
*/
#ifdef KTERM_COLOUR_RGB
#	error "Macro KTERM_COLOUR_BLACK Already Defined!"
#endif
#ifdef KTERM_COLOUR_BGR
#	error "Macro KTERM_COLOUR_WHITE Already Defined!"
#endif
#ifdef KTERM_COLOUR_BLACK
#	error "Macro KTERM_COLOUR_BLACK Already Defined!"
#endif
#ifdef KTERM_COLOUR_WHITE
#	error "Macro KTERM_COLOUR_WHITE Already Defined!"
#endif
#ifdef KTERM_COLOUR_RED
#	error "Macro KTERM_COLOUR_RED Already Defined!"
#endif
#ifdef KTERM_COLOUR_BRIGHT_RED
#	error "Macro KTERM_COLOUR_BRIGHT_RED Already Defined!"
#endif
#ifdef KTERM_COLOUR_ORANGE
#	error "Macro KTERM_COLOUR_ORANGE Already Defined!"
#endif
#ifdef KTERM_COLOUR_LIME
#	error "Macro KTERM_COLOUR_LIME Already Defined!"
#endif
#ifdef KTERM_COLOUR_BLUE
#	error "Macro KTERM_COLOUR_BLUE Already Defined!"
#endif
#ifdef KTERM_COLOUR_YELLOW
#	error "Macro KTERM_COLOUR_YELLOW Already Defined!"
#endif
#ifdef KTERM_COLOUR_CYAN
#	error "Macro KTERM_COLOUR_CYAN Already Defined!"
#endif
#ifdef KTERM_COLOUR_MAGENTA
#	error "Macro KTERM_COLOUR_MAGENTA Already Defined!"
#endif
#ifdef KTERM_COLOUR_SILVER
#	error "Macro KTERM_COLOUR_SILVER Already Defined!"
#endif
#ifdef KTERM_COLOUR_GRAY
#	error "Macro KTERM_COLOUR_GRAY Already Defined!"
#endif
#ifdef KTERM_COLOUR_MAROON
#	error "Macro KTERM_COLOUR_MAROON Already Defined!"
#endif
#ifdef KTERM_COLOUR_OLIVE
#	error "Macro KTERM_COLOUR_OLIVE Already Defined!"
#endif
#ifdef KTERM_COLOUR_GREEN
#	error "Macro KTERM_COLOUR_GREEN Already Defined!"
#endif
#ifdef KTERM_COLOUR_NEON_GREEN
#	error "Macro KTERM_COLOUR_NEON_GREEN Already Defined!"
#endif
#ifdef KTERM_COLOUR_PURPLE
#	error "Macro KTERM_COLOUR_PURPLE Already Defined!"
#endif
#ifdef KTERM_COLOUR_TEAL
#	error "Macro KTERM_COLOUR_TEAL Already Defined!"
#endif
#ifdef KTERM_COLOUR_NAVY
#	error "Macro KTERM_COLOUR_NAVY Already Defined!"
#endif


#define KTERM_COLOUR_RGB(r, g, b) (uint32_t)(r << 24 + g << 16 + b << 8)
#define KTERM_COLOUR_BGR(r, g, b) (uint32_t)(b << 24 + g << 16 + r << 8) 
//      Color      	 RES R  G  B   (little-endian BGR format)
#define KTERM_COLOUR_BLACK      0x00000000	
#define KTERM_COLOUR_WHITE	    0x00FFFFFF
#define KTERM_COLOUR_RED		0x00FF0000
#define KTERM_COLOUR_BRIGHT_RED 0x00ff1439
#define KTERM_COLOUR_ORANGE     0x00FF6600
#define KTERM_COLOUR_LIME	   	0x0000FF00
#define KTERM_COLOUR_BLUE	   	0x000000FF
#define KTERM_COLOUR_YELLOW	    0x00FFFF00
#define KTERM_COLOUR_CYAN 	    0x0000FFFF
#define KTERM_COLOUR_MAGENTA    0x00FF00FF
#define KTERM_COLOUR_SILVER	    0x00C0C0C0
#define KTERM_COLOUR_GRAY	   	0x00808080
#define KTERM_COLOUR_MAROON	    0x00800000
#define KTERM_COLOUR_OLIVE	    0x00808000
#define KTERM_COLOUR_GREEN	    0x00008000
#define KTERM_COLOUR_NEON_GREEN 0x0039ff14
#define KTERM_COLOUR_PURPLE	    0x00800080
#define KTERM_COLOUR_TEAL	    0x00008080
#define KTERM_COLOUR_NAVY	    0x00000080


#endif /* __KTERM_TERMINAL_EMULATOR_COLOUR_DEFINITION__ */
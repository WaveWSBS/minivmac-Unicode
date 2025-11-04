/*
	text_utf8_sdl.h

	Utility helpers for rendering UTF-8 text into the Mini vMac
	control/message overlay buffers using SDL_ttf.
*/

#ifndef TEXT_UTF8_SDL_H
#define TEXT_UTF8_SDL_H

/* Prefer real project definitions when available. */
#if !defined(SYSDEPNS_H) && (defined(AllFiles) || (defined(__has_include) && __has_include("SYSDEPNS.h")))
#include "SYSDEPNS.h"
#endif

/* Fallback typedefs/macros for editors without generated headers. */
#if !defined(SYSDEPNS_H) && !defined(TEXT_UTF8_SDL_FALLBACK_TYPES)
#define TEXT_UTF8_SDL_FALLBACK_TYPES 1
typedef unsigned char ui3b;
typedef unsigned int ui4r;
typedef unsigned char *ui3p;
typedef int blnr;
#ifndef trueblnr
#define trueblnr 1
#define falseblnr 0
#endif
#ifndef GLOBALFUNC
#define GLOBALFUNC extern
#endif
#ifndef GLOBALPROC
#define GLOBALPROC extern
#endif
#endif /* TEXT_UTF8_SDL_FALLBACK_TYPES */

#ifndef EnableUnicodeOverlay
#define EnableUnicodeOverlay 0
#endif

#if EnableUnicodeOverlay

GLOBALFUNC blnr TextUtf8_Init(const char *font_path, int pixel_size);
GLOBALPROC TextUtf8_Quit(void);

/* Measure the pixel width of a UTF-8 string. Returns -1 on error. */
GLOBALFUNC si4b TextUtf8_MeasureWidth(const char *utf8);

GLOBALFUNC si4b TextUtf8_DrawLineToCntrlBuff(
	int x_px,
	int y_px,
	const char *utf8,
	ui4r fg_rgb,
	ui4r bg_rgb,
	int screen_depth,
	blnr use_color_mode,
	ui4r mono_stride,
	ui4r color_stride,
	ui3p cntrl_buf,
	ui4r max_width_px,
	ui4r screen_width_px,
	ui4r screen_height_px);

#endif /* EnableUnicodeOverlay */

#endif /* TEXT_UTF8_SDL_H */

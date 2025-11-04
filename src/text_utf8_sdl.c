#include "text_utf8_sdl.h"

#if EnableUnicodeOverlay

#include <SDL.h>
#include <SDL_ttf.h>
#include <string.h>

static blnr g_text_utf8_ttf_inited = falseblnr;
static TTF_Font *g_text_utf8_font = NULL;

GLOBALFUNC blnr TextUtf8_Init(const char *font_path, int pixel_size)
{
	if (NULL == font_path) {
		return falseblnr;
	}

	if (!g_text_utf8_ttf_inited) {
		if (TTF_Init() == -1) {
			return falseblnr;
		}
		g_text_utf8_ttf_inited = trueblnr;
	}

	if (NULL != g_text_utf8_font) {
		TTF_CloseFont(g_text_utf8_font);
		g_text_utf8_font = NULL;
	}

	g_text_utf8_font = TTF_OpenFont(font_path, pixel_size);
	if (NULL == g_text_utf8_font) {
		return falseblnr;
	}

	/* Enable hinting for better clarity */
	TTF_SetFontHinting(g_text_utf8_font, TTF_HINTING_NORMAL);

	return trueblnr;
}

GLOBALPROC TextUtf8_Quit(void)
{
	if (NULL != g_text_utf8_font) {
		TTF_CloseFont(g_text_utf8_font);
		g_text_utf8_font = NULL;
	}

	if (g_text_utf8_ttf_inited) {
		TTF_Quit();
		g_text_utf8_ttf_inited = falseblnr;
	}
}

GLOBALFUNC si4b TextUtf8_MeasureWidth(const char *utf8)
{
	if (NULL == utf8 || NULL == g_text_utf8_font) {
		return -1;
	}

	int w = 0, h = 0;
	if (TTF_SizeUTF8(g_text_utf8_font, utf8, &w, &h) != 0) {
		return -1;
	}

	return (si4b)w;
}

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
	ui4r screen_height_px)
{
	(void)bg_rgb;
	(void)color_stride;

	if (NULL == utf8 || NULL == cntrl_buf) {
		return -1;
	}

	if (NULL == g_text_utf8_font) {
		return -1;
	}

	if (use_color_mode || (screen_depth != 0)) {
		return -2;
	}

	if (mono_stride == 0 || max_width_px == 0) {
		return 0;
	}

	SDL_Color fg;
	fg.r = (Uint8)((fg_rgb >> 16) & 0xFF);
	fg.g = (Uint8)((fg_rgb >> 8) & 0xFF);
	fg.b = (Uint8)(fg_rgb & 0xFF);
	fg.a = 255;

	SDL_Surface *surface = TTF_RenderUTF8_Blended(g_text_utf8_font, utf8, fg);
	if (NULL == surface) {
		return -1;
	}

	int draw_w = surface->w;
	int draw_h = surface->h;

	if (draw_w > (int)max_width_px) {
		draw_w = (int)max_width_px;
	}

	if (draw_w <= 0 || draw_h <= 0) {
		SDL_FreeSurface(surface);
		return 0;
	}

	if ((int)screen_width_px <= 0) {
		screen_width_px = mono_stride * 8;
	}
	if ((int)screen_height_px <= 0) {
		screen_height_px = 32767;
	}

	if (x_px >= (int)screen_width_px || y_px >= (int)screen_height_px) {
		SDL_FreeSurface(surface);
		return 0;
	}

	Uint8 *src = (Uint8 *)surface->pixels;
	int pitch = surface->pitch;
	int bpp = surface->format->BytesPerPixel;

	for (int dy = 0; dy < draw_h; ++dy) {
		int dest_y = y_px + dy;
		if (dest_y < 0 || dest_y >= (int)screen_height_px) {
			continue;
		}

		Uint8 *src_row = src + dy * pitch;

		for (int dx = 0; dx < draw_w; ++dx) {
			int dest_x = x_px + dx;
			if (dest_x < 0 || dest_x >= (int)screen_width_px) {
				continue;
			}

			Uint8 alpha;
			if (bpp == 4) {
				alpha = src_row[dx * 4 + 3];
			} else if (bpp == 1) {
				alpha = src_row[dx];
			} else {
				alpha = 0xFF;
			}

			ui3p dest_byte = cntrl_buf + dest_y * mono_stride + (dest_x >> 3);
			ui3b mask = (ui3b)(1 << (7 - (dest_x & 7)));

			/* clear background to white */
			*dest_byte &= (ui3b)(~mask);

			/* Use higher threshold for better anti-aliasing (128 = 50% opacity) */
			if (alpha > 128) {
				*dest_byte |= mask;
			}
		}
	}

	SDL_FreeSurface(surface);

	return draw_w;
}

#endif /* EnableUnicodeOverlay */

Unicode Overlay (SDL_ttf) — Usage Notes

Overview
- Adds UTF‑8 text rendering to the Control/Message overlays only. The emulated Mac screen remains unchanged.
- Rendering path uses SDL_ttf/FreeType to draw into `CntrlDisplayBuff`, then reuses the existing dirty‑rect pipeline.

Status & Limits
- Implemented for the SDL2 frontend.
- Currently enabled by compile‑time macro `EnableUnicodeOverlay`.
- Monochrome overlay path supported (UseColorMode off). Color overlay alpha blending can be added later.

Enable at Build Time
- Define macro `EnableUnicodeOverlay=1` for the build of the SDL2 target. Examples:
  - Make/C: add `-DEnableUnicodeOverlay=1` to your CFLAGS.
  - If you maintain per‑platform config headers, set `#define EnableUnicodeOverlay 1` there before including `CONTROLM.h`.
- Link SDL_ttf (in addition to SDL2):
  - Linux/macOS (typical): `-lSDL2_ttf -lSDL2`
  - Make sure your compiler can find SDL_ttf headers and libs.

Font Loading
- Default search order:
  1) Environment variable `MINIVMAC_FONT` (absolute path to a .otf/.ttf)
  2) Program directory file `unifont.otf`
- Recommended fonts for Chinese/Japanese/Korean:
  - Unifont (OTF/TTF)
  - Noto Sans/Serif CJK, Source Han Sans/Serif

Runtime Placement Examples
- Put your font next to the executable as `unifont.otf`.
- Or set environment variable before launching:
  - macOS/Linux: `export MINIVMAC_FONT="/absolute/path/yourfont.otf"`
  - Windows (PowerShell): `$env:MINIVMAC_FONT = "C:\\path\\to\\yourfont.otf"`

Where It Renders
- Only overlay UI (Control Mode, messages) strings render via SDL_ttf.
- Overlay frame borders and icons still use the built‑in 8×16 cell font to preserve original style.

Known Behaviors
- Without `EnableUnicodeOverlay=1`, the feature is compiled out and the original cell font pipeline is used.
- If the chosen font lacks a glyph, SDL_ttf will render an empty box; pick a font with wider CJK coverage.

Files Touched
- `src/text_utf8_sdl.h`, `src/text_utf8_sdl.c`: SDL_ttf wrapper.
- `src/CONTROLM.h`: overlay string expansion + conditional UTF‑8 drawing.
- `src/OSGLUSD2.c`: font init/quit; default filename `unifont.otf`.

Next Steps (Optional)
- Add color‑overlay alpha blending path (UseColorMode on).
- Add fallback font chain (load multiple fonts, try in order).
- Extend `;` substitution mapping as needed for more symbols.


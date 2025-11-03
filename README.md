Mini vMac (SDL2 + Unicode Overlay)

This branch adds UTF‑8 text rendering (SDL_ttf/FreeType) to the Mini vMac SDL2 frontend for the Control/Message overlay UI only. The emulated Macintosh display remains unchanged.

- Goal: Unicode text (e.g., Chinese) in the overlay UI without modifying the emulated Mac OS.
- Scope: Only overlay text is affected; frame borders and icons still use the built‑in 8×16 cell font.


Features
- UTF‑8 overlay rendering: Draws strings into `CntrlDisplayBuff` via SDL_ttf, then uses the existing dirty‑rect pipeline to present via SDL2.
- Font search order:
  1) Environment variable `MINIVMAC_FONT` (absolute path to .otf/.ttf)
  2) `unifont.otf` next to the executable
- Language header override:
  - Setup generates `cfg/STRCONST.h` (English by default). For SDL2 builds, define `STRCONST_OVERRIDE` to force another header, e.g., `STRCONZHT.h` for Traditional Chinese.
- Stability: The “fast texture copy” path is disabled (`SDLUseFastTextureCopy=0`) to avoid `UpdateBWDepth5Copy` crashes on some platforms (e.g., Apple Silicon). The renderer uses a safe per‑pixel path.


Layout & Key Files
- `Makefile.sdl`: SDL2/SDL_ttf build script (not overwritten by setup). It enables:
  - `-DEnableUnicodeOverlay=1`
  - `-DSTRCONST_OVERRIDE="<header>"`, controlled by `LANG_HEADER` (see Build section)
- `src/text_utf8_sdl.h`, `src/text_utf8_sdl.c`: SDL_ttf wrapper and UTF‑8 renderer.
- `src/STRCONZHT.h`: Traditional Chinese overlay strings (overrides English).
- Modified core files:
  - `src/CONTROLM.h`: Integrates UTF‑8 drawing; expands `^`/`;` substitutions; guards for 1‑bit builds where `UseColorMode` may be undefined.
  - `src/OSGLUSD2.c`: Font init/quit (uses `unifont.otf`/`MINIVMAC_FONT`), `STRCONST_OVERRIDE` include hook, disables the fragile fast path.
- Docs: `UNICODE_OVERLAY.md` (usage notes and limitations).

Note: `cfg/` (generated headers), `bld/` (objects), `minivmac` (binary), and `gen_config.sh` are build artifacts and generally should not be versioned.


Build (macOS, SDL2 frontend)

Prerequisites
- Install via Homebrew:
  - `brew install sdl2 sdl2_ttf`

Generate config (required once per variant)
```
./setup/minivmac-setup -t xgen -api sd2 > gen_config.sh
sh gen_config.sh
```
Important: The command above rewrites the root `Makefile` and `cfg/`. Use `Makefile.sdl` for SDL2 builds in this branch.

Compile (Traditional Chinese strings enabled by default)
```
make -f Makefile.sdl clean
make -f Makefile.sdl -j4
```
Switch language without editing `cfg/STRCONST.h`
```
make -f Makefile.sdl LANG_HEADER=STRCNENG.h -j4   # English
make -f Makefile.sdl LANG_HEADER=STRCONZHT.h -j4  # Traditional Chinese (default)
```

Run
```
# Choose a font (either option):
# 1) Place unifont.otf next to the executable
# 2) Or set an absolute path via env var
export MINIVMAC_FONT="/absolute/path/unifont.otf"

./minivmac
```


Usage
- Overlay strings show in Control Mode (hold the control key, or platform‑specific shortcut).
- Currently supports monochrome overlay only (UseColorMode off). Color overlay alpha blending can be added later.
- Language is selected at build time via `STRCONST_OVERRIDE`/`LANG_HEADER` and does not depend on `cfg/STRCONST.h` (which setup resets to English).


Known Limitations / TODO
- Color overlay is not implemented: when UseColorMode is on or screen depth != 1‑bit, `TextUtf8_DrawLineToCntrlBuff` returns `-2` and the code falls back to ASCII.
- Performance: per‑pixel path only; the fast path may be reconsidered when pitch/dimensions are guaranteed to match.
- Missing glyphs: if the chosen font lacks a glyph, SDL_ttf may draw empty boxes. Prefer wide‑coverage fonts such as Unifont or Noto/Source Han.


Troubleshooting
- “SDL2/SDL.h not found” during build: ensure `sdl2` is installed and use `make -f Makefile.sdl`; the root `Makefile` is not the SDL2 variant.
- Historical crash: `UpdateBWDepth5Copy` segfaults are avoided by disabling the fast texture copy path.
- “The video driver did not add any displays”: often a headless environment—run from a regular macOS Terminal with GUI access.
- Linker warning “ignoring duplicate libraries: '-lSDL2'”: safe to ignore; `Makefile.sdl` dedupes in most cases.


Version Control Suggestions (.gitignore)
- Ignore: `cfg/`, `bld/`, `minivmac`, `gen_config.sh`, `unifont.otf` (large/third‑party asset).
- Track: `Makefile.sdl`, `UNICODE_OVERLAY.md`, `src/text_utf8_sdl.*`, `src/STRCONZHT.h`, and minimal source modifications.


License
- Mini vMac and its build system are licensed under GNU GPL v2 (see `COPYING.txt`).
- New/modified source files in this branch inherit the same license unless stated otherwise.
- Fonts: e.g., `unifont.otf` is copyrighted by its authors; follow its license. Prefer documenting download instructions instead of storing fonts in the repo.


Acknowledgements
- Paul C. Pratt and Mini vMac contributors.
- SDL2, SDL_ttf/FreeType, HarfBuzz and the wider OSS community.




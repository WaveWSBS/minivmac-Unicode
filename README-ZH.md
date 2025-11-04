Mini vMac（SDL2 + Unicode 疊加層）

本分支在 Mini vMac（經典 Mac 模擬器）的 SDL2 前端之上，加入基於 SDL_ttf/FreeType 的 UTF‑8 文字渲染，僅用於「控制模式／訊息框」等疊加層（overlay）介面。被仿真的 Mac 畫面維持原樣（位圖／系統字形不變）。

- 目標：在不更動被仿真的 Mac OS 的前提下，讓叢集 UI 支援 Unicode（如中文）。
- 範圍：只影響疊加層文字；邊框與圖示仍使用內建 8×16 單元格字形。


功能總覽
- UTF‑8 疊加層渲染：透過 SDL_ttf 將字串繪製到 `CntrlDisplayBuff`，並沿用既有「髒矩形」刷新管線輸出到 SDL2 視窗。
- 字型查找順序：
  1) 環境變數 `MINIVMAC_FONT` 指向的絕對路徑（.otf／.ttf）
  2) 與可執行檔同目錄的 `unifont.otf`
- 語言覆蓋機制：
  - setup 會產生 `cfg/STRCONST.h`（預設英文）。SDL2 建置時可經由 `STRCONST_OVERRIDE` 強制包含其他標頭，例如繁體中文 `STRCONZHT.h`。
- 穩定性：
  - 關閉 SDL 紋理的「快速拷貝」路徑（`SDLUseFastTextureCopy=0`），統一走逐像素安全路徑，以避免在 Apple Silicon 等環境觸發 `UpdateBWDepth5Copy` 異常。


目錄與關鍵檔案
- `Makefile.sdl`：SDL2/SDL_ttf 建置腳本（不會被 setup 覆蓋）。啟用：
  - `-DEnableUnicodeOverlay=1` 打開疊加層 Unicode
  - `-DSTRCONST_OVERRIDE="<header>"` 指定語言標頭，配合 `LANG_HEADER` 變數（見下方建置章節）
- `src/text_utf8_sdl.h`, `src/text_utf8_sdl.c`：SDL_ttf 封裝與 UTF‑8 繪製實作。
- `src/STRCONZHT.h`：繁體中文疊加層字串表（在英文基礎上覆寫）。
- 已修改檔：
  - `src/CONTROLM.h`：整合 UTF‑8 繪製；展開 `^`／`;` 替代符；在 1‑bit 建置下容忍 `UseColorMode` 未定義。
  - `src/OSGLUSD2.c`：字型初始化／釋放（預設 `unifont.otf`／`MINIVMAC_FONT`）；加入 `STRCONST_OVERRIDE` 鉤子；停用易碎的快速路徑。
- 文件：`UNICODE_OVERLAY.md`（使用說明與限制）。

提示：`cfg/`（產生的標頭）、`bld/`（中介檔）、`minivmac`（可執行檔）、`gen_config.sh` 均屬建置產物，通常不建議納入版控。


建置（macOS，SDL2 前端）

前置
- 建議以 Homebrew 安裝：
  - `brew install sdl2 sdl2_ttf`

全新 clone 快速開始
```
# 0) 若倉庫未提交 setup 生成器，可自行重建
cc -O2 -o setup/minivmac-setup setup/tool.c

# 1) 產生 SDL2 目標的設定
./setup/minivmac-setup -t xgen -api sd2 > gen_config.sh
sh gen_config.sh

# 2) 使用 SDL2 專用的 Makefile 建置
make -f Makefile.sdl -j4
```

產生設定（細節說明）
```
./setup/minivmac-setup -t xgen -api sd2 > gen_config.sh
sh gen_config.sh
```
注意：上述命令會重寫根目錄 `Makefile` 與 `cfg/`。本分支請使用 `Makefile.sdl` 進行建置。

編譯（預設啟用繁體中文字串）
```
make -f Makefile.sdl clean
make -f Makefile.sdl -j4
```
不修改 `cfg/STRCONST.h` 的情況下切換語言：
```
make -f Makefile.sdl LANG_HEADER=STRCNENG.h -j4   # 英文
make -f Makefile.sdl LANG_HEADER=STRCONZHT.h -j4  # 繁體（預設）
```

執行
```
# 選擇字型（二選一）
# 1) 將 unifont.otf 放在可執行檔同目錄
# 2) 或設定環境變數為絕對路徑
export MINIVMAC_FONT="/絕對/路徑/unifont.otf"

./minivmac
```


使用說明
- 疊加層文字顯示於控制模式（按住 Control 鍵，或依平台快捷鍵）。
- 目前僅支援單色疊加層（UseColorMode 關閉）。彩色疊加層的 alpha 混合尚未實作。
- 顯示語言：於建置時以 `STRCONST_OVERRIDE`／`LANG_HEADER` 指定，與 `cfg/STRCONST.h` 內容無關（setup 仍會把它重寫回英文）。


已知限制／TODO
- 彩色疊加層：`TextUtf8_DrawLineToCntrlBuff` 在 UseColorMode 開啟或螢幕深度非 1‑bit 時回傳 `-2`，並退回 ASCII 路徑。未來可加入 16／32bpp 的 alpha 混合。
- 效能：目前統一走逐像素路徑；在確認 pitch／尺寸完全匹配後，可再評估開啟快速路徑的條件。
- 缺字：若字型缺字，SDL_ttf 可能顯示空框；建議使用覆蓋面較廣的字型（如 Unifont、Noto／思源系列）。


疑難排解
- 編譯找不到 `SDL2/SDL.h`：確認已安裝 `sdl2`，並使用 `make -f Makefile.sdl`；根目錄 `Makefile` 非 SDL2 版本。
- 歷史崩潰：`UpdateBWDepth5Copy` 的位址錯誤已藉由停用快速路徑避開。
- 顯示裝置錯誤 “The video driver did not add any displays”：多見於無 GUI 環境，請從一般 macOS Terminal 執行。
- 連結警告 “ignoring duplicate libraries: '-lSDL2'”：可忽略；`Makefile.sdl` 已儘量去除重複。


版控建議（.gitignore）
- 忽略：`cfg/`, `bld/`, `minivmac`, `gen_config.sh`, `unifont.otf`（體積大且第三方授權）。
- 追蹤：`Makefile.sdl`, `UNICODE_OVERLAY.md`, `src/text_utf8_sdl.*`, `src/STRCONZHT.h`，以及對既有原始碼的最小修改。


授權
- Mini vMac 與其建置系統遵循 GNU GPL v2（見 `COPYING.txt`）。
- 本分支新增／修改之原始碼檔，除另行註明，承襲同一授權。
- 字型：示例的 `unifont.otf` 版權屬原作者所有，請遵循其授權條款；建議以提供下載指引替代將字型納入版本庫。


致謝
- Mini vMac 作者 Paul C. Pratt 與貢獻者。
- SDL2、SDL_ttf/FreeType、HarfBuzz 與廣大開源社群。

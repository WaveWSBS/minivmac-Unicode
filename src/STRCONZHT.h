/*
	STRCONZHT.h

	Traditional Chinese string constants for Mini vMac overlay UI
	(extends the English baseline and overrides selected entries).
*/

#include "STRCNENG.h"

/* ---- 基本訊息 ---- */
#undef kStrAboutTitle
#define kStrAboutTitle "關於"
#undef kStrAboutMessage
#define kStrAboutMessage "要顯示此程式的相關資訊，請使用 ^p 控制模式中的 ;]A;} 指令。若想了解控制模式，請參閱 ;[更多指令;ll;{，位於 ;[特殊;{ 功能表。"

#undef kStrMoreCommandsTitle
#define kStrMoreCommandsTitle "在 ^p 控制模式中還有更多指令。"
#undef kStrMoreCommandsMessage
#define kStrMoreCommandsMessage "要進入控制模式，請按住 ;]^c;} 鍵。當你放開 ;]^c;} 鍵時，即離開控制模式。在控制模式中輸入 ;]H;} 可列出可用指令。"

#undef kStrTooManyImagesTitle
#define kStrTooManyImagesTitle "磁碟映像過多"
#undef kStrTooManyImagesMessage
#define kStrTooManyImagesMessage "無法掛載那麼多磁碟映像。請嘗試退出一個。"

#undef kStrImageInUseTitle
#define kStrImageInUseTitle "磁碟映像使用中"
#undef kStrImageInUseMessage
#define kStrImageInUseMessage "無法掛載該磁碟映像，因為它已被其他應用程式使用，或已在 ^p 中開啟。"

#undef kStrOutOfMemTitle
#define kStrOutOfMemTitle "記憶體不足"
#undef kStrOutOfMemMessage
#define kStrOutOfMemMessage "可用記憶體不足，無法啟動 ^p。"

#undef kStrNoROMTitle
#define kStrNoROMTitle "找不到 ROM 映像"
#undef kStrNoROMMessage
#define kStrNoROMMessage "找不到 ROM 檔案 ;[^r;{。欲知詳細資訊，請參閱：;[^w;{。"

#undef kStrCorruptedROMTitle
#define kStrCorruptedROMTitle "ROM 驗證失敗"
#undef kStrCorruptedROMMessage
#define kStrCorruptedROMMessage "ROM 檔案 ;[^r;{ 可能已損毀。"

#undef kStrUnsupportedROMTitle
#define kStrUnsupportedROMTitle "不支援的 ROM"
#undef kStrUnsupportedROMMessage
#define kStrUnsupportedROMMessage "已成功載入 ROM 檔案 ;[^r;{，但此 ROM 版本不受支援。"

#undef kStrQuitWarningTitle
#define kStrQuitWarningTitle "請先在模擬電腦內關機再離開。"
#undef kStrQuitWarningMessage
#define kStrQuitWarningMessage "若要強制結束 ^p（可能導致已掛載磁碟映像毀損），請使用 ^p 控制模式中的 ;]Q;} 指令。若想了解控制模式，請參閱 ;[更多指令;ll;{，位於 ;[特殊;{ 功能表。"

#undef kStrReportAbnormalTitle
#define kStrReportAbnormalTitle "非預期狀況"
#undef kStrReportAbnormalMessage
#define kStrReportAbnormalMessage "模擬電腦正在嘗試在一般使用情況下不應發生的操作。"

#undef kStrBadArgTitle
#define kStrBadArgTitle "未知參數"
#undef kStrBadArgMessage
#define kStrBadArgMessage "無法識別某個命令列參數，已忽略。"

#undef kStrOpenFailTitle
#define kStrOpenFailTitle "開啟失敗"
#undef kStrOpenFailMessage
#define kStrOpenFailMessage "無法開啟磁碟映像。"

#undef kStrNoReadROMTitle
#define kStrNoReadROMTitle "無法讀取 ROM 映像"
#undef kStrNoReadROMMessage
#define kStrNoReadROMMessage "找到 ROM 檔案 ;[^r;{，但無法讀取。"

#undef kStrShortROMTitle
#define kStrShortROMTitle "ROM 映像過短"
#undef kStrShortROMMessage
#define kStrShortROMMessage "ROM 檔案 ;[^r;{ 的長度小於預期。"

/* ---- 狀態字串 ---- */
#undef kStrOn
#define kStrOn "開啟"
#undef kStrOff
#define kStrOff "關閉"
#undef kStrPressed
#define kStrPressed "按下"
#undef kStrReleased
#define kStrReleased "放開"

#undef kStrSpeedAllOut
#define kStrSpeedAllOut "全速"

/* ---- 控制模式與速度控制 ---- */
#undef kStrHowToLeaveControl
#define kStrHowToLeaveControl "要離開控制模式，請放開 ;]^c;} 鍵。"
#undef kStrHowToPickACommand
#define kStrHowToPickACommand "否則請輸入一個字母。可用指令如下："
#undef kStrCmdAbout
#define kStrCmdAbout "關於（版本資訊）"
#undef kStrCmdOpenDiskImage
#define kStrCmdOpenDiskImage "開啟磁碟映像;ll"
#undef kStrCmdQuit
#define kStrCmdQuit "離開"
#undef kStrCmdSpeedControl
#define kStrCmdSpeedControl "速度控制;ll (^s)"
#undef kStrCmdMagnifyToggle
#define kStrCmdMagnifyToggle "放大切換 (^g)"
#undef kStrCmdFullScrnToggle
#define kStrCmdFullScrnToggle "全螢幕切換 (^f)"
#undef kStrCmdCtrlKeyToggle
#define kStrCmdCtrlKeyToggle "模擬 ;]^m;} 鍵切換 (^k)"
#undef kStrCmdReset
#define kStrCmdReset "重新啟動"
#undef kStrCmdInterrupt
#define kStrCmdInterrupt "中斷"
#undef kStrCmdHelp
#define kStrCmdHelp "說明（顯示本頁）"

#undef kStrCurrentSpeed
#define kStrCurrentSpeed "目前速度：^s"
#undef kStrSpeedStopped
#define kStrSpeedStopped "停止切換 (^h)"
#undef kStrSpeedBackToggle
#define kStrSpeedBackToggle "背景執行切換 (^b)"
#undef kStrSpeedAutoSlowToggle
#define kStrSpeedAutoSlowToggle "自動降速切換 (^l)"
#undef kStrSpeedExit
#define kStrSpeedExit "離開速度控制"

#undef kStrNewSpeed
#define kStrNewSpeed "速度：^s"
#undef kStrSpeedValueAllOut
#define kStrSpeedValueAllOut kStrSpeedAllOut
#undef kStrNewRunInBack
#define kStrNewRunInBack "背景執行為 ^b。"
#undef kStrNewStopped
#define kStrNewStopped "停止狀態為 ^h。"
#undef kStrNewAutoSlow
#define kStrNewAutoSlow "自動降速為 ^l。"
#undef kStrNewMagnify
#define kStrNewMagnify "放大為 ^g。"
#undef kStrNewFullScreen
#define kStrNewFullScreen "全螢幕為 ^f。"

#undef kStrModeConfirmReset
#define kStrModeConfirmReset "控制模式：確認重新啟動"
#undef kStrModeConfirmInterrupt
#define kStrModeConfirmInterrupt "控制模式：確認中斷"
#undef kStrModeConfirmQuit
#define kStrModeConfirmQuit "控制模式：確認離開"
#undef kStrModeSpeedControl
#define kStrModeSpeedControl "控制模式：速度控制"
#undef kStrModeControlBase
#define kStrModeControlBase "控制模式（輸入 ;]H;} 以取得說明）"
#undef kStrModeControlHelp
#define kStrModeControlHelp "控制模式"
#undef kStrModeMessage
#define kStrModeMessage "訊息（輸入 ;]C;} 繼續）"

#undef kStrConfirmReset
#define kStrConfirmReset "確定要重新啟動模擬電腦嗎？未儲存的變更將會遺失，且可能造成磁碟映像毀損。請輸入指令："
#undef kStrResetDo
#define kStrResetDo "重新啟動"
#undef kStrResetNo
#define kStrResetNo "取消"
#undef kStrHaveReset
#define kStrHaveReset "已重新啟動模擬電腦"
#undef kStrCancelledReset
#define kStrCancelledReset "已取消重新啟動"

#undef kStrConfirmInterrupt
#define kStrConfirmInterrupt "確定要中斷模擬電腦嗎？這將呼叫任何已安裝的除錯器。請輸入指令："
#undef kStrInterruptDo
#define kStrInterruptDo "中斷"
#undef kStrInterruptNo
#define kStrInterruptNo "取消"
#undef kStrHaveInterrupted
#define kStrHaveInterrupted "已中斷模擬電腦"
#undef kStrCancelledInterrupt
#define kStrCancelledInterrupt "已取消中斷"

#undef kStrConfirmQuit
#define kStrConfirmQuit "確定要離開 ^p 嗎？離開前應先在模擬電腦內關機以避免磁碟映像毀損。請輸入指令："
#undef kStrQuitDo
#define kStrQuitDo "離開"
#undef kStrQuitNo
#define kStrQuitNo "取消"
#undef kStrCancelledQuit
#define kStrCancelledQuit "已取消離開"

/* ---- 功能表 ---- */
#undef kStrMenuFile
#define kStrMenuFile "檔案"
#undef kStrMenuSpecial
#define kStrMenuSpecial "特殊"
#undef kStrMenuHelp
#define kStrMenuHelp "說明"
#undef kStrMenuItemAbout
#define kStrMenuItemAbout "關於 ^p"
#undef kStrMenuItemOpen
#define kStrMenuItemOpen "開啟磁碟映像"
#undef kStrMenuItemQuit
#define kStrMenuItemQuit "離開"
#undef kStrMenuItemMore
#define kStrMenuItemMore "更多指令"

/* ---- 其他 ---- */
#undef kStrCmdCopyOptions
#define kStrCmdCopyOptions "複製變體選項"
#undef kStrHaveCopiedOptions
#define kStrHaveCopiedOptions "已複製變體選項"

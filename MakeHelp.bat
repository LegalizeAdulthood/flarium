@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by FLARIUM24.HPJ. >"hlp\Flarium24.hm"
echo. >>"hlp\Flarium24.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\Flarium24.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\Flarium24.hm"
echo. >>"hlp\Flarium24.hm"
echo // Prompts (IDP_*) >>"hlp\Flarium24.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\Flarium24.hm"
echo. >>"hlp\Flarium24.hm"
echo // Resources (IDR_*) >>"hlp\Flarium24.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\Flarium24.hm"
echo. >>"hlp\Flarium24.hm"
echo // Dialogs (IDD_*) >>"hlp\Flarium24.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\Flarium24.hm"
echo. >>"hlp\Flarium24.hm"
echo // Frame Controls (IDW_*) >>"hlp\Flarium24.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\Flarium24.hm"
REM -- Make help for Project FLARIUM24


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\Flarium24.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\Flarium24.hlp" goto :Error
if not exist "hlp\Flarium24.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\Flarium24.hlp" Debug
if exist Debug\nul copy "hlp\Flarium24.cnt" Debug
if exist Release\nul copy "hlp\Flarium24.hlp" Release
if exist Release\nul copy "hlp\Flarium24.cnt" Release
echo.
goto :done

:Error
echo hlp\Flarium24.hpj(1) : error: Problem encountered creating help file

:done
echo.

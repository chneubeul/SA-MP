@ECHO OFF

TITLE SAM Auto Include Update v1.0
COLOR 9F

SET SETTINGS=%CD%\settings.ini
SET LISTFILE=%CD%\include.lst

ECHO.
ECHO SAM Auto Include Update v1.0
ECHO.

IF NOT EXIST "%SETTINGS%" (
	ECHO [SAM] >> "%SETTINGS%" 
	ECHO input=https://raw.githubusercontent.com/AbyssMorgan/SA-MP/master/include/SAM >> "%SETTINGS%" 
	ECHO output=%CD%\include >> "%SETTINGS%" 
)

FOR /F "tokens=*" %%s IN (settings.ini) DO CALL :READINI %%s

IF NOT DEFINED INPUT ECHO Source is not set & PAUSE > nul & EXIT
IF NOT DEFINED OUTPUT ECHO Destination folder is not set & PAUSE > nul & EXIT

ECHO Update Include List
IF EXIST "%CD%\include.tmp" DEL /Q /A "%CD%\include.tmp"
powershell -command "& { (New-Object Net.WebClient).DownloadFile('%INPUT%/z_include.lst', '%CD%\include.tmp') }"
IF EXIST "%CD%\include.tmp" (
	IF EXIST "%CD%\include.lst" (
		DEL /Q /A "%CD%\include.lst"
	)
	REN "%CD%\include.tmp" "include.lst"
)
ECHO.

IF NOT EXIST "%LISTFILE%" ECHO List file not exist & PAUSE > nul & EXIT

IF NOT EXIST "%OUTPUT%" (
	ECHO Create Output folder: %OUTPUT%
	MD "%OUTPUT%"
	ECHO.
)

FOR /F "tokens=*" %%s IN (include.lst) DO (
	ECHO Download %%s
	powershell -command "& { (New-Object Net.WebClient).DownloadFile('%INPUT%/%%s', '%OUTPUT%\%%s') }"
)

ECHO.
ECHO End
ECHO.
PAUSE > nul
GOTO :eof

REM Read Ini file
:READINI
SET BUFFER=%*
IF "%BUFFER:~0,1%" == "$" GOTO :eof
IF "%BUFFER:~0,1%" == "#" GOTO :eof
IF "%BUFFER:~0,1%" == ";" GOTO :eof
IF "%BUFFER:~0,1%" == "!" GOTO :eof
IF "%BUFFER:~0,1%%BUFFER:~-1,1%" == "[]" GOTO :eof
SET %*
GOTO :eof

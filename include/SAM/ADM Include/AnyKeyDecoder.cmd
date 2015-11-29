@ECHO OFF
COLOR 9F
TITLE %~n0
ECHO.
ECHO Allowed arguments: 1 - 255
ECHO.

SETLOCAL enabledelayedexpansion
SET /P I_KEY=Encryption key: 


CALL :ARG %I_KEY%
SET O_KEY=
FOR /l %%i IN (1,1,%ARGCNT%) DO CALL :SET_KEY %%i

ECHO Decryption key:%O_KEY%
ECHO.
PAUSE > nul

GOTO :eof

:SET_KEY
IF !P[%~1]! GTR 255 CALL :ERR "!P[%~1]!"
IF !P[%~1]! LSS 1 CALL :ERR "!P[%~1]!"
SET /A si=256-!P[%~1]!
SET O_KEY=%O_KEY% %si%
GOTO :eof

:ARG
FOR /l %%i IN (1,1,%ARGCNT%) DO SET P[%%i]=
SET ARGCNT=0
FOR %%p IN (%*) DO CALL :ARG_GET %%p
GOTO :eof

:ARG_GET
SET /A ARGCNT=%ARGCNT%+1
SET P[%ARGCNT%]=%~1
GOTO :eof

:ERR
ECHO.
ECHO Invalid argument: %~1
PAUSE > nul
EXIT 0
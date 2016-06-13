@ECHO OFF

TITLE Binary Object File Converter
COLOR 9F

ECHO.
ECHO Binary Object File Converter v1.0 by Abyss Morgan
ECHO Drop input file, and click enter.
:RESTART
ECHO.
SET FILE=
SET /P FILE=Input file: 
ECHO.

IF EXIST %FILE% (
	CALL :CONVERT %FILE%
) ELSE (
	CALL :CONVERT "%FILE%"
)
ECHO.


GOTO :RESTART

:CONVERT
IF /I "%~1" == "exit" EXIT
IMG_Gen	"%~1" "%CD%\%~n1.bin"
ECHO.
ECHO Output file: %CD%\%~n1.bin
GOTO :eof
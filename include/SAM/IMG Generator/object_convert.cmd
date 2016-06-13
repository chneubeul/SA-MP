@ECHO OFF

TITLE Binary Object File Converter
COLOR 9F

ECHO.
ECHO Binary Object File Converter v1.0 by Abyss Morgan
ECHO Drop input file, and click enter.
ECHO.
SET /P FILE=Input file: 
ECHO.
CALL :CONVERT %FILE%
ECHO.
PAUSE
GOTO :eof

:CONVERT
IMG_Gen	"%~1" "%CD%\%~n1.bin"
ECHO.
ECHO Output file: %CD%\%~n1.bin
GOTO :eof
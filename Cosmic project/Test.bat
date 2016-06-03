@echo off
cxstm8 -vl +modsl crts.s acia.c vector.c
if errorlevel 1 goto bad
:clink
echo.
echo Linking ...
clnk -o acia.sm8 -m acia.map acia.lkf
if errorlevel 1 goto bad
:chexa
echo.
echo Converting ...
chex -o acia.hex acia.sm8
if errorlevel 1 goto bad
:cllabs
echo.
echo Generating absolute listing ...
clabs acia.sm8
if errorlevel 1 goto bad
echo.
echo.
echo        The C Cross Compiler for STM8 is now installed.
echo.
pause
goto sortie
:bad
echo.
echo.
echo        THE COMPILER INSTALLATION FAILED.
echo.
pause
:sortie
echo on

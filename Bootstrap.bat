@echo off

if [%1] == [] (set project=vs2022) else set project=%1

call vendor\premake\premake5.exe %project%
pause

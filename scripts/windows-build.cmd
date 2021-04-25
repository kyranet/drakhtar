@echo off

where pwsh >nul 2>nul
if %ERRORLEVEL% neq 0 (
	echo You must install Microsoft PowerShell to run this command, please download it here:
	echo https://github.com/PowerShell/PowerShell/releases
	pause
	exit /B 1
)

pwsh -NoLogo -NoProfile -ExecutionPolicy ByPass -Command "& """%~dp0windows-build.ps1""" %*"
if %ERRORLEVEL% neq 0 (
	pause
)

exit /B %ERRORLEVEL%

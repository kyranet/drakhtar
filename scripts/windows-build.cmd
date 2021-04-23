@ECHO OFF
pwsh -NoLogo -NoProfile -ExecutionPolicy ByPass -Command "& """%~dp0windows-build.ps1""" %*"
EXIT /B %ERRORLEVEL%

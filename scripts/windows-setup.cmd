@ECHO OFF
pwsh -NoLogo -NoProfile -ExecutionPolicy ByPass -Command "& """%~dp0windows-setup.ps1""" %*"
EXIT /B %ERRORLEVEL%

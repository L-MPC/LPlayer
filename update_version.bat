@ECHO OFF

SETLOCAL
SET "FILE_DIR=%~dp0"
PUSHD "%FILE_DIR%"

SET "COMMON=%FILE_DIR%\common.bat"

IF EXIST "build.user.bat" CALL "build.user.bat"

IF NOT DEFINED MPCHC_GIT IF DEFINED GIT (SET MPCHC_GIT=%GIT%)
SET "PATH=%MPCHC_GIT%\cmd;%PATH%"

CALL "%COMMON%" :SubSetPath
IF %ERRORLEVEL% NEQ 0 GOTO MissingVar
CALL "%COMMON%" :SubDoesExist bash.exe
IF %ERRORLEVEL% NEQ 0 GOTO MissingVar

bash.exe ./version.sh %*


:END
POPD
ENDLOCAL
EXIT /B


:MissingVar
ECHO Not all build dependencies were found.
ECHO.
ECHO See "docs\Compilation.txt" for more information.
ENDLOCAL
EXIT /B 1

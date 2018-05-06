@ECHO OFF
SET "MPCHC_MSYS=C:\MSYS"
SET "MPCHC_MINGW32=%MPCHC_MSYS%\mingw"
SET "MPCHC_MINGW64=%MPCHC_MINGW32%"
REM Git is optional to set if you chose to add it in PATH when installing it
SET "MPCHC_GIT=C:\Program Files (x86)\Git"
REM Optional, if you plan to modify the translations, install Python 2.7 or set the variable to its path
SET "MPCHC_PYTHON=C:\Python27"
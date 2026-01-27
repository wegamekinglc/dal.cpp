@echo off

call :set_variable DAL_DIR "%CD%" %DAL_DIR%
call :set_variable MSVC_VERSION "Visual Studio 17 2022" %MSVC_VERSION%

echo BUILD_TYPE:  %BUILD_TYPE%
echo DAL_DIR: %DAL_DIR%

if exist build (
  rem build folder already exists.
) else (
  mkdir build
)

cd build
cmake -G "%MSVC_VERSION%" --preset %BUILD_TYPE%-windows ..

if %errorlevel% neq 0 exit /b 1

msbuild dal.sln /m /p:Configuration=%BUILD_TYPE% /p:Platform=x64
msbuild INSTALL.vcxproj /m:%NUMBER_OF_PROCESSORS% /p:Configuration=%BUILD_TYPE% /p:Platform=x64

if %errorlevel% neq 0 exit /b 1

cd ..


if "%SKIP_TESTS%"=="false" (
    echo "starting run unit tests suite"
    bin\test_suite.exe
)

if %errorlevel% neq 0 exit /b 1

@echo on

EXIT /B 0

:set_variable
set %~1=%~2
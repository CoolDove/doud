@echo off
set Config=Debug
if "%1" == "native" (
    pushd dcore
    premake5 vs2019 --cppnative
	if exist ".\bin\Debug\dcore\dcore.dll" (
	    rm .\bin\Debug\dcore\dcore.dll
	)
    msbuild.exe Doud.sln -m -p:Configuration=%Config% -p:WarningLevel=0 -nologo
    popd
) else (
    pushd dcore
    premake5 vs2019
	if exist ".\bin\Debug\dcore\dcore.exe" (
	    rm .\bin\Debug\dcore\dcore.exe
	)
    msbuild.exe Doud.sln -m -p:Configuration=%Config% -p:WarningLevel=0 -nologo
    popd
    robocopy dcore/bin/%Config%/dcore doudcs/bin/%Config%/net5.0 dcore.dll
    pushd doudcs
    msbuild.exe doudcs.sln -m -p:Configuration=%Config% -p:WarningLevel=0 -nologo
    popd
)

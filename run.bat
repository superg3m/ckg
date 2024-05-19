@echo off

call build.bat

if not exist .\examples\cl (
    mkdir .\examples\cl
)

if not exist .\examples\gcc (
    mkdir .\examples\gcc
)

echo "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
echo =========================== CL ===========================
echo "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
pushd .\examples\cl
cl /Fe: ".\test_ckg.exe" /Zi "..\*.c" "..\..\build_cl\ckg.lib"

".\test_ckg.exe"
popd




:: echo "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
:: echo =========================== GCC ==========================
:: echo "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
:: pushd .\examples\gcc
:: gcc "..\*.c" -o "CKit_Test.exe" -g -L"../../build_gcc" -lCKit
:: ".\CKit_Test.exe"
:: popd
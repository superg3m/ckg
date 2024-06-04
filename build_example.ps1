./build.ps1

if(!(Test-Path -Path ".\examples\cl")) {
    mkdir ".\examples\cl"
}

if(!(Test-Path -Path ".\examples\gcc")) {
    mkdir ".\examples\gcc"
}

Push-Location -Path ".\examples\cl"
cl /std:c11 /Fe: ".\test_ckg.exe" /Zi "..\*.c" "..\..\build_cl\ckg.lib"
Pop-Location
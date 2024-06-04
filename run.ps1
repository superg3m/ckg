./build.ps1 "c99"

Push-Location ".\examples\cl"
cl /std:c11 /Fe: ".\ckit_test.exe" /Zi "..\*.c" "..\..\build_cl\ckg.lib"
& "./ckit_test.exe"
Pop-Location
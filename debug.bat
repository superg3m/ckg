@echo off

if not exist .\examples\cl\test_ckg.sln (
    if not exist .\examples\cl\test_ckg.exe (
        powershell -nologo -command "Write-Host 'ERROR: check if exe exists and re-build' -ForegroundColor Red"
    ) else (
        devenv .\examples\cl\test_ckg.exe
    )
) else (
    devenv .\examples\cl\test_ckg.sln
)

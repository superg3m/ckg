@echo off
powershell -nologo -command "Write-Host 'running ckg clean.bat...' -ForegroundColor Green"
del .\build_cl /q
del .\build_gcc /q
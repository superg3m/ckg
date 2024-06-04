Write-Host "running CKit clean.bat..." -ForegroundColor Green

Remove-Item -Path ".\build_cl\*", -Force -ErrorAction SilentlyContinue -Confirm:$false -Recurse
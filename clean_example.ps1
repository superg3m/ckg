Write-Host "running CKit clean.bat..." -ForegroundColor Green

Remove-Item -Path ".\examples\cl\*" -Force -ErrorAction SilentlyContinue -Confirm:$false -Recurse
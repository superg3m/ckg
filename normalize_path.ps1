Write-Host 'Running normalize_path.ps1...' -ForegroundColor Green

$rootPath = $PSScriptRoot
$tempFile = 'compilation_errors_temp.txt'

# Create a new, empty temporary file
New-Item -Path $tempFile -Force | Out-Null

# Read each line from compilation_errors.txt
Get-Content -Path 'compilation_errors.txt' | ForEach-Object {
    $line = $_

    # Replace $rootPath with nothing in the line
    $line = $line -replace [Regex]::Escape($rootPath), ''

    # Write the modified line to the temporary file
    Add-Content -Path $tempFile -Value $line
}

# Replace the original file with the temporary file
Move-Item -Path $tempFile -Destination 'compilation_errors.txt' -Force

# Display the modified file
Get-Content -Path 'compilation_errors.txt'

# Clean up
Remove-Item -Path 'compilation_errors.txt'
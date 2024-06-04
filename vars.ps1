# Define the path to the vcvarsall.bat script
$clAvailable = $null -ne (Get-Command cl -ErrorAction SilentlyContinue)

if (!$clAvailable) {
    $vcvarsallPath = "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat"

    # Run the batch file and capture the environment variables it sets
    $envVars = & cmd /c "call `"$vcvarsallPath`" x64 > NUL && set"

    # Import the environment variables into PowerShell
    $envVars -split "`r`n" | ForEach-Object {
        $name, $value = $_ -split '=', 2
        [Environment]::SetEnvironmentVariable($name, $value, [System.EnvironmentVariableTarget]::Process)
    }

    Write-Host "Visual Studio environment variables have been set." -ForegroundColor Green
}
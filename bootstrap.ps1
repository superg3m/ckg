# This build file has been generated by C-Build
if ($PSVersionTable.Platform -eq "Unix") {
    Set-Alias python python3
}

$directoryPath = "./c-build"
$repositoryUrl = "https://github.com/superg3m/c-build.git"

if (-not (Test-Path -Path $directoryPath)) {
    Write-Output "Directory does not exist. Cloning the repository..."
    git clone $repositoryUrl
}

. ./c-build/validate_temp_files.ps1 $MyInvocation.MyCommand.Name

$bootstrapScriptPath = "$directoryPath/bootstrap.ps1"
if (Test-Path -Path $bootstrapScriptPath) {
    & $bootstrapScriptPath
} else {
    Write-Output "Bootstrap script not found at $bootstrapScriptPath"
}

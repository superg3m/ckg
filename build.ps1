param(
	[Parameter(Mandatory=$true)]
	[string] $std_version
)

./vars.ps1

$extension = ".c"

if(!(Test-Path -Path ".\ckg")) {
    #Write-Host "missing ckg"
    #git clone https://github.com/superg3m/ckg.git
} else {
    #Push-Location  ".\ckg"
    #git stash
    #git stash drop
    #git pull
    #Pop-Location
}

if(!(Test-Path -Path ".\build_cl")) {
    mkdir .\build_cl
}

if(Test-Path -Path ".\compilation_errors.txt") {
	Remove-Item -Path "./compilation_errors.txt" -Force -Confirm:$false
}

Write-Host "running CKit build.ps1..." -ForegroundColor Green

$timer = [Diagnostics.Stopwatch]::new() # Create a timer
$timer.Start() # Start the timer

Push-Location ".\build_cl"
# MAKE SURE YOU HAVE AN OPTION FOR DEBUG LIBS
# cl -DCUSTOM_PLATFORM_IMPL /std:c++20 /c "..\source\*.cpp"
cl /std:c11 /Zi /FC /c "..\source\*$extension" | Out-File -FilePath "..\compilation_errors.txt" -Append
lib /OUT:".\ckg.lib" "User32.lib" ".\*.obj" | Out-Null
Pop-Location

$timer.Stop()
Write-Host "========================================================"
Write-Host "MSVC Elapsed time: $($timer.Elapsed.TotalSeconds)s" -ForegroundColor Blue
Write-Host "========================================================"
Write-Host ""

./normalize_path.ps1


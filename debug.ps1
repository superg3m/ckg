param(
	[Parameter(Mandatory=$false)]
	[string] $debug_with_visual_studio
)

$executableFilePath = ".\examples\cl\test_ckg.exe"

if (!(Test-Path -Path $executableFilePath)) {
    Write-Host "ERROR: Can't find exe, building..." -ForegroundColor Red
    ./build_example.ps1
    if ($debug_with_visual_studio -eq "vs") {
        devenv $executableFilePath
    } else {
        & "raddbg" $executableFilePath
    }
} else {
    if ($debug_with_visual_studio -eq "vs") {
        devenv $executableFilePath
    } else {
        & "raddbg" $executableFilePath
    }
}
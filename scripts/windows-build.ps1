function New-Directory([string[]] $Path) {
	if (!(Test-Path -Path $Path)) {
		New-Item -Path $Path -Force -ItemType Directory | Out-Null
	}
}

# Asserts that the variable assigned to $CMake is a valid file path, discarding files that do not exist and folders.
function Assert-CMakePath([string] $CMake) {
	if (($CMake -Eq "") -Or !(Test-Path -LiteralPath $CMake -PathType Leaf)) {
		Write-Host "I was not able to find cmake.exe, please download the binary at https://cmake.org." -ForegroundColor Red
		Write-Host "  # Please specify the route to the cmake.exe by doing "                            -ForegroundColor Yellow -NoNewline
		Write-Host "`$Env:CMake=`"Path\To\cmake.exe`""                                                  -ForegroundColor Cyan   -NoNewline
		Write-Host ", afterwards you will be able to execute "                                          -ForegroundColor Yellow -NoNewline
		Write-Host ".\scripts\windows-build.ps1"                                                        -ForegroundColor Cyan   -NoNewline
		Write-Host " normally."                                                                         -ForegroundColor Yellow
		exit 1
	}

	return $CMake
}

# Finds cmake.exe from the user's input, falling back in the following order:
#  - Environmental Variable
#  - Get-Command (PATH)
#  - Program Files typical installation path scan
function Find-CMake() {
	# Find from environmental variable:
	if ($Env:CMake) {
		$CMake = (Resolve-Path $Env:CMake)[0].Path
		Write-Host "CMake not provided, using '"             -ForegroundColor Blue -NoNewline
		Write-Host $CMake                                    -ForegroundColor Cyan -NoNewline
		Write-Host "' from environmental variables instead." -ForegroundColor Blue
		return Assert-CMakePath $CMake;
	}

	# Find from PATH environmental variables:
	$local:PossibleCMake = Get-Command "cmake.exe" -ErrorAction SilentlyContinue
	if ($PossibleCMake) {
		$CMake = $PossibleCMake.Path;
		Write-Host "CMake not provided, using '" -ForegroundColor Blue -NoNewline
		Write-Host $CMake                        -ForegroundColor Cyan -NoNewline
		Write-Host "' from PATH instead."        -ForegroundColor Blue
		return Assert-CMakePath $CMake;
	}

	# Find from ProgramFiles:
	$local:PossibleCMake = Resolve-Path "${Env:ProgramFiles}\CMake\bin\cmake.exe" -ErrorAction SilentlyContinue
	if (($PossibleCMake) -And ($PossibleCMake.Length -Ge 0)) {
		$CMake = $PossibleCMake[0].Path
		Write-Host "CMake not provided, using '" -ForegroundColor Blue -NoNewline
		Write-Host $CMake                          -ForegroundColor Cyan -NoNewline
		Write-Host "' instead."                    -ForegroundColor Blue
		return Assert-CMakePath $CMake;
	}
}

# Find and assert CMake
function Step-CMakeConfigure([string] $CMake, [string] $Path, [string[]] $Arguments) {
	Write-Host "# Generating CMake Project for '" -ForegroundColor Blue -NoNewline
	Write-Host $Path                              -ForegroundColor Cyan -NoNewline
	Write-Host "'."                               -ForegroundColor Blue

	New-Directory -Path "$Path\build"
	$private:startTime = Get-Date
	& $CMake -S $Path -B "$Path\build" $Arguments -Wno-dev
	$private:exitTime = Get-Date

	# Print information to the screen
	$private:duration = $exitTime - $startTime
	if ($LastExitCode -Eq 0) {
		Write-Host "# Finished generating '" -ForegroundColor Green -NoNewLine
		Write-Host $Path                     -ForegroundColor Cyan  -NoNewLine
		Write-Host "'. Took: "               -ForegroundColor Green -NoNewLine
		Write-Host ("{0:g}" -f $duration)    -ForegroundColor Cyan  -NoNewLine
		Write-Host "."                       -ForegroundColor Green
	} else {
		Write-Host "# Errored when generating '"      -ForegroundColor Red  -NoNewLine
		Write-Host $Path                              -ForegroundColor Cyan -NoNewLine
		Write-Host "' with code $LastExitCode Took: " -ForegroundColor Red  -NoNewLine
		Write-Host ("{0:g}" -f $duration)             -ForegroundColor Cyan -NoNewLine
		Write-Host "."                                -ForegroundColor Red
		throw "Failed to generate CMake project, please read the logs above.";
	}
}

# Build a CMake-generated project given a path and optional arguments
function Step-CMakeBuild([string] $CMake, [string] $Path, [string] $Configuration = "Debug") {
	Write-Host "# Now building '"     -ForegroundColor Blue -NoNewline
	Write-Host $Path                  -ForegroundColor Cyan -NoNewline
	Write-Host "' as $Configuration." -ForegroundColor Blue

	# Run the process
	$private:startTime = Get-Date
	& $CMake @("--build", "$Path", "--config", "$Configuration", "-j", "--", "-m", "-noLogo")
	$private:exitTime = Get-Date

	# Print information to the screen
	$private:duration = $exitTime - $startTime
	if ($LastExitCode -Eq 0) {
		Write-Host "# Finished building '" -ForegroundColor Green -NoNewLine
		Write-Host $Path                   -ForegroundColor Cyan  -NoNewLine
		Write-Host "'. Took: "             -ForegroundColor Green -NoNewLine
		Write-Host ("{0:g}" -f $duration)  -ForegroundColor Cyan  -NoNewLine
		Write-Host "."                     -ForegroundColor Green
	} else {
		Write-Host "# Errored when building '"        -ForegroundColor Red  -NoNewLine
		Write-Host $Path                              -ForegroundColor Cyan -NoNewLine
		Write-Host "' with code $LastExitCode Took: " -ForegroundColor Red  -NoNewLine
		Write-Host ("{0:g}" -f $duration)             -ForegroundColor Cyan -NoNewLine
		Write-Host "."                                -ForegroundColor Red
		exit 1
	}
}

$private:CMake = Find-CMake

# Run CMake in the project:
$local:RootFolder = Split-Path $PSScriptRoot
Step-CMakeConfigure -CMake $CMake -Path $RootFolder

# Run CMake Build to the built project:
$local:BuildFolder = Join-Path -Path $RootFolder -ChildPath "build"
Step-CMakeBuild -CMake $CMake -Path $BuildFolder

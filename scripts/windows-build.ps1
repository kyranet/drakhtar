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
	if (Get-Command "cmake.exe" -ErrorAction SilentlyContinue) {
		$CMake = (Get-Command "cmake.exe").Path;
		Write-Host "CMake not provided, using '" -ForegroundColor Blue -NoNewline
		Write-Host $CMake                        -ForegroundColor Cyan -NoNewline
		Write-Host "' from PATH instead."        -ForegroundColor Blue
		return Assert-CMakePath $CMake;
	}

	# Find from ProgramFiles:
	$local:PossibleCMake = Resolve-Path "${Env:ProgramFiles}\CMake\bin\cmake.exe" -ErrorAction SilentlyContinue
	if (($PossibleCMake) -And ($PossibleCMake.Length -Ge 0)) {
		$CMake = $PossibleCMake[0].Path
		Write-Host "MsBuild not provided, using '" -ForegroundColor Blue -NoNewline
		Write-Host $CMake                          -ForegroundColor Cyan -NoNewline
		Write-Host "' instead."                    -ForegroundColor Blue
		return Assert-CMakePath $CMake;
	}
}

# Find and assert CMake
function Step-CMake([string] $CMake, [string] $Path, [string[]] $Arguments) {
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

# Asserts that the variable assigned to $MsBuild is a valid file path, discarding files that do not exist and folders.
function Assert-MsBuildPath([string] $MsBuild) {
	if (($MsBuild -Eq "") -Or !(Test-Path -LiteralPath $MsBuild -PathType Leaf)) {
		Write-Host "I was not able to find MSBuild.exe, please check https://docs.microsoft.com/visualstudio/msbuild/msbuild?view=vs-2019 for more information." -ForegroundColor Red
		Write-Host "  # Please specify the route to the MSBuild.exe by doing " -ForegroundColor Yellow -NoNewline
		Write-Host ".\scripts\build.ps1 `"Path\To\MSBuild.exe`""               -ForegroundColor Cyan   -NoNewline
		Write-Host " or "                                                      -ForegroundColor Yellow -NoNewline
		Write-Host ".\scripts\build.ps1 -MsBuild `"Path\To\MSBuild.exe`""      -ForegroundColor Cyan   -NoNewline
		Write-Host " to set the path."                                         -ForegroundColor Yellow
		Write-Host "  # Alternatively, do "                                    -ForegroundColor Yellow -NoNewline
		Write-Host "`$Env:MsBuild=`"Path\To\MSBuild.exe`""                     -ForegroundColor Cyan   -NoNewline
		Write-Host ", afterwards you will be able to execute "                 -ForegroundColor Yellow -NoNewline
		Write-Host ".\scripts\build.ps1"                                       -ForegroundColor Cyan   -NoNewline
		Write-Host " normally."                                                -ForegroundColor Yellow
		exit 1
	}

	return $MsBuild
}

# Finds MSBuild.exe from the user's input, falling back in the following order:
#  - Environmental Variable
#  - Get-Command (PATH)
#  - Program Files typical installation path scan
function Find-MsBuild() {
	# Find from environmental variable:
	if ($Env:MsBuild) {
		$MsBuild = (Resolve-Path $Env:MsBuild)[0].Path
		Write-Host "MsBuild not provided, using '"           -ForegroundColor Blue -NoNewline
		Write-Host $MsBuild                                  -ForegroundColor Cyan -NoNewline
		Write-Host "' from environmental variables instead." -ForegroundColor Blue
		return Assert-MsBuildPath $MsBuild;
	}

	# Find from PATH environmental variables:
	if (Get-Command "MSBuild.exe" -ErrorAction SilentlyContinue) {
		$MsBuild = (Get-Command "MSBuild.exe").Path;
		Write-Host "MsBuild not provided, using '" -ForegroundColor Blue -NoNewline
		Write-Host $MsBuild                        -ForegroundColor Cyan -NoNewline
		Write-Host "' from PATH instead."          -ForegroundColor Blue
		return Assert-MsBuildPath $MsBuild;
	}

	# Find from ProgramFiles:
	$local:PossibleMsBuild = Resolve-Path "${Env:ProgramFiles(x86)}\Microsoft Visual Studio\2019\*\MSBuild\*\Bin\MSBuild.exe" -ErrorAction SilentlyContinue
	if (($PossibleMsBuild) -And ($PossibleMsBuild.Length -Ge 0)) {
		$MsBuild = $PossibleMsBuild[0].Path;
		Write-Host "MsBuild not provided, using '" -ForegroundColor Blue -NoNewline
		Write-Host $MsBuild                        -ForegroundColor Cyan -NoNewline
		Write-Host "' instead."                    -ForegroundColor Blue
		return Assert-MsBuildPath $MsBuild;
	}
}

# Build a MSVC project given a path and optional arguments
function Step-VisualStudio {
	param (
		[string] $MsBuild,
		[string] $Path,
		[string] $Configuration = "Debug",
		[bool] $ThrowOnError = $false
	)

	Write-Host "# Now building '"     -ForegroundColor Blue -NoNewline
	Write-Host $Path                  -ForegroundColor Cyan -NoNewline
	Write-Host "' as $Configuration." -ForegroundColor Blue

	# Run the process
	$private:startTime = Get-Date
	& $MsBuild $Path @("-p:Configuration=$Configuration", "-m", "-noLogo")
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
		if ($ThrowOnError) {
			throw "Failed to build project project, please read the logs above.";
		}
	}
}

$private:CMake = Find-CMake
$private:MsBuild = Find-MsBuild

# Run CMake in the project:
$local:RootFolder = Split-Path $PSScriptRoot
Step-CMake -CMake $CMake -Path $RootFolder

# Run Visual Studio to the built project:
$local:BuildFolder = Join-Path -Path $RootFolder -ChildPath "build"
$local:BuildSolution = Join-Path -Path $BuildFolder -ChildPath "drakhtar.sln"
Step-VisualStudio -MsBuild $MsBuild -Path $BuildSolution

# Set up the submodule so Drakhtar Telemetry is properly included in the project:
git submodule init
git submodule update

$local:DependencyFolder = Join-Path -Path $(Split-Path $PSScriptRoot) -ChildPath "deps"
$local:BaseDomain = "https://www.libsdl.org/"

function Step-Download {
	[CmdletBinding()]
	param (
		[string] $Output,
		[string] $UriPath
	)

	process {
		$private:OutputDirectory = Join-Path -Path $DependencyFolder -ChildPath $Output
		if (Test-Path -Path $OutputDirectory) {
			Write-Host "Skipping ["                  -ForegroundColor Green -NoNewline
			Write-Host $Output                       -ForegroundColor Blue  -NoNewline
			Write-Host "] as it already exists in [" -ForegroundColor Green -NoNewline
			Write-Host $OutputDirectory              -ForegroundColor Blue  -NoNewline
			Write-Host "]."                          -ForegroundColor Green
		} else {
			Write-Host "Downloading ["  -ForegroundColor DarkGray -NoNewline
			Write-Host $Output          -ForegroundColor Blue   -NoNewline
			Write-Host "] into ["       -ForegroundColor DarkGray -NoNewline
			Write-Host $OutputDirectory -ForegroundColor Blue   -NoNewline
			Write-Host "]."             -ForegroundColor DarkGray

			$private:DownloadUri = $BaseDomain + $UriPath
			$private:File = New-TemporaryFile
			Invoke-WebRequest -Uri $DownloadUri -OutFile $File
			$File | Expand-Archive -DestinationPath $DependencyFolder -Force
			$File | Remove-Item
		}
	}
}

function Remove-SafeItem([string] $Path) {
	if (Test-Path -Path $Path) {
		Write-Host "Deleting [" -ForegroundColor DarkGray -NoNewline
		Write-Host $Path        -ForegroundColor Blue   -NoNewline
		Write-Host "]."         -ForegroundColor DarkGray

		Remove-Item $Path
	}
}

$private:Sdl2 = "SDL2-2.0.14"
$private:Sdl2Ttf = "SDL2_ttf-2.0.15"
$private:Sdl2Image = "SDL2_image-2.0.5"
$private:Sdl2Mixer = "SDL2_mixer-2.0.4"

# Download the dependencies:
Step-Download -Output $Sdl2      -UriPath "release/SDL2-devel-2.0.14-VC.zip"
Step-Download -Output $Sdl2Ttf   -UriPath "projects/SDL_ttf/release/SDL2_ttf-devel-2.0.15-VC.zip"
Step-Download -Output $Sdl2Image -UriPath "projects/SDL_image/release/SDL2_image-devel-2.0.5-VC.zip"
Step-Download -Output $Sdl2Mixer -UriPath "projects/SDL_mixer/release/SDL2_mixer-devel-2.0.4-VC.zip"

# Remove SDL2 TTF's zlib1.dll, as they are already included in SDL2 Image:
Remove-SafeItem $(Join-Path -Path $DependencyFolder -ChildPath "$Sdl2Ttf/lib/x64/zlib1.dll")
Remove-SafeItem $(Join-Path -Path $DependencyFolder -ChildPath "$Sdl2Ttf/lib/x86/zlib1.dll")

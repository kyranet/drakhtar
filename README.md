# Drakhtar

A game built on top of SDL2.

---

## Build Pre-requisites

### Windows

#### Automatic

Double click on the [`windows-setup.cmd`] and the [`windows-build.cmd`] files accordingly. That's all!

> **Note**: You must download [Microsoft PowerShell](https://github.com/PowerShell/PowerShell) to run the scripts, the
built-in Windows PowerShell does not work as it lacks of features needed for them to work.

#### Manual

Please download the suitable dependencies for
[SDL2](https://www.libsdl.org/download-2.0.php),
[SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/),
[SDL2_image](https://www.libsdl.org/projects/SDL_image/), and
[SDL2_mixer](https://www.libsdl.org/projects/SDL_mixer/).

This project supports a local dependency link, download the development dependencies and unzip them inside a `deps`
folder at the root of this project, this will allow the project to link and build the project successfully.

Additionally, you must remove the `zlib1.dll` from both binary directories of `SDL2_ttf`, they're older than `SDL2_image`'s
and cause runtime errors when loading images, as `inflateValidate` does not exist in that version.

### Debian/Ubuntu

```
$ apt-get install cmake libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev libsdl2-mixer-dev
```

### FreeBSD

```shell
$ pkg install cmake libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev libsdl2-mixer-dev
```

### OS X

```shell
$ brew install cmake sdl2 sdl2-ttf sdl2-image sdl2-mixer
```

[`windows-setup.cmd`]: https://github.com/kyranet/drakhtar/blob/main/scripts/windows-setup.cmd
[`windows-build.cmd`]: https://github.com/kyranet/drakhtar/blob/main/scripts/windows-build.cmd

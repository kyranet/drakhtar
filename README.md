# Drakhtar

A game built on top of SDLv2.

---

## Build Pre-requisites

### FreeBSD

```shell
$ pkg install cmake sdl2 sdl2_ttf sdl2_image sdl2_mixer
```

### OS X

```shell
$ brew install cmake sdl2 sdl2_ttf sdl2_image sdl2_mixer
```

### Debian/Ubuntu

```
$ apt-get install cmake sdl2 sdl2_ttf sdl2_image sdl2_mixer
```

### Windows

Please download the suitable dependencies for
[SDL2](https://www.libsdl.org/download-2.0.php),
[SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/),
[SDL2_image](https://www.libsdl.org/projects/SDL_image/), and
[SDL2_mixer](https://www.libsdl.org/projects/SDL_mixer/).

This project supports a local dependency link, download the development dependencies and unzip them inside a `deps`
folder at the root of this project, this will allow the project to link and build the project successfully.

Additionally, you must remove the `zlib1.dll` from both binary directories of `SDL2_ttf`, they're older than `SDL2_image`'s
and cause runtime errors when loading images, as `inflateValidate` does not exist in that version.


---

## Lint

### Windows

```shell
$ python .\\tools\\cpplint.py --quiet --recursive Drakhtar
```

### Linux or Mac

```
$ python ./tools/cpplint.py --quiet --recursive Drakhtar
```

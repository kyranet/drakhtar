# Drakhtar

A game built on top of SDL2.

---

## Build Pre-requisites

### Debian/Ubuntu

```
$ apt-get install libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev libsdl2-mixer-dev
```

### FreeBSD

```shell
$ pkg install libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev libsdl2-mixer-dev
```

### OS X

```shell
$ brew install sdl2 sdl2-ttf sdl2-image sdl2-mixer
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

### Linux or Mac

```
$ python ./tools/cpplint.py --quiet --recursive Drakhtar
```

### Windows

```shell
$ python .\\tools\\cpplint.py --quiet --recursive Drakhtar
```

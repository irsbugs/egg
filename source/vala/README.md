# Vala

**Egg Timer written in Vala.**

## Installation of Vala

Install vala on a linux/debian based system with:
```
sudo apt install valac
```

## Compiling Vala source code

The source file is *egg.vala*.

The application *valac* is used to compile the vala source code to become an executable image.
On linux the command...
```
$ valac egg.vala
```
...will produce the executable file *egg*. This may be run with:
```
$ ./egg
```

Valac takes a *egg.vala* source file and converts it *C* source code which it writes to the temporary file *egg.c*. It then uses the GNU Compiler Collection (*gcc*) to compile the *egg.c* to be the executable *egg* file. The temporary *egg.c* file is normally deleted as part of this operation. However with the command line option *--save-temps* the *egg.c* file is preserved for you to review. Use the following compile command to preserve the *egg.c* file:
```
$ valac --save-temps egg.vala
```

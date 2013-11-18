simple3dgeom
============

A very simple C++ templated library for 3D geometry with zero dependencies. Supports pre-C++0x.

Caveats
------------
Note that due to the zero-dependency requirement, there are no 'unit tests' per se.
However, you can compile and run simpletests.cpp instead as it tests basic functionality.

Also, the library doesn't differentiate between a 'point' and a 'vector',
because template aliases require a newer C++ standard.

Usage
------------
To use the library, simply include `simple3dgeom.h` in your file.
There is an additional file, `simple3dgeom.tpp` that implements most of the real functionality,
so that the header file is easier to navigate and read.
You also need that file present in the same directory as `simple3dgeom.h` to use the library.

Precision
------------
There is support for specifying 'precision' through a template argument. This is used when comparing points.

There are two classes included for comparators - TrivialNumberComparator (which does the default type comparison)
and DefaultNumberComparator, which takes an integer template parameter for 

Scope
------------
The library is very small in scope and only implements the linear space structure of the 3D space and 3D rotations.

***Note***
That this library was written awhile back and I haven't really used it since.

Contributing
------------
If you have found a bug, please report it here in Github, or (even better) fix it
and make a pull request.
Pull requests with edits that don't require newer C++ standard or new dependencies
and don't significantly increase the scope of the library are very welcome!

If requested, I will add any contributor to the README.


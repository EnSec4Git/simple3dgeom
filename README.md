simple3dgeom
============

A minimalistic C++ templated library for 3D geometry with zero dependencies. Supports pre-C++0x.

Caveats
------------
Note that due to the zero-dependency requirement, there are no 'unit tests' per se.
However, you can compile and run simpletests.cpp instead as it tests basic functionality.

Also, the library doesn't differentiate between a 'point' and a 'vector',
because template aliases require a newer C++ standard. Therefore, it is the programmer's
duty to understand (and take care of) any difference between affine and vector space.

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
and DefaultNumberComparator, which takes an integer template parameter for the exponent of the precision
(that is to which exponent one must take 10, so that it is "equal" to zero).
***Note***
The DefaultNumberComparator is suboptimal in performance, as it relies on the pow() function to perform comparisons.
This is due to limitations in C++ templates, which disallows floating-point arithmetics.
If possible, use your own implementation for fixed values of the exponent.

Template arguments
------------
The library supports arbitrary types that implement the required operations, in particular any
type that implements "Field" operations (+,-,* and / for non-zero elements) should work.
Therefore any arbitrary precision type should work out of the box as a template argument.

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
and don't significantly increase the scope of the library are very, very welcome!

If requested, I will add any contributor to the README.


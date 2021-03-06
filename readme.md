LIBDAIJOUBU
===========

LIBDAIJOUBU is a parser library for the Daijoubu programming language, written in C++.

Table of Contents
=================

1. [Changelog](https://github.com/majestic53/libdaijoubu#changelog)
2. [License](https://github.com/majestic53/libdaijoubu#license)

Changelog
=========

##Version 0.1.1532
*Updated: 8/4/2015*

* Implemented control enumeration routines (incomplete)

*Updated: 8/3/2015*

* Implemented statement enumeration routines (incomplete)
* Added proper syntactical error checking in enumeration routines
* Added additional token types

##Version 0.1.1531
*Updated: 8/2/2015*

* Implemented statement enumeration routines (incomplete)
* Added order and special flags to tokens
* Fixed a bug in simple dialect lexer operator enumeration
	* Unary operators ('++' | '--') used with an underscore prefixed identifier (ie. '++_abc' or similar) would be interpreted incorrectly.

*Updated: 8/1/2015*

* Implemented base statement enumeration routine
* Added additional parser enumeration routines (incomplete)

*Updated: 7/31/2015*

* Added parser enumeration routines (incomplete)
* Added support for simple dialect unary numeric
* Added parser grammar (inpcomplete)
* Added statement/native call token type

*Updated: 7/30/2015*

* Added parser enumeration routines (incomplete)
* Added statement helper routines
* Minor code cleanup

*Updated: 7/29/2015*

* Added parser class routines (incomplete)
* Added component tests

*Updated: 7/28/2015*

* Added parser class routines (incomplete)

*Updated: 7/27/2015*

* Added parser class (incomplete)
* Aligned with simple dialect

##Version 0.1.1530
*Updated: 7/23/2015*

* Added node factory class

*Updated: 7/22/2015*

* Added node class
* Aligned lexer grammar with specification

*Updated: 7/21/2015*

* Added number token support
* Minor code cleanup

*Updated: 7/20/2015*

* Added operator/symbol token support

*Changelog truncated (see file history for full log)*

License
======

Copyright(C) 2015 David Jolly <majestic53@gmail.com>

libdaijoubu is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

libdaijoubu is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

[![Build Status](https://travis-ci.org/pamarcos/triplet_challenge.svg?branch=master)](https://travis-ci.org/pamarcos/triplet_challenge)

# Triplet Challenge

*Triplet Challenge*'s goal is to encourage people to implement a small task in the programming language of their choice aiming at speed and low memory consumption. It borns from reading this [post](https://elixirforum.com/t/i-failed-my-tech-challenge-today-for-a-job-interview-i-dont-think-i-was-given-a-fair-chance/17928) about the tech challenge of an interview.

## Definition

1. The program takes an **UTF-8 file in English** as the only parameter. e.g.`./triplet_challenge pg2008.txt`
2. The output of the program are the top three triplet of words used along with their cadence:
<pre>
this is fine - 1337
call me maybe - 567
bring them back - 133
</pre>
3. Ignore any non-English letter, punctuation and line ending
4. Triplets are case-insensitive. Hence, `CaLL mE mAyBE` and `call me maybe` should be considered as the same triplet

## Data

[Origin Of Species](http://www.gutenberg.org/cache/epub/2009/pg2009.txt)

## License

**GPLv3**

Copyright (C) 2018 Pablo Marcos Oltra

triplet_challenge is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

triplet_challenge is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with triplet_challenge.  If not, see <http://www.gnu.org/licenses/>.

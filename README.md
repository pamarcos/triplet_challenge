[![Build Status](https://travis-ci.org/pamarcos/triplet_challenge.svg?branch=master)](https://travis-ci.org/pamarcos/triplet_challenge)

# Triplet Challenge

*Triplet Challenge*'s goal is to encourage people to implement a small task in the programming language of their choice aiming at speed and low memory consumption. It borns from reading this [post](https://elixirforum.com/t/i-failed-my-tech-challenge-today-for-a-job-interview-i-dont-think-i-was-given-a-fair-chance/17928) about the tech challenge of an interview. The output of this experiment is to see how even a simple challenge can be implemented in many different ways with a wide variety of results. It would be interesting to see how much we can squeeze of the CPU to get the program to complete its task as fast as possible while maintaining a low memory footprint.

If you have any doubts or suggestions about the challenge, please do not hesite and open an issue to discuss it.

## Definition of the problem

First let's define what we are going to consider a triplet for this challenge: a triplet is a tuple of 3 consecutive words in the text.

1. The program takes an **UTF-8 file in English** as the only parameter. e.g.`./triplet_challenge pg2009.txt`.
2. The output of the program are the top 3 triplet of words used along with the number of times they are repeated:
<pre>
this is fine - 1337
call me maybe - 567
bring them back - 133
</pre>
3. Since we assume English, ignore any non alphanumeric character except `'`. This means `this - is?= fine` should be interpreted as `this is fine`.
4. Triplets are case-insensitive. Hence, `CaLL mE mAyBE` and `call me maybe` should be considered as the same.

## Requirements

1. You can use any programming language, as long as it can be run on Linux. Why Linux? Because the Continuous Integration system that we are all going to use will use a Linux machine. This is done like that so that we all play with the same context. Do take into account that using languages that require a virtual machine (e.g. Java, C#, Python, JavaScript, Ruby) will most likely result in a non-negligible startup time and overhead in terms of RAM usage. Feel free to tweak the parameters of the virtual machine to optimize that.
2. You can't use any 3rd-party library for the task. Even a simple one. That means, no `npm`, `pip`, `conan`, or whatever. The reasoning for this is that the task is small enough to be done with what the language offers and so that others can easily understand in the vanilla version of the language what's happening under the hoods without any extra knowledge of frameworks or libraries.
3. The file we will use to benchmark our program will be the free book [The Origin of Species by Means of Natural Selection by Charles Darwin](http://www.gutenberg.org/cache/epub/2009/pg2009.txt). The file is already included in the repo, so there is no need to download it separately. Its size is 1270822 bytes, containing 212199 words and 157858 triplets. The output of `triplet_challenge` using this file in my solution is:
<pre>
of the same - 320
the same species - 130
conditions of life - 125
</pre>
4. Do not make any assumptions regarding the content or size of the file.

## How to compete

1. Fork this repo.
2. Sign-in to [Travis CI](https://travis-ci.org) using your GitHub credentials. Enable the `triplet_challenge` project in [Travis CI repositories](https://travis-ci.org/account/repositories) so that it starts tracking the project to build new commits. If you don't see there your `triplet_challenge` project yet, try the `Sync account` button on the top left.
3. Create a new branch for your work. e.g `git checkout -b java`. Do not commit to the master branch, so that you can easily fetch for updates from original repo, rebase, etc. Also, this makes it easier to others to add your remote to their already-existing repo and check out your work.
4. Implement your solution in the language of your choice. Use a different directory for unit tests and the rest, since the `src` directory is the one that will be used (by default) to count the lines of code of your solution. Please ensure you license all your code with the GPLv3 license and give credit if you are modifying an existing solution. One of this exercise's goal is that people can learn from other's code and improve it, without taking advantage of it.
5. Test your solution against the `pg2009.txt` file, write unit tests if needed, etc.
6. Once you are happy with your solution, modify the [.travis.yml](https://github.com/pamarcos/triplet_challenge/blob/master/.travis.yml) file that Travis CI will use to build and benchmark your solution. Take into account that all our solutions will use the same hardware running Ubuntu 16.04 on a **2-core Intel(R) Xeon(R) CPU @ 2.30GHz with 7.5GB of RAM**. You may need a few attempts to get the Travis CI configuration right if you have never used it before. I'd suggest to use an Ubuntu 16.04 docker container to test which packages need to be downloaded.
7. Push your new branch to your GitHub fork.
8. Check the build on [https://travis-ci.org/[user]/triplet_challenge/builds](https://travis-ci.org/[user]/triplet_challenge/builds). Pay attention the log to see whether it succeded or not and check out the benchmark results.
9. If you want to participate in the public ladder, create a PR to the original `triplet_challenge` repo or open an issue with all the details needed to add a new row with your results.
10. Feel free to have a different solution for each category in the ladder. The easiest way is to create a new branch to compete in each category.

## Benchmark on Travis CI

The `script` part of Travis CI is the one that compiles your program. This is the part you should modify, along with the `addons:apt:packages` that you need to install on Ubuntu. The `after_script` part should never be modified, since it ensures we all execute the benchmark with the same conditions. This part does the following:

1. Report the CPU info, in case it ever changes.
2. Count the number of lines of code in the `src` directory using [cloc](https://github.com/AlDanial/cloc).
3. Run the `triplet_challenge` binary once to check out the output.
4. Benchmark the `triplet_challenge` binary using [hyperfine](https://github.com/sharkdp/hyperfine). We run the application 3 times to ensure the IO is cached (warmp up runs) and then compute the average of the next 10 runs.
5. Run the `triplet_challenge` binary using [Valgrind Massif](http://valgrind.org/docs/manual/ms-manual.html) to collect the actual RAM usage made by the application and show the results.

## Ladder

There are 3 main areas that I think would be interesting to compare: speed, memory and lines of code (without comments):

### Speed
|#|User|Language|Time|Memory|LOC|Source|Build|
|-|----|--------|---|----|------|------|-----|
|1|[pamarcos](https://github.com/pamarcos)|C++|169.2 ms|16.23 MiB|143|[Repo](https://github.com/pamarcos/triplet_challenge/tree/master)|[Build](https://travis-ci.org/pamarcos/triplet_challenge/jobs/460379027)|
|2|[javsanchez](https://github.com/javsanchez)|C#|848.6 ms|Valgrind error|100|[Repo](https://github.com/javsanchez/triplet_challenge/tree/C%23-Implementation)|[Build](https://travis-ci.org/javsanchez/triplet_challenge/builds/460853924)|
|3|[javsanchez](https://github.com/javsanchez)|Python|1199 ms|8.425 MiB|47|[Repo](https://github.com/javsanchez/triplet_challenge/tree/Python-Implementation)|[Build](https://travis-ci.org/javsanchez/triplet_challenge/builds/460852222)|

### Memory
|#|User|Language|Memory|Time|LOC|Source|Build|
|-|----|--------|---|----|------|------|-----|
|1|[javsanchez](https://github.com/javsanchez)|Python|8.425 MiB|1199 ms|47|[Repo](https://github.com/javsanchez/triplet_challenge/tree/Python-Implementation)|[Build](https://travis-ci.org/javsanchez/triplet_challenge/builds/460852222)|
|2|[pamarcos](https://github.com/pamarcos)|C++|16.23 MiB|169.2 ms|143|[Repo](https://github.com/pamarcos/triplet_challenge/tree/master)|[Build](https://travis-ci.org/pamarcos/triplet_challenge/jobs/460379027)|
|3|[javsanchez](https://github.com/javsanchez)|C#|Valgrind error|848.6 ms|100|[Repo](https://github.com/javsanchez/triplet_challenge/tree/C%23-Implementation)|[Build](https://travis-ci.org/javsanchez/triplet_challenge/builds/460853924)|

### Lines of code
|#|User|Language|LOC|Time|Memory|Source|Build|
|-|----|--------|---|----|------|------|-----|
|1|[javsanchez](https://github.com/javsanchez)|Python|47|1199 ms|8.425 MiB|[Repo](https://github.com/javsanchez/triplet_challenge/tree/Python-Implementation)|[Build](https://travis-ci.org/javsanchez/triplet_challenge/builds/460852222)|
|2|[javsanchez](https://github.com/javsanchez)|C#|100|848.6 ms|Valgrind error|[Repo](https://github.com/javsanchez/triplet_challenge/tree/C%23-Implementation)|[Build](https://travis-ci.org/javsanchez/triplet_challenge/builds/460853924)|
|3|[pamarcos](https://github.com/pamarcos)|C++|143|169.2 ms|16.23 MiB|[Repo](https://github.com/pamarcos/triplet_challenge/tree/master)|[Build](https://travis-ci.org/pamarcos/triplet_challenge/jobs/460379027)|

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

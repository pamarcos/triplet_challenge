#!/bin/bash

set -eu

sudo apt-get update
sudo apt-get install time cloc

wget https://github.com/sharkdp/hyperfine/releases/download/v1.5.0/hyperfine_1.5.0_amd64.deb && sudo dpkg -i hyperfine_1.5.0_amd64.deb
wget https://github.com/pamarcos/triplet_challenge_stats/releases/download/continuous/triplet_challenge_stats.tar.gz && tar xvzf triplet_challenge_stats.tar.gz

lscpu
cloc $SRC_DIR

# 3 runs to warm up
for i in `seq 1 3`; do 
    $TRIPLET_CHALLENGE
done

# Benchmark speed
./triplet_challenge_stats clear
hyperfine -r 30 "LD_PRELOAD=./triplet_challenge_preload.so $TRIPLET_CHALLENGE"
./triplet_challenge_stats read

# Benchmark memory using GNU Time (Maximum resident set size)
$(which time) -v $TRIPLET_CHALLENGE

#!/bin/bash

set -eu

wget https://raw.githubusercontent.com/pamarcos/triplet_challenge/master/expected_result.txt
$TRIPLET_CHALLENGE | tail -n 3 | diff -u expected_result.txt - # Check that the result is the expected one

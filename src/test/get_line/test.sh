#!/bin/sh

set -e

./main.exe "$1" | cmp -s "$1"

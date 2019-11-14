#!/usr/bin/env bash

shopt -s globstar
clang-format -style=file -i **/*.cpp **/*.h

#!/bin/sh

while [ "$1" ]; do
  DO_RUN=true ./compile.sh lesson/$1.cpp
  shift
done

#!/bin/bash

for FILE in $(ls ./src); do source-highlight -f latexcolor -i ./src/$FILE -o ./tex/${FILE%.*}.tex; done
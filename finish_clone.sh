#!/bin/bash

if [ ! -d ".git" ]; then
    echo "Questo script deve essere eseguito nella directory della repository clonata."
    exit 1
fi
git submodule update --init --recursive
git submodule update --recursive --remote
echo "Complete Clone!"
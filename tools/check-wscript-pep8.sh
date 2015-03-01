#! /bin/bash

if hash pep8 2>/dev/null; then
    find ../ -type f -name "wscript" | xargs pep8
else
    echo "pep8 is not installed, cannot check wscript files for pep8 conformity"
fi

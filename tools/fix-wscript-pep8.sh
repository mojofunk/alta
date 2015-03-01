#! /bin/bash

if hash pep8 2>/dev/null; then
    find ../ -type f -name "wscript" | xargs autopep8 -i -a
else
    echo "autopep8 is not installed, cannot fix wscript files for pep8 conformity"
fi

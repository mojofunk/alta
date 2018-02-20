#! /bin/bash

if hash pycodestyle 2>/dev/null; then
    find ../ -type f -name "wscript" | xargs pycodestyle
else
    echo "pycodestyle is not installed, cannot check wscript files for pep8 conformity"
	echo "try $ sudo pip install pycodestyle"
fi

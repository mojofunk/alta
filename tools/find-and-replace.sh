#! /bin/bash

if hash sed 2>/dev/null; then
    find ../src/mojo -type f | xargs sed -i -e "$@"
else
    echo "sed is not installed, cannot find and replace using expression"
fi

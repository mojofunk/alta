#! /bin/bash

if hash clang-format 2>/dev/null; then
    find ../src -type f -name "*.?pp" | xargs clang-format -i "$@"
else
    echo "clang-format is not installed, cannot automatically format source code"
fi

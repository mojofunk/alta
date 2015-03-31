#!/bin/bash

./clean.sh
./configure-debug.sh && ./build.sh -j2 || exit 1
./clean.sh
./configure-debug-amalgamated.sh && ./build.sh -j2 || exit 1
./clean.sh
./configure-debug-tests.sh && ./build.sh -j2 || exit 1
./clean.sh
./configure-debug-tests-static.sh && ./build.sh -j2 || exit 1
./clean.sh
./configure-debug-tests-amalgamated.sh && ./build.sh -j2 || exit 1
./clean.sh
./configure-debug-single-tests.sh && ./build.sh -j2 || exit 1
./clean.sh
./configure-debug-single-tests-static.sh && ./build.sh -j2 || exit 1
./clean.sh
#./configure-debug-gtkmm-ui.sh && ./build.sh -j2 || exit 1
#./clean.sh
#./configure-debug-gtkmm-ui-static.sh && ./build.sh -j2 || exit 1
#./clean.sh
#./configure-debug-gtkmm-ui-amalgamated.sh && ./build.sh -j2 || exit 1
#./clean.sh
./configure-release.sh && ./build.sh -j2 || exit 1
./clean.sh

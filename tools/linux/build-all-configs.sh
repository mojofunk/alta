#!/bin/bash

./clean.sh
./configure-debug.sh && ./waf.sh -j2 || exit 1
./clean.sh
./configure-debug-static.sh && ./waf.sh -j2 || exit 1
./clean.sh
./configure-debug-amalgamated.sh && ./waf.sh -j2 || exit 1
./clean.sh
./configure-debug-tests.sh && ./waf.sh -j2 || exit 1
./clean.sh
./configure-debug-tests-amalgamated.sh && ./waf.sh -j2 || exit 1
./clean.sh
./configure-debug-gui.sh && ./waf.sh -j2 || exit 1
./clean.sh
./configure-debug-gui-static.sh && ./waf.sh -j2 || exit 1
./clean.sh
./configure-debug-gui-amalgamated.sh && ./waf.sh -j2 || exit 1
./clean.sh
./configure-release.sh && ./waf.sh -j2 || exit 1
./clean.sh

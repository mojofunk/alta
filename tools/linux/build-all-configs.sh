#!/bin/bash

./clean.sh
./configure-debug.sh && ./waf.sh -j2 || exit 1
./clean.sh
./configure-debug-amalgamated.sh && ./waf.sh -j2 || exit 1
./clean.sh
./configure-debug-tests.sh && ./waf.sh -j2 || exit 1
./clean.sh
./configure-debug-tests-static.sh && ./waf.sh -j2 || exit 1
./clean.sh
./configure-debug-tests-amalgamated.sh && ./waf.sh -j2 || exit 1
./clean.sh
#./configure-debug-gtkmm-ui.sh && ./waf.sh -j2 || exit 1
#./clean.sh
#./configure-debug-gtkmm-ui-static.sh && ./waf.sh -j2 || exit 1
#./clean.sh
#./configure-debug-gtkmm-ui-amalgamated.sh && ./waf.sh -j2 || exit 1
#./clean.sh
./configure-release.sh && ./waf.sh -j2 || exit 1
./clean.sh

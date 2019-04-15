#!/bin/bash
#
# $Id: atlas_build_run.sh.in 725450 2016-02-22 09:40:30Z krasznaa $
#
# This script is used during the build to set up a functional runtime
# environment for running scripts/executables.
#

# Transmit errors:
set -e

# Set up the environment:
source /home/abes/tutorial2017/build/x86_64-centos7-gcc62-opt/setup.sh || exit 1

# Run the command:
exec $* || exit 1

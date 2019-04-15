# $Id: setup.csh.in 734659 2016-04-07 17:21:52Z krasznaa $
#
# Script providing a functional runtime environment for project
# WorkDir when sourced from TCSH.
#

# Make sure that we run in (T)CSH:
set sourced=($_)
if ( "$sourced" == "" ) then
    echo "ERROR: This script must be sourced from TCSH"
    return 1
endif

# Get the name of the directory of the script:
set thisdir=`dirname $sourced[2]`
unset sourced

# Decide about the environment status variable to be used:
set ENV_VAR=WorkDir_SET_UP
if ( "$*" == "extonly" ) then
    set ENV_VAR=WorkDir_EXTONLY_SET_UP
else if ( "$*" == "relonly" ) then
    set ENV_VAR=WorkDir_RELONLY_SET_UP
endif

# Prevent the script from being called multiple times:
if ( ! `eval echo \$\?$ENV_VAR` ) then

    # Set the variable now:
    eval "setenv $ENV_VAR 1"

    # Set up the project's main directory:
    setenv WorkDir_DIR `cd $thisdir && pwd`
    unset thisdir

    # Extract directory names relevant for the rest of the operations:
    setenv WorkDir_PLATFORM `basename $WorkDir_DIR`
    set helper1=`dirname $WorkDir_DIR`
    set helper2=`dirname $helper1`
    setenv WorkDir_VERSION `basename $helper2`
    unset helper1 helper2

    # Base project(s) used for the build of WorkDir:
    set WorkDir_BASEPROJECTS=" AtlasOffline"

endif

# Clean up:
unset ENV_VAR

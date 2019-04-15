# $Id: ProjectConfig-version.cmake.in 711151 2015-11-27 12:00:55Z krasznaa $

# Installed Version as set from CMake:
set( PACKAGE_VERSION "21.0.20" )
set( WorkDir_VERSION ${PACKAGE_VERSION} )

# Check whether the requested PACKAGE_FIND_VERSION is compatible with this
# installed version:
if( "${PACKAGE_VERSION}" VERSION_LESS "${PACKAGE_FIND_VERSION}" )
   set( PACKAGE_VERSION_COMPATIBLE FALSE )
else()
   set( PACKAGE_VERSION_COMPATIBLE TRUE )
   if( "${PACKAGE_VERSION}" VERSION_EQUAL "${PACKAGE_FIND_VERSION}" )
      set( PACKAGE_VERSION_EXACT TRUE )
   endif()
endif()

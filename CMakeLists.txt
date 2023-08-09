cmake_minimum_required (VERSION 3.20)

if(NOT RELEASE_VERSION)
  set(RELEASE_VERSION 0.0.1)
endif()

project(tkgl 
  VERSION ${RELEASE_VERSION}
  LANGUAGES CXX
)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# lib
add_subdirectory(lib)

# demo
IF (BUILD_DEMO STREQUAL ON)
  add_subdirectory(demo)
ENDIF()

# test
IF (BUILD_TEST STREQUAL ON)
  enable_testing()
  add_subdirectory(test)
ENDIF()

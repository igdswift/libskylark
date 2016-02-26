cmake_minimum_required(VERSION 2.8.7)
project(libskylark)

option(libskylark_docs "Build all of libskylark's docs." ON)
option(libskylark_tests "Build all of libskylark's tests." ON)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(FindCURL)

set(CMAKE_C_FLAGS_RELEASE "-O3")
set(CMAKE_C_FLAGS_MINSIZEREL "-Os")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

# Set project version using Git tag and hash.
execute_process(
  COMMAND git describe --dirty --tags --always
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  RESULT_VARIABLE GIT_VERSION_FOUND
  ERROR_QUIET
  OUTPUT_VARIABLE GIT_VERSION
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
if (GIT_VERSION_FOUND)
  set(VERSION "unknown")
else (GIT_VERSION_FOUND)
  set(VERSION ${GIT_VERSION})
endif (GIT_VERSION_FOUND)

message(STATUS "libskylark version: ${VERSION}")

# Clang/GCC have slight different flag names.
if ("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
  set(CMAKE_C_FLAGS "-Wall -Wextra -Wno-strict-prototypes -Wno-unknown-warning-option -Werror -std=gnu99 ${CMAKE_C_FLAGS}")
elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
  set(CMAKE_C_FLAGS "-Wall -Wextra -Wno-strict-prototypes -Werror -std=gnu99 ${CMAKE_C_FLAGS}")
elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
  message( SEND_ERROR "Unsupported platform: Windows." )
endif()

add_subdirectory(src)
if (libskylark_docs)
  add_subdirectory(docs)
endif ()
if (libskylark_tests)
  add_subdirectory(test)
endif ()

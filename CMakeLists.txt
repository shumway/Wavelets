cmake_minimum_required (VERSION 2.6)

project (WAVELETS)
set (WAVELETS_VERSION_MAJOR 0)
set (WAVELETS_VERSION_MINOR 1)


configure_file (
  "${WAVELETS_SOURCE_DIR}/config.h.in"
  "${WAVELETS_BINARY_DIR}/config.h"
)

INCLUDE_DIRECTORIES(${WAVELETS_BINARY_DIR})

set(EXECUTABLE_OUTPUT_PATH ${WAVELETS_BINARY_DIR}/bin)

add_subdirectory(src)

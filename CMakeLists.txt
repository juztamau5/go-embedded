project(ipfs-embedded)

cmake_minimum_required(VERSION 2.8)

enable_language(CXX)

################################################################################
#
#  CMake modules
#
################################################################################

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(Go 1.5 REQUIRED)
include(ExternalProject)

################################################################################
#
#  Configure Go and build IPSF
#
################################################################################

if (GO_FOUND)
  # IPSF repo, without the leading protocol
  set(IPSF_REPO github.com/juztamau5/go-ipfs)

  # For more information, run `go help environment`
  set(ENV{GOPATH} "${CMAKE_BINARY_DIR}")

  # Available OSes: linux, darwin, windows, android, netbsd, ...?
  set(ENV{GOOS} linux) # TODO

  # Available architectures: amd64, 386, arm, arm64, ppc64, ppc64le, ...?
  set(ENV{GOARCH} amd64) # TODO

  # cgo is disabled by default when cross-compiling (https://golang.org/cmd/cgo)
  set(ENV{CGO_ENABLED} 1)

  message(STATUS "Fetching and building IPFS for $ENV{GOOS}_$ENV{GOARCH}")

  execute_process(COMMAND ${GO_EXECUTABLE} get -u -v -buildmode=c-archive ${IPSF_REPO}/cmd/ipfs)

  set(IPSF_OUTPUT_DIR "$ENV{GOPATH}/pkg/$ENV{GOOS}_$ENV{GOARCH}/${IPSF_REPO}/cmd")

  set(IPSF_LIBRARY "${IPSF_OUTPUT_DIR}/ipfs${CMAKE_STATIC_LIBRARY_SUFFIX}")

  if (NOT EXISTS ${IPSF_LIBRARY})
    message(FATAL_ERROR "Can't find IPFS library: ${IPSF_LIBRARY}")
  endif()

  include_directories(${IPSF_OUTPUT_DIR})
else()
  # Change warning to status when go-ipfs no longer required
  message(WARNING "Go not found. Continuing without go-ipfs")
endif()

################################################################################
#
#  Add sources, headers and libraries
#
################################################################################

include_directories(${PROJECT_SOURCE_DIR}/include)

set(IPSF_EMBEDDED_SOURCES)

set(STANDALONE_SOURCES
    src/main.cpp)

set(LIBRARY_SOURCES
    src/lib.cpp)

set(DEPENDENCIES
    ${IPSF_LIBRARY}
    pthread)

################################################################################
#
#  Standalone target
#
################################################################################

add_executable(ipfs_embedded ${IPSF_EMBEDDED_SOURCES} ${STANDALONE_SOURCES})

target_link_libraries(ipfs_embedded ${DEPENDENCIES})

################################################################################
#
#  Library target
#
################################################################################

add_library(ipfs STATIC ${IPSF_EMBEDDED_SOURCES} ${LIBRARY_SOURCES})

################################################################################
#
#  Warnings
#
################################################################################

if(MSVC)
    # Force to always compile with W4
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    # Update if necessary
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -Wpedantic")
endif()

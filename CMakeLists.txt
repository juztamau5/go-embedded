project(ipfs-embedded)

cmake_minimum_required(VERSION 2.8)

enable_language(CXX)

################################################################################
#
#  CMake modules
#
################################################################################

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(Git)
find_package(Go 1.5 REQUIRED)
include(ExternalProject)

################################################################################
#
#  Build IPSF
#
################################################################################

set(IPFS_REPO https://github.com/ipfs/go-ipfs)
set(IPFS_VERSION master) # Must use master, go get can't deal with branches or tags

# Resolve the version to a commit
execute_process(COMMAND ${GIT_EXECUTABLE} ls-remote
                https://github.com/ipfs/go-ipfs ${IPSF_VERSION}
                RESULT_VARIABLE RESULT
                OUTPUT_VARIABLE OUTPUT)

if("${OUTPUT}" STREQUAL "")
  message(FATAL_ERROR "Failed to determine IPSF commit hash for ${IPSF_VERSION}")
endif()

string(REGEX MATCHALL "^([a-f0-9]+)" IPSF_COMMIT ${OUTPUT})

if("${IPSF_COMMIT}" STREQUAL "")
  message(FATAL_ERROR "Failed to extract commit hash from \"${OUTPUT}\"")
endif()

# Set link flags
#set(IPSF_LDFLAGS "-ldflags=\"-X github.com/ipfs/go-ipfs/repo/config.CurrentCommit=${IPSF_COMMIT}\"")

externalproject_add(go-ipfs
                    GIT_REPOSITORY ${IPFS_REPO}
                    GIT_TAG ${IPFS_VERSION}
                    CONFIGURE_COMMAND ${GO_EXECUTABLE} get -u github.com/ipfs/go-ipfs/cmd/ipfs
                    BUILD_COMMAND cd cmd/ipfs && ${GO_EXECUTABLE} build -buildmode=c-archive "${IPSF_LDFLAGS}"
                    BUILD_IN_SOURCE 1)

################################################################################
#
#  Add sources, headers and libraries
#
################################################################################

set(IPSF_SOURCES)

set(STANDALONE_SOURCES
    src/main.cpp)

set(DEPLIBS)

################################################################################
#
#  Standalone target
#
################################################################################

add_executable(ipfs_embedded ${STANDALONE_SOURCES})

target_link_libraries(ipfs_embedded ${DEPLIBS})

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


cmake_minimum_required(VERSION 3.13)


project(NFS)

file(GLOB SOURCES_CORE "libraries/core/*.cpp" "libraries/core/*.hpp")
message( "${SOURCES_CORE}")
add_library(libnfs ${SOURCES_CORE})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)


file(GLOB SOURCES_CLIENT "libraries/client/*.cpp" "libraries/client/*.hpp")
add_library(client ${SOURCES_CLIENT})


file(GLOB SOURCES_SERVER "server/*.cpp" "server/*.hpp")
add_executable(server ${SOURCES_SERVER})


target_link_libraries(client libnfs)
target_link_libraries(server libnfs)

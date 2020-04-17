project(NFS)

file(GLOB SOURCES "src/*.cpp")

add_library(nfsclient lib.cpp ${SOURCES})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)


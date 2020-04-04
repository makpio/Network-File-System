project(NFS)

file(GLOB SOURCES "src/*.cpp")

add_library(test1 lib.cpp ${SOURCES})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)


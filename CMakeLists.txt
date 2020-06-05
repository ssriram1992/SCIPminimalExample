cmake_minimum_required(VERSION 3.3)

project(HelloWorld)

find_package(SCIP REQUIRED)
include_directories(${SCIP_INCLUDE_DIRS})

add_executable(clique
   src/clique.c)

target_link_libraries(clique ${SCIP_LIBRARIES})

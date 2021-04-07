cmake_minimum_required(VERSION 3.16)
project(GrapheneChat-Server)

file (GLOB SOURCE_FILES src/*.cpp)
file (GLOB HEADER_FILES src/*.h)

set (TARGET_NAME Server)

find_package(Threads REQUIRED)

include_directories (websocketpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

FIND_PACKAGE( Boost 1.40 COMPONENTS system REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

add_executable (${TARGET_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(${TARGET_NAME} ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})

cmake_minimum_required(VERSION 3.16)
project(GrapheneChat-Server)

if(UNIX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif(UNIX)

file (GLOB SOURCE_FILES src/*.cpp)
file (GLOB HEADER_FILES src/*.h)

set (TARGET_NAME Server)

if(UNIX)
link_libraries(sqlite3)

find_package(Threads REQUIRED)
find_package (SQLite3 REQUIRED)
find_library(SQLITE3_LIBRARY NAMES sqlite3)
if(SQLITE3_FOUND)
include_directories(${SQLite3_INCLUDE_DIR})

endif(SQLITE3_FOUND)
find_package(RapidJSON REQUIRED)
FIND_PACKAGE( Boost 1.40 COMPONENTS system REQUIRED )
endif(UNIX)

if(APPLE)
link_libraries(sqlite3)

find_package(Threads REQUIRED)
find_package (SQLite3 REQUIRED)
find_package(RapidJSON REQUIRED)
FIND_PACKAGE( Boost 1.40 COMPONENTS system REQUIRED )
endif(APPLE)

include_directories (websocketpp ${Boost_INCLUDE_DIR} ${SQLite3_INCLUDE_DIR} ${RapidJSON_INCLUDE_DIRS})

add_executable (${TARGET_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(${TARGET_NAME} ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
if(SQLITE3_FOUND)
target_link_libraries(${TARGET_NAME}${SQLITE3_LIBRARIES})
endif(SQLITE3_FOUND)

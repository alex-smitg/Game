# CMakeList.txt : CMake project for Game, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.13)

project ("Game")


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")




set(ASSETS_PATH "${CMAKE_SOURCE_DIR}/ASSETS")
add_definitions(-DASSETS_PATH="${ASSETS_PATH}")

add_executable (Game "Game.cpp" main.rc )

if(MSVC)
    set(CMAKE_RC_COMPILER "RC")
    target_sources(Game PRIVATE main.rc)
endif()

set(SCRIPT ${CMAKE_SOURCE_DIR}/packer.py)

add_custom_target(
    pack
    COMMAND ${SCRIPT}
)

add_dependencies(Game pack)

target_include_directories(Game PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/include/AL)

link_directories(${CMAKE_SOURCE_DIR}/lib/Debug)

file(GLOB_RECURSE LIBRARIES "${CMAKE_SOURCE_DIR}/lib/Debug/*.lib")
message(STATUS "Found libraries: ${LIBRARIES}")


target_link_libraries(Game PRIVATE ${LIBRARIES} opengl32 ${CMAKE_SOURCE_DIR}/lib/Debug/OpenAL32.lib)



# TODO: Add tests and install targets if needed.

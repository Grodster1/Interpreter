cmake_minimum_required(VERSION 3.0)

set(PROJ_NAME "plugins_4_program")
project(${PROJ_NAME})

include_directories(${PROJECT_SOURCE_DIR}/inc ${PROJECT_SOURCE_DIR}/../inc)
add_library(Interp4Move MODULE src/Interp4Move.cpp)
add_custom_command(TARGET Interp4Move POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy libInterp4Move.so /tmp/bk_downloads
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo " Utworzony zostal plugin:  libInterp4Move.so"
    COMMAND ${CMAKE_COMMAND} -E echo ""    
  )



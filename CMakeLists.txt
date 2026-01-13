cmake_minimum_required(VERSION 3.10) 

set(PROJ_NAME "cmds_interpreter")
project(${PROJ_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(XercesC 3.2.0 REQUIRED)
find_package(Threads REQUIRED)

add_subdirectory(plugin)

include_directories(${PROJECT_SOURCE_DIR}/inc)

add_executable(${PROJ_NAME} 
    src/main.cpp
    src/LibInterface.cpp
    src/Set4LibInterfaces.cpp
    src/Cuboid.cpp
    src/Scene.cpp
    src/ProgramInterpreter.cpp
    src/xmlinterp.cpp
    src/Configuration.cpp
    src/ComChannel.cpp
    src/Sender.cpp 
)

target_link_libraries(${PROJ_NAME} PRIVATE 
    Threads::Threads 
    ${CMAKE_DL_LIBS} 
    XercesC::XercesC
)

set_target_properties(${PROJ_NAME} PROPERTIES 
    LINK_FLAGS "-Wl,-rpath=./plugin"
)

add_custom_command(TARGET ${PROJ_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo " Utworzony zostal program:  ${PROJ_NAME}"
    COMMAND ${CMAKE_COMMAND} -E echo ""
)
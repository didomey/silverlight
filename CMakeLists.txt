cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 20)

project(silverlight C CXX)

#include(ExternalProject)

add_executable(silverlight)
wut_add_exports(silverlight exports.def)
wut_create_rpl(silverlight)

add_subdirectory(src)
add_subdirectory(deps/glm)
add_subdirectory(deps/fmt)

target_include_directories(silverlight PRIVATE src)

target_link_libraries(silverlight glm::glm fmt wut)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/silverlight.rpl"
    DESTINATION "${CMAKE_INSTALL_PREFIX}")

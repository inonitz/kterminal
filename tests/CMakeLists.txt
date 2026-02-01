cmake_minimum_required(VERSION 3.14)
project(test
    VERSION 0.0.1
    DESCRIPTION "C/C++ Programs to Test Functionality of kterminal"
    LANGUAGES C CXX
)


set(SOURCES
    source/main.cpp
)


add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
)

# The minimum C/C++ versions required for the library
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_compile_features(${PROJECT_NAME} PUBLIC c_std_11)


add_custom_target(run_tests
    COMMAND ./${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_CUSTOM_BUILD_OUTPUT_DIRECTORY}
)

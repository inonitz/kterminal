cmake_minimum_required(VERSION 3.14)
project(kterminal 
    VERSION 0.0.1
    DESCRIPTION "Kernel-Space Terminal Emulator"
    LANGUAGES C CXX
)


set(SOURCES
    source/fonts/fontstyle.c
    source/internal/fontrender.c
    source/internal/vterminal.c
)

set(HEADERS
    include/kterminal/fonts/fontstyle.h
    include/internal/fontrender.h
    include/internal/ringbuffer.h
    include/internal/types.h
    include/internal/vterminal.h
)


if(BUILD_SHARED_LIBS)
    add_library(${PROJECT_NAME} SHARED)
    target_compile_definitions(${PROJECT_NAME} PUBLIC KTERM_EXPORTS)
else()
    add_library(${PROJECT_NAME} STATIC)
    target_compile_definitions(${PROJECT_NAME} PUBLIC KTERM_STATIC_DEFINE)
endif()

add_library(kterminal::kterminal ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
target_sources(${PROJECT_NAME} PRIVATE ${HEADERS})
target_link_libraries(${PROJECT_NAME} PRIVATE UTIL2::util2)


# The minimum C/C++ versions required for the library
target_compile_features(${PROJECT_NAME} PUBLIC c_std_11)
if(BUILD_SHARED_LIBS)
    set_target_properties(${PROJECT_NAME} PROPERTIES 
        C_VISIBILITY_PRESET       hidden
        CXX_VISIBILITY_PRESET     hidden
        VISIBILITY_INLINES_HIDDEN ON
    )
endif()


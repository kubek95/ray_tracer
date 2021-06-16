file(GLOB SOURCES
     *.hpp
     *.cpp)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})
add_library(${CMAKE_PROJECT_NAME}_lib
            STATIC
            ${SOURCES})
target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    PRIVATE compiler_warnings
    )

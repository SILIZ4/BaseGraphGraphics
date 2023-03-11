add_library(${EXTENSION_NAME} svg.cpp vertex_layouts.cpp style.cpp)

set_target_properties(${EXTENSION_NAME} PROPERTIES
    LINKER_LANGUAGE CXX
    POSITION_INDEPENDENT_CODE TRUE
)
target_include_directories(${EXTENSION_NAME} PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
target_link_libraries(${EXTENSION_NAME} PUBLIC BaseGraph::core)

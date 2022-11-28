set(EXTENSION_NAME graphics)
add_library(${EXTENSION_NAME} svg.cpp vertex_layouts.cpp style.cpp)
target_link_libraries(${EXTENSION_NAME} core)
add_extension(${EXTENSION_NAME})

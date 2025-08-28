file(GLOB_RECURSE IMGUI_FILES ./*.h ./*.cpp)
add_library(imgui STATIC ${IMGUI_FILES})
target_include_directories(imgui PUBLIC .)

target_link_libraries(imgui PRIVATE SDL3::SDL3)

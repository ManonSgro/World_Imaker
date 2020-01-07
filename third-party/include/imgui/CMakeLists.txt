include_directories(include)
file(GLOB SRC_FILES
    include/*.h
    include/*.cpp
    examples/imgui_impl_opengl3.cpp
    examples/imgui_impl_sdl.cpp
    misc/cpp/imgui_stdlib.cpp
    misc/cpp/imgui_stdlib.h
)
add_library(imgui ${SRC_FILES})
target_compile_definitions(imgui PRIVATE IMGUI_IMPL_OPENGL_LOADER_GLEW)
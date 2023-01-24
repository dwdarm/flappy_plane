find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2 SDL2_image)

file(GLOB SRC "./*.cpp" "libs/*.cpp")
add_executable(flappy_plane ${SRC})
target_link_libraries(flappy_plane ${SDL2_LIBRARIES})
target_include_directories(flappy_plane PUBLIC ${SDL2_INCLUDE_DIRS})
target_compile_options(flappy_plane PUBLIC ${SDL2_CFLAGS_OTHER})
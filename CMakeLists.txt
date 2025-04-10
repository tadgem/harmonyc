cmake_minimum_required(VERSION 3.22)

project(harmonyc)
set (CMAKE_CXX_STANDARD 17)

# Add clang compile_commands.json for nvim
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
set(MI_BUILD_SHARED OFF CACHE INTERNAL "")
set(MI_BUILD_TESTS OFF CACHE INTERNAL "")
# Enable this to remove the examples + their dependencies (glm, assimp)
# set(BUILD_LVK_EXAMPLES OFF CACHE INTERNAL "Disable LVK Examples")
add_subdirectory(submodules/lvk)
add_subdirectory(submodules/flecs)
add_subdirectory(third_party/mimalloc)

set(harmonyc_libs lvk lvk-sdl flecs_static mimalloc-static)
set(harmonyc_definitions "EASTL_EABASE_DISABLED")
set(harmonyc_includes
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/mimalloc/include
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/mimalloc/src
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party
  ${CMAKE_CURRENT_SOURCE_DIR}/submodules/sdl/include
  ${CMAKE_CURRENT_SOURCE_DIR}/submodules/flecs/include
  ${CMAKE_CURRENT_SOURCE_DIR}/harmony/
  ${LVK_INCLUDES}
  ${LVK_SDL_INCLUDES}
)

function(add_harmony_exe exe_name entry_file)
	add_executable(${exe_name} ${entry_file})
	target_compile_definitions(${exe_name} PRIVATE ${harmonyc_definitions} )
	target_link_libraries(${exe_name} ${harmonyc_libs})
	target_include_directories(${exe_name} PRIVATE ${harmonyc_includes})
endfunction()

add_harmony_exe(harmonyc harmony/Entry.cpp)
add_harmony_exe(harmonyc_tests tests/CoreTests.cpp)

add_custom_command(
        TARGET harmonyc_tests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.bin
                ${CMAKE_CURRENT_BINARY_DIR}/test.bin)
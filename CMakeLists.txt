cmake_minimum_required(VERSION 3.22)

project(harmonyc)
set (CMAKE_CXX_STANDARD 17)

# Add clang compile_commands.json for nvim
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

add_subdirectory(submodules/lvk)
add_subdirectory(submodules/flecs)

set(harmonyc_libs lvk lvk-sdl flecs_static)
set(harmonyc_definitions "EASTL_EABASE_DISABLED")
set(harmonyc_includes
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/eastl/include
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/eastl/source
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

add_harmony_exe(harmonyc harmony/entry.cpp)
add_harmony_exe(harmonyc_tests tests/core_tests.cpp)
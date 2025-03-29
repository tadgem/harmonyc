cmake_minimum_required(VERSION 3.22)

project(harmonyc)
set (CMAKE_CXX_STANDARD 17)

# Add clang compile_commands.json for nvim
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

add_subdirectory(submodules/lvk)
add_subdirectory(submodules/flecs)

add_executable(harmonyc harmony/Entry.cpp)
add_executable(harmonyc_tests tests/harmony_tests.cpp)

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


target_compile_definitions(harmonyc PRIVATE ${harmonyc_definitions})
target_link_libraries(harmonyc ${harmonyc_libs})
target_include_directories(harmonyc PRIVATE ${harmonyc_includes})

target_compile_definitions(harmonyc_tests PRIVATE ${harmonyc_definitions})
target_link_libraries(harmonyc_tests ${harmonyc_libs})
target_include_directories(harmonyc_tests PRIVATE ${harmonyc_includes} ${CMAKE_CURRENT_SOURCE_DIR}/tests)

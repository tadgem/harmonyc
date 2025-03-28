cmake_minimum_required(VERSION 3.22)

project(harmonyc)
set (CMAKE_CXX_STANDARD 17)

# Add clang compile_commands.json for nvim
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

add_subdirectory(submodules/lvk)
add_subdirectory(submodules/flecs)

add_executable(harmonyc harmony/Entry.cpp)

target_compile_definitions(harmonyc PRIVATE "EASTL_EABASE_DISABLED")
target_link_libraries(harmonyc lvk lvk-sdl flecs_static)
target_include_directories(harmonyc PRIVATE
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

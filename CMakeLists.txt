cmake_minimum_required(VERSION 3.22)

project(harmonyc)
set (CMAKE_CXX_STANDARD 20)

# SDL Option Setting (TODO: Dont do this in root CMakeLists)
set(SDL_STATIC TRUE CACHE INTERNAL TRUE)
set(SDL_SHARED FALSE CACHE INTERNAL TRUE)
set(CMAKE_SUPPRESS_REGENERATION true)
set(SDL3_DISABLE_SDL3MAIN ON CACHE BOOL "Disable SDL Entrypoint")
set(SDL3_DISABLE_INSTALL ON CACHE BOOL "Disable SDL Install")
set(SDL3_DISABLE_UNINSTALL ON CACHE BOOL "Disable SDL Uninstall")

add_subdirectory(submodules/sdl)

add_executable(harmonyc entry.cpp)

target_compile_definitions(harmonyc PRIVATE "EASTL_EABASE_DISABLED")
target_link_libraries(harmonyc PRIVATE SDL3-static)
target_include_directories(harmonyc PRIVATE 
	${CMAKE_CURRENT_SOURCE_DIR}/third_party/eastl/include 
	${CMAKE_CURRENT_SOURCE_DIR}/third_party/eastl/source
	${CMAKE_CURRENT_SOURCE_DIR}/third_party/mimalloc/include 
	${CMAKE_CURRENT_SOURCE_DIR}/third_party/mimalloc/src
	${CMAKE_CURRENT_SOURCE_DIR}/submodules/sdl/include
)
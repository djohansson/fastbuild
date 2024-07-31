cmake_minimum_required(VERSION 3.10)

project(Fastbuild)

find_package(lz4 CONFIG REQUIRED)
find_package(xxHash CONFIG REQUIRED)
find_package(zstd CONFIG REQUIRED)

set(CMAKE_VERBOSE_MAKEFILE ON)

if(CMAKE_SYSTEM_NAME MATCHES "Darwin")
	# set(CMAKE_OSX_ARCHITECTURES arm64;x86_64)
	# set(CMAKE_OSX_SYSROOT $ENV{MACOS_SDK_PATH})
	add_compile_options("-D__OSX__")
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
	add_compile_options("-D__WINDOWS__")
	include_directories(PRIVATE "${PROJECT_SOURCE_DIR}/External/VSProjTypeExtractor")
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
	add_compile_options("-D__LINUX__")
endif()

add_compile_options(
	"$<$<CONFIG:RELEASE>:-DRELEASE>"
	"$<$<CONFIG:DEBUG>:-DDEBUG>"
	"-Wno-invalid-offsetof"
)

include_directories(PRIVATE "${PROJECT_SOURCE_DIR}/Code")

file(GLOB_RECURSE CORE_SRC_FILES CONFIGURE_DEPENDS
	"${PROJECT_SOURCE_DIR}/Code/Core/Env/*.cpp"
	"${PROJECT_SOURCE_DIR}/Code/Core/FileIO/*.cpp"
	"${PROJECT_SOURCE_DIR}/Code/Core/Math/*.cpp"
	"${PROJECT_SOURCE_DIR}/Code/Core/FileIO/*.cpp"
	"${PROJECT_SOURCE_DIR}/Code/Core/Mem/*.cpp"
	"${PROJECT_SOURCE_DIR}/Code/Core/Network/*.cpp"
	"${PROJECT_SOURCE_DIR}/Code/Core/Process/*.cpp"
	"${PROJECT_SOURCE_DIR}/Code/Core/Profile/*.cpp"
	"${PROJECT_SOURCE_DIR}/Code/Core/Reflection/*.cpp"
	"${PROJECT_SOURCE_DIR}/Code/Core/Strings/*.cpp"
	"${PROJECT_SOURCE_DIR}/Code/Core/Time/*.cpp"
	"${PROJECT_SOURCE_DIR}/Code/Core/Tracing/*.cpp"
)
file(GLOB_RECURSE FBUILD_CORE_SRC_FILES CONFIGURE_DEPENDS
	"${PROJECT_SOURCE_DIR}/Code/Tools/FBuild/FBuildCore/*.cpp"
)
file(GLOB_RECURSE FBUILD_SRC_FILES CONFIGURE_DEPENDS
	"${PROJECT_SOURCE_DIR}/Code/Tools/FBuild/FBuild/*.cpp"
)
add_executable(FBuild "${CORE_SRC_FILES}" "${FBUILD_CORE_SRC_FILES}" "${FBUILD_SRC_FILES}")
target_link_libraries(FBuild PRIVATE lz4::lz4 xxHash::xxhash zstd::libzstd)

install(TARGETS FBuild DESTINATION bin)

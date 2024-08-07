cmake_minimum_required(VERSION 3.10)

project(Fastbuild)

find_package(lz4 CONFIG REQUIRED)
find_package(xxHash CONFIG REQUIRED)
find_package(zstd CONFIG REQUIRED)

set(CMAKE_VERBOSE_MAKEFILE ON)

option(USE_CRT_NEW_DELETE "Use vanilla new & delete from C runtime" OFF)

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

if (USE_CRT_NEW_DELETE)
	add_compile_options("-DUSE_CRT_NEW_DELETE")
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

list(APPEND FBUILD_LIB_DEPENDENCIES lz4::lz4 xxHash::xxhash zstd::libzstd)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
	list(APPEND FBUILD_LIB_DEPENDENCIES advapi32 iphlpapi kernel32 shell32 user32 ws2_32)
endif()

add_executable(FBuild "${CORE_SRC_FILES}" "${FBUILD_CORE_SRC_FILES}" "${FBUILD_SRC_FILES}")
target_link_libraries(FBuild PRIVATE ${FBUILD_LIB_DEPENDENCIES})

install(TARGETS FBuild DESTINATION bin)

cmake_minimum_required(VERSION 3.12)

# Main Project
set(PROJECT_NAME ArrayPerformance)
project(${PROJECT_NAME})

# Unit Tests
set(UNIT_TEST_RUNNER UnitTestRunner)

# Files
set(HEADER_FILES sortutils.hpp)
set(SOURCE_FILES sortutils.cpp)
set(UNIT_TEST_FILES TestPerformance.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES} main.cpp)
add_executable(${UNIT_TEST_RUNNER} ${SOURCE_FILES} ${HEADER_FILES} ${UNIT_TEST_FILES})


# Minimum C++ Version
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
set_property(TARGET ${UNIT_TEST_RUNNER} PROPERTY CXX_STANDARD 20)

# Compiler Warning Options
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive-)
	target_compile_options(${UNIT_TEST_RUNNER} PRIVATE /W4 /permissive-)

	# Stack Size Increase
	set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/STACK:10000000")
	set_target_properties(${UNIT_TEST_RUNNER} PROPERTIES LINK_FLAGS "/STACK:10000000")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Wl,--stack,10000000)
    target_compile_options(${UNIT_TEST_RUNNER} PRIVATE -Wall -Wextra -pedantic -Wl,--stack,10000000)
endif()

# Automatically Apply Clang Format
find_program(CLANG_FORMAT "clang-format")
if (CLANG_FORMAT)
	message("CLANG-FORMAT found at: " ${CLANG_FORMAT})
	unset(SOURCE_FILES_PATHS)
	foreach(SOURCE_FILE ${SOURCE_FILES} ${HEADER_FILES} ${UNIT_TEST_FILES} main.cpp)
		get_source_file_property(WHERE ${SOURCE_FILE} LOCATION)
		set(SOURCE_FILES_PATHS ${SOURCE_FILES_PATHS} ${WHERE})
	endforeach()

	add_custom_target(
		ClangFormat
		COMMAND ${CLANG_FORMAT}
		-i
		-style=file
		${SOURCE_FILES_PATHS})

	add_dependencies(${PROJECT_NAME} ClangFormat)
else()
	message("Unable to find Clang-Format")
endif()


# Include Google Test Library
include(FetchContent)
FetchContent_Declare(
	googletest
	GIT_REPOSITORY 	https://github.com/google/googletest.git
	GIT_TAG			release-1.11.0
)

FetchContent_MakeAvailable(googletest)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)



# Include fmt Library
include(FetchContent)
FetchContent_Declare(
    fmt
    GIT_REPOSITORY    https://github.com/fmtlib/fmt.git
    GIT_TAG           9.1.0
)
FetchContent_MakeAvailable(fmt)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
target_link_libraries(${UNIT_TEST_RUNNER} gtest_main fmt::fmt)
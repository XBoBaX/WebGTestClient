cmake_minimum_required(VERSION 3.1)

set(PROJECT_NAME example_find_send)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -Wall")

# force static runtime libraries for msvc builds0
if(MSVC)
  set(variables 
    CMAKE_CXX_FLAGS_DEBUG
    CMAKE_CXX_FLAGS_RELEASE
	CMAKE_CXX_FLAGS_RELWITHDEBINFO
	CMAKE_CXX_FLAGS_MINSIZEREL
  )
  foreach(variable ${variables})
	if(${variable} MATCHES "/MD")
	  string(REGEX REPLACE "/MD" "/MT" ${variable} "${${variable}}")
	endif()
  endforeach()
endif()

#include_directories(../../libs)


set(SOURCE_FILES
	find_test.cpp
	main.cpp
	../../tests/environment.h
	../../libs/ReportingSystem.h
	../../libs/ReportingSystem/reportdriver.h
	../../libs/ReportingSystem/reportdriver.cpp
	../../libs/ReportingSystem/sqliteDriver.h
	../../libs/ReportingSystem/sqliteDriver.cpp

	)
	
################################
# CURL
################################

include_directories("../../tests/lib/curl-7.55.0/builds/libcurl-vc13-x64-release-dll-ipv6-sspi-winssl/include")
link_directories("../../tests/lib/curl-7.55.0/builds/libcurl-vc13-x64-release-dll-ipv6-sspi-winssl/lib")

list(APPEND LIBS libcurl wsock32 ws2_32)
list(APPEND DEPS curl_project)

add_definitions(-DCURL_STATICLIB)

################################
# SQL
################################

include_directories("../../tests/lib/SQLite")
link_directories("../../tests/lib/SQLite")

list(APPEND LIBS SQLite3)

#message(${SQLITE3_INCLUDE_DIRS})

################################
# Testing
################################
add_subdirectory(../../tests/lib/googletest build)

enable_testing()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

list(APPEND LIBS gtest gmock)

# Target

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${LIBS})

include_directories(../../libs)

# libcurl.dll to path with .exe
configure_file(../../tests/lib/curl-7.55.0/builds/libcurl-vc13-x64-release-dll-ipv6-sspi-winssl/bin/libcurl.dll ${CMAKE_CURRENT_BINARY_DIR}/Debug/libcurl.dll COPYONLY)

install(DIRECTORY
		${CMAKE_SOURCE_DIR}/libs/
		DESTINATION /usr/local/libs/${PROJECT_NAME}
		FILES_MATCHING PATTERN "*")
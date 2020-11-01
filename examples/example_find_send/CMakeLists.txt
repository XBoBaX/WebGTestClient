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

set(HEADER_FILES
	../../libs/WebGTestClient.h
	../../libs/WebGTestClient/WebDriver.h
	../../libs/WebGTestClient/by.h 
	../../libs/WebGTestClient/capabilities.h 
	../../libs/WebGTestClient/client.h 
	../../libs/WebGTestClient/client.inl  
	../../libs/WebGTestClient/conversions.h 
	../../libs/WebGTestClient/element.h
	../../libs/WebGTestClient/element.inl  
	../../libs/WebGTestClient/errors.h 
	../../libs/WebGTestClient/js_args.h 
	../../libs/WebGTestClient/keys.h 
	../../libs/WebGTestClient/response_status_code.h 
	../../libs/WebGTestClient/session.h 
	../../libs/WebGTestClient/session.inl 
	../../libs/WebGTestClient/types.h 
	../../libs/WebGTestClient/wait.h 
	../../libs/WebGTestClient/wait_match.h 
	../../libs/WebGTestClient/webdriver.h 
	../../libs/WebGTestClient/window.h 
	../../libs/WebGTestClient/picojson.h
	../../libs/WebGTestClient/browsers/chrome.h
	../../libs/WebGTestClient/detail/error_handling.h
	../../libs/WebGTestClient/detail/factories.h 
	../../libs/WebGTestClient/detail/factories_impl.h 
	../../libs/WebGTestClient/detail/finder.h 
	../../libs/WebGTestClient/detail/finder.inl 
	../../libs/WebGTestClient/detail/http_client.h 
	../../libs/WebGTestClient/detail/http_connection.h 
	../../libs/WebGTestClient/detail/http_request.h 
	../../libs/WebGTestClient/detail/keyboard.h 
	../../libs/WebGTestClient/detail/meta_tools.h 
	../../libs/WebGTestClient/detail/resource.h 
	../../libs/WebGTestClient/detail/shared.h 
	../../libs/WebGTestClient/detail/time.h 
	../../libs/WebGTestClient/detail/to_string.h 
	../../libs/WebGTestClient/detail/types.h 
	)

set(SOURCE_FILES
	main.cpp
	)

# CURL

include_directories("../../tests/lib/curl-7.55.0/builds/libcurl-vc13-x64-release-dll-ipv6-sspi-winssl/include")
link_directories("../../tests/lib/curl-7.55.0/builds/libcurl-vc13-x64-release-dll-ipv6-sspi-winssl/lib")

list(APPEND LIBS libcurl wsock32 ws2_32)
list(APPEND DEPS curl_project)

add_definitions(-DCURL_STATICLIB)

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
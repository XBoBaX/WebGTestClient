set(HEADER_FILES
	../libs/WebGTestClient/WebDriver.h
	../libs/WebGTestClient/by.h 
	../libs/WebGTestClient/capabilities.h 
	../libs/WebGTestClient/client.h 
	../libs/WebGTestClient/client.inl  
	../libs/WebGTestClient/conversions.h 
	../libs/WebGTestClient/element.h
	../libs/WebGTestClient/element.inl  
	../libs/WebGTestClient/errors.h 
	../libs/WebGTestClient/js_args.h 
	../libs/WebGTestClient/keys.h 
	../libs/WebGTestClient/response_status_code.h 
	../libs/WebGTestClient/session.h 
	../libs/WebGTestClient/session.inl 
	../libs/WebGTestClient/types.h 
	../libs/WebGTestClient/wait.h 
	../libs/WebGTestClient/wait_match.h 
	../libs/WebGTestClient/webdriver.h 
	../libs/WebGTestClient/window.h 
	../libs/WebGTestClient/picojson.h
	../libs/WebGTestClient/browsers/chrome.h
	../libs/WebGTestClient/detail/error_handling.h
	../libs/WebGTestClient/detail/factories.h 
	../libs/WebGTestClient/detail/factories_impl.h 
	../libs/WebGTestClient/detail/finder.h 
	../libs/WebGTestClient/detail/finder.inl 
	../libs/WebGTestClient/detail/http_client.h 
	../libs/WebGTestClient/detail/http_connection.h 
	../libs/WebGTestClient/detail/http_request.h 
	../libs/WebGTestClient/detail/keyboard.h 
	../libs/WebGTestClient/detail/meta_tools.h 
	../libs/WebGTestClient/detail/resource.h 
	../libs/WebGTestClient/detail/shared.h 
	../libs/WebGTestClient/detail/time.h 
	../libs/WebGTestClient/detail/to_string.h 
	../libs/WebGTestClient/detail/types.h 
	)

set(SOURCE_FILES
	main.cpp
	#client_test.cpp
	environment.h
	webgtestclient_test.cpp
	#capabilities_test.cpp
	#client_test.cpp
	#examples_test.cpp
	#http_connection_test.cpp
	session_test.cpp
	)

file(COPY pages DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_definitions(-DWEBDRIVERXX_ENABLE_GMOCK_MATCHERS)

# CURL

include_directories("lib/curl-7.55.0/builds/libcurl-vc13-x64-release-dll-ipv6-sspi-winssl/include")
link_directories("lib/curl-7.55.0/builds/libcurl-vc13-x64-release-dll-ipv6-sspi-winssl/lib")

list(APPEND LIBS libcurl wsock32 ws2_32)
list(APPEND DEPS curl_project)

add_definitions(-DCURL_STATICLIB)



add_library(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(${PROJECT_NAME} ${LIBS})
################################
# Testing
################################
if (test)

	add_subdirectory(lib/googletest)

	enable_testing()

	include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

	list(APPEND LIBS gtest gmock)

	##############
	# Unit Tests
	##############
	add_executable(${PROJECT_NAME}_test ${SOURCE_FILES} ${HEADER_FILES})
	target_link_libraries(${PROJECT_NAME}_test ${LIBS})
	add_test(${PROJECT_NAME}_test ${PROJECT_NAME})

	configure_file(lib/curl-7.55.0/builds/libcurl-vc13-x64-release-dll-ipv6-sspi-winssl/bin/libcurl.dll ${CMAKE_CURRENT_BINARY_DIR}/Debug/libcurl.dll COPYONLY)

endif()

#if (WIN32)
#	set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME} SUFFIX ".dll")
#endif()

#install(TARGETS ${PROJECT_NAME} DESTINATION /usr/local/lib)

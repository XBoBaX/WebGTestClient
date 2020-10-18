set(HEADER_FILES
	../libs/WebGTestClient/WebDriver.h
	../libs/WebGTestClient/picojson.h
	../libs/WebGTestClient/capabilities.h
	)

set(SOURCE_FILES
	main.cpp
	diplomWork_test.cpp
	)

file(COPY pages DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# CURL
include_directories(lib/curl-7.73.0-win64-mingw/include)
list(APPEND LIBS ${CURL_LIBRARIES})

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

endif()

#if (WIN32)
#	set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME} SUFFIX ".dll")
#endif()

#install(TARGETS ${PROJECT_NAME} DESTINATION /usr/local/lib)

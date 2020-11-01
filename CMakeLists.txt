cmake_minimum_required(VERSION 3.1)

set(PROJECT_NAME diplomWork)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)
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

include_directories(libs)
add_subdirectory(tests)

install(DIRECTORY
		${CMAKE_SOURCE_DIR}/libs/
		DESTINATION /usr/local/libs/${PROJECT_NAME}
		FILES_MATCHING PATTERN "*")
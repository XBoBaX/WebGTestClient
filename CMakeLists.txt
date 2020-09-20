cmake_minimum_required(VERSION 3.1)

project(diplomWork)

add_executable(diplomWork diplomWork.cpp)

install(DIRECTORY
		${CMAKE_SOURCE_DIR}/lib/
		DESTINATION /usr/local/lib/${PROJECT_NAME}
		FILES_MATCHING PATTERN "*")

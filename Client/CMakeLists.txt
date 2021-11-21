cmake_minimum_required (VERSION 3.13)
project(ObjectFusion)
set (CMAKE_CXX_STANDARD 11)
# Add source to this project's executable.
add_executable (ObjectFusion)
target_include_directories(ObjectFusion PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc ${CMAKE_CURRENT_SOURCE_DIR}/../inc)
target_sources(ObjectFusion PRIVATE
			${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/DataLogger.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/../inc/Definitions.h
			${CMAKE_CURRENT_SOURCE_DIR}/inc/ISensorInterface.h
			${CMAKE_CURRENT_SOURCE_DIR}/inc/IFusionInterface.h
			${CMAKE_CURRENT_SOURCE_DIR}/inc/DataLogger.h)

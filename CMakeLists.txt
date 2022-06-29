# Created by the script cgal_create_CMakeLists
# This is the CMake script for compiling a set of CGAL applications.

project( RationalRotation )

cmake_minimum_required(VERSION 2.8.11)
aux_source_directory(. SRC_LIST)

cmake_policy(SET CMP0057 NEW)

#Required in DGtal
FIND_PACKAGE(DGtal REQUIRED)
INCLUDE_DIRECTORIES(${DGTAL_INCLUDE_DIRS})
LINK_DIRECTORIES(${DGTAL_LIBRARY_DIRS})

#Required in Gmp
FIND_PACKAGE(GMP REQUIRED)
INCLUDE_DIRECTORIES(${GMP_INCLUDE_DIRS})
LINK_DIRECTORIES(${GMP_LIBRARY_DIRS})

# Boost and its components
find_package( Boost REQUIRED )
if ( NOT Boost_FOUND )
  message(STATUS "This project requires the Boost library, and will not be compiled.")
  return()
endif()

# include for local directory

# include for local package

add_definitions(-g)

# Creating entries for target: RationalRotation
# ############################

#add_executable(${PROJECT_NAME} ${SRC_LIST})
add_executable(${PROJECT_NAME} main.cpp Functions.h Functions.cpp Rotation2D.h Rotation2D.cpp)
target_link_libraries(${PROJECT_NAME} ${DGTAL_LIBRARIES} ${DGtalToolsLibDependencies} gmp gmpxx)

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

add_definitions(-g)

#add_executable(${PROJECT_NAME} ${SRC_LIST})
add_executable(${PROJECT_NAME} main.cpp Functions.h Functions.cpp Rotation2D.h Rotation2D.cpp)
target_link_libraries(${PROJECT_NAME} ${DGTAL_LIBRARIES} ${DGtalToolsLibDependencies} gmp gmpxx)

project(EstoqueLabQuimica)
cmake_minimum_required(VERSION 2.8)
find_package(Boost COMPONENTS filesystem system)
include_directories( src ${Boost_INCLUDE_DIRS})
aux_source_directory(src SRC)
aux_source_directory(src/dao DAO)
aux_source_directory(src/entity ENTITY)
aux_source_directory(src/model MODEL)
aux_source_directory(src/view VIEW)
aux_source_directory(src/control CONTROL)
aux_source_directory(src/exception  EXCEPTION)
list(APPEND FULL_SRC
    ${SRC}
	${ENTITY}
	${MODEL}
	${VIEW}
	${CONTROL}
    ${DAO}
    ${EXCEPTION} )
add_executable(${PROJECT_NAME} ${FULL_SRC})
target_link_libraries(${PROJECT_NAME} mysqlcppconn _mongoose pthread htmlcxx dl)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++11")


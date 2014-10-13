project(EstoqueLabQuimica)
cmake_minimum_required(VERSION 2.8)
find_package(Boost COMPONENTS filesystem system)
set(MYSQL_DIR "C:/Program Files (x86)/MySQL/MySQL Connector C++ 1.1.4")
include_directories( src ${Boost_INCLUDE_DIRS} ${MYSQL_DIR}/include)
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
target_link_libraries(${PROJECT_NAME} _mongoose)

if(WIN32)
	include_directories(../mongoose 
						../ #htmlcxx
						${MYSQL_DIR}/include)
	add_subdirectory(../mongoose mongoose)
	IF(CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_link_libraries(${PROJECT_NAME} ../../htmlcxx/Debug/htmlcxx)
		target_link_libraries(${PROJECT_NAME} ${MYSQL_DIR}/lib/debug/mysqlcppconn.lib)
	ELSE()
	target_link_libraries(${PROJECT_NAME} ../../htmlcxx/Release/htmlcxx)
		target_link_libraries(${PROJECT_NAME} ${MYSQL_DIR}/lib/opt/mysqlcppconn.lib)
	ENDIF(CMAKE_BUILD_TYPE STREQUAL "Debug")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++11")
	target_link_libraries(${PROJECT_NAME} pthread dl mysqlcppconn htmlcxx)
endif()


project(EstoqueLabQuimica)
cmake_minimum_required(VERSION 2.8)
find_package(Boost COMPONENTS filesystem system)
set(MYSQL_DIR "C:/Program Files (x86)/MySQL/MySQL Connector C++ 1.1.4")
set(JSON_DIR "C:/Program Files (x86)/jsoncpp")
set(MONGOOSE_DIR "C:/Program Files (x86)/mongoose")
include_directories( src ${Boost_INCLUDE_DIRS} ${MYSQL_DIR}/include ${JSON_DIR}/include ${MONGOOSE_DIR}/include)
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
if(WIN32)
	include_directories(../)
	IF(CMAKE_BUILD_TYPE STREQUAL "Debug")	
		link_directories( ${LINK_DIRECTORIES} ${MYSQL_DIR}/lib/debug ../../htmlcxx/Debug ${JSON_DIR}/lib/debug)
	ELSE()
		link_directories( ${LINK_DIRECTORIES} ${MYSQL_DIR}/lib/opt ../../htmlcxx/Release ${JSON_DIR}/lib ${MONGOOSE_DIR}/lib)
	ENDIF(CMAKE_BUILD_TYPE STREQUAL "Debug")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++11")
	target_link_libraries(${PROJECT_NAME} pthread dl)
endif()

add_executable(${PROJECT_NAME} ${FULL_SRC})
target_link_libraries(${PROJECT_NAME} _mongoose jsoncpp mysqlcppconn htmlcxx)


# install
install (FILES msvcp100d.dll msvcr100d.dll mysqlcppconn.dll DESTINATION bin)
install (DIRECTORY WebContent/ DESTINATION WebContent)
install (TARGETS ${PROJECT_NAME} DESTINATION bin)

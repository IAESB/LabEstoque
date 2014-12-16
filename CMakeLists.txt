project(LabEstoqueServer)
cmake_minimum_required(VERSION 2.8)
find_package(Boost COMPONENTS filesystem system thread program_options )
set(MYSQL_DIR "C:/Program Files (x86)/MySQL/MySQL Connector C++ 1.1.4")
set(JSON_DIR "C:/Program Files (x86)/jsoncpp")
set(MONGOOSE_DIR "C:/Program Files (x86)/mongoose")
include_directories(../../ src ${Boost_INCLUDE_DIRS} ${MYSQL_DIR}/include ${JSON_DIR}/include)
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
if(MSVC)
	include_directories(../)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHa")
	IF(CMAKE_BUILD_TYPE STREQUAL "Debug")	
		link_directories( ${LINK_DIRECTORIES} ${MYSQL_DIR}/lib/debug ../../htmlcxx/build/Debug ${JSON_DIR}/lib/debug ${MONGOOSE_DIR}/lib_debug)
	ELSE()
		link_directories( ${LINK_DIRECTORIES} ${MYSQL_DIR}/lib/opt ../../htmlcxx/build/$(Configuration) ${JSON_DIR}/lib ${MONGOOSE_DIR}/lib)
	ENDIF(CMAKE_BUILD_TYPE STREQUAL "Debug")
else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")
endif()
link_directories(c:/Boost/lib)

add_definitions(-DCPPCONN_LIB_BUILD)
add_executable(${PROJECT_NAME} ${FULL_SRC})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} _mongoose jsoncpp htmlcxx soci_mysql soci_core mysql psapi)
if(UNIX)
	target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} pthread)
else()
	target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ws2_32)
endif()


# install
install (FILES restart.bat restartHide.vbs createDump.bat DESTINATION bin)
install (FILES doc/estoqueLabQuimica.mwb DESTINATION doc)
install (DIRECTORY WebContent/ DESTINATION WebContent)
install (TARGETS ${PROJECT_NAME} DESTINATION bin)

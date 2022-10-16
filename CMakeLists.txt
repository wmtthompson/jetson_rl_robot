cmake_minimum_required (VERSION 3.10)

project (test_project2)

set(CMAKE_CXX_STANDARD 11)

set(headers 
	Agent.h
	common.h
	Simulator.h
	i2c.h
	StateActionTable.h
	Episode.h
	)
	
set(sources 
	Agent.cpp
	Episode.cpp
	Simulator.cpp
	i2c.c
	StateActionTable.cpp
	test_project2.cpp
	)
  

add_executable(test_project2 ${headers} ${sources})



#target_link_libraries(test_project2 PUBLIC i2c) 

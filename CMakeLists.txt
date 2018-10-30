cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
project(tic_tac_toe)

include_directories(components)
include_directories(gameplay)
include_directories(model)

add_executable(tic_tac_toe main.cpp 
			  components/Playfield.cpp components/Cell.cpp gameplay/GameEngine.cpp  gameplay/GameConfig.cpp 
			  model/Player.cpp model/PlayfieldState.cpp)
cmake_minimum_required(VERSION 3.7)
project(orb_stereo_mapping)

set(CMAKE_CXX_STANDARD 11)


include_directories(/usr/local/include)
link_directories(/usr/local/lib)

file(GLOB_RECURSE SOURCE_FILES ./src/*.cpp )
add_executable(orb_stereo_mapping ${SOURCE_FILES})


target_link_libraries(orb_stereo_mapping )
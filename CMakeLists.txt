cmake_minimum_required(VERSION 3.20)
project(leetgpu-challenges)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIRECTORIES include)

set(MAIN_FOLDERS easy medium hard)
set(PROBLEMS_FOLDER "")

message(STATUS "Searching problems by difficulty")

foreach(folder IN LISTS MAIN_FOLDERS)

    message(STATUS "\tSearching for ${folder} problems")

    file(GLOB SUBFOLDERS RELATIVE "${SRC_DIR}/${folder}" "${SRC_DIR}/${folder}/*")
    foreach(subfolder IN LISTS SUBFOLDERS)
        if(IS_DIRECTORY "${SRC_DIR}/${folder}/${subfolder}")
            list(APPEND PROBLEMS_FOLDER ${folder}/${subfolder})
            message(STATUS "\t\tFound problem: ${subfolder}")
        endif()
    endforeach()
endforeach()


foreach(problem IN LISTS PROBLEMS_FOLDER)
    set(SOURCES "")
    file(GLOB SOURCES RELATIVE ${SRC_DIR}/${problem} "${SRC_DIR}/${problem}/*.cpp")

    string(REPLACE "/" ";" PROBLEM_PARTS "${problem}")

    list(GET PROBLEM_PARTS 1 PROBLEM_NAME)
    message(STATUS "Adding rule for problem: ${PROBLEM_NAME}")
    
    foreach(SRC IN LISTS SOURCES)
        get_filename_component(EXEC_NAME ${SRC} NAME_WE)
        set(BINARY_NAME "${PROBLEM_NAME}-${EXEC_NAME}")
        message(STATUS "Adding build for ${BINARY_NAME}")
        add_executable(${BINARY_NAME} ${SRC_DIR}/${problem}/${SRC})
        target_include_directories(${BINARY_NAME} PRIVATE ${INCLUDE_DIRECTORIES})
    endforeach()
endforeach()
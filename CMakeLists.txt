cmake_minimum_required(VERSION 3.1.3 FATAL_ERROR)

project(XOR-File-Encoder)

#Change language version to c99
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

#Set Output Directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

#For Visual Studio compiler
if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W2)
endif()

add_executable(FileEncoder 
	src/main.c
	src/Encoder/xorencoder.h src/Encoder/xorencoder.c
	src/Custom/cstmio.h src/Custom/cstmio.c
	src/Custom/cstmstr.h src/Custom/cstmstr.c)
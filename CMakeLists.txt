cmake_minimum_required(VERSION 3.1.3 FATAL_ERROR)

project(XOR-FileEncoder)

#Change language version to c99
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

#Set Output Directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

#For Visual Studio compiler
if (MSVC)
    # warning level 2 enabled
    add_compile_options(/W2)
endif()

add_executable(FileEncoder 
	src/main.c
	src/Encoders/xorencoder.h src/Encoders/xorencoder.c
	src/Customs/cstmio.h src/Customs/cstmio.c
	src/Customs/cstmstr.h src/Customs/cstmstr.c)
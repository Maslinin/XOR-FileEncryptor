cmake_minimum_required(VERSION 3.1.3 FATAL_ERROR)

project(XOR-FileEncryptor)

#Change language version to c99
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

#Set Output Directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

#For MSVC compiler
if (MSVC)
    # warning level 2 enabled
    add_compile_options(/W2)
endif()

add_executable(FileEncryptor
	src/main.c
	src/macros.h
	src/dinput.h src/dinput.c
	src/Encryptors/xorencryptor.h src/Encryptors/xorencryptor.c
	src/Custom/cstmio.h src/Custom/cstmio.c
	src/Custom/cstmstr.h src/Custom/cstmstr.c)
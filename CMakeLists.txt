cmake_minimum_required(VERSION 3.31.6 FATAL_ERROR)

project(XOR-FileEncryptor)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin)

set(HEADERS
	src/macros.h 
	src/dinput.h 
	src/Encryptors/xorencryptor.h
	src/Custom/cstmio.h 
	src/Custom/cstmstr.h
)

set(SOURCES
	src/main.c 
	src/dinput.c 
	src/Encryptors/xorencryptor.c
	src/Custom/cstmio.c
	src/Custom/cstmstr.c
)

add_executable(FileEncryptor
	${HEADERS}
	${SOURCES}
)
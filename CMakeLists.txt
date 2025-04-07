cmake_minimum_required(VERSION 3.31.6 FATAL_ERROR)

project(XOR-FileEncryptor)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin)

set(HEADERS
	src/constants.h
	src/Encryptors/xorencryptor.h
	src/Cli/options.h
)

set(SOURCES
	src/main.c
	src/Encryptors/xorencryptor.c
	src/Cli/options.c
)

add_executable(FileEncryptor
	${HEADERS}
	${SOURCES}
)
cmake_minimum_required(VERSION 3.0.2 FATAL_ERROR)

project(XOR-File-Encoder)

add_executable(FileEncoder 
	src/main.c
	src/Encoder/xorencoder.h src/Encoder/xorencoder.c
	src/Custom/cstmio.h src/Custom/cstmio.c
	src/Custom/cstmstr.h src/Custom/cstmstr.c)
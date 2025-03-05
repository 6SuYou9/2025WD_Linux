#!/bin/bash

# 创建目录
mkdir -p include
mkdir -p objs
mkdir -p res
mkdir -p src

# 创建头文件
touch include/main.h
touch include/network.h
touch include/server.h
touch include/task.h
touch include/thread.h

# 创建源文件
touch src/main.c
touch src/network.c
touch src/server.c
touch src/task.c
touch src/thread.c

# 创建其他文件
touch makefile
touch res/file1.txt

echo "目录结构和文件已生成。"

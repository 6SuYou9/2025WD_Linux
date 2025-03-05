# 定义编译器
CC = gcc
# 定义源文件目录
SRC_DIR = src
# 定义头文件目录
INC_DIR = include
# 定义对象文件目录
OBJ_DIR = objs
# 定义可执行文件名
TARGET = myTestServer
# 定义源文件
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/network.c $(SRC_DIR)/server.c $(SRC_DIR)/task.c $(SRC_DIR)/thread.c
# 定义头文件
HDRS = $(INC_DIR)/main.h $(INC_DIR)/network.h $(INC_DIR)/server.h $(INC_DIR)/task.h $(INC_DIR)/thread.h

# 定义对象文件
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# 默认目标
all: $(TARGET)

# 链接目标文件生成可执行文件
$(TARGET): $(OBJS)
	$(CC) $^ -o $@

# 编译源文件生成对象文件
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c 
	$(CC) -c $^ -I$(INC_DIR) -o $@
# 清理生成的文件
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

.PHONY: all clean

# 指定编译器
CC = gcc

# 编译选项
CFLAGS = -Wall -g

# 目标可执行文件名称
TARGET = breaker

# 默认目标
$(TARGET): breaker.o
	$(CC) $(CFLAGS) -o $(TARGET) breaker.o

# 编译规则
main.o: breaker.c
	$(CC) $(CFLAGS) -c breaker.c -o breaker.o

# 清理目标
.PHONY: clean
clean:
	rm -f $(TARGET) breaker.o

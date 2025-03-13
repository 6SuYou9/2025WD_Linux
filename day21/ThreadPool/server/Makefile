# 生成项目
SRCS:= main.c epoll.c tcpInit.c worker.c taskQueue.c
OBJS:=$(SRCS:%.c=%.o)
server:$(OBJS)
	gcc $(OBJS) -o server -lpthread 
%.o:%.c
	gcc -c $< -o $@ -g
clean:
	$(RM) server $(OBJS)  

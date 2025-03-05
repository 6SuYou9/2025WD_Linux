# 定义一个变量，:=前是名字，:=后是内容,是自定义变量
OUT:=main
OBJS:=sub.o main.o add.o
# 预定义变量也可以改内容
CC:=gcc
# $(OUT) 是访问OUT变量内容
$(OUT):$(OBJS)
	$(CC) $(OBJS) -o $(OUT)
main.o:main.c
	$(CC) -c $< -o $@ -g
sub.o:sub.c
	$(CC) -c $< -o $@ -g
add.o:add.c
	$(CC) -c $< -o $@ -g
# 有一个规范，希望写一个规则，把所有伪目标都集中在一起
.PHONY:clean rebuild
clean:
	rm -f $(OBJS) $(OUT)
rebuild:clean main

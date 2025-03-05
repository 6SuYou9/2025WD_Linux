#include <2025Linux.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
	// 检查参数
	ARGS_CHECK(argc,3);		
	// 打开两个管道
	int fdw = open(argv[1], O_WRONLY);
	ERROR_CHECK(fdw,-1,"open fdw");
    int fdr = open(argv[2], O_RDONLY);
	ERROR_CHECK(fdr,-1,"open fdr");
    printf("qiang is connected\n");
	// 创建文件描述符集合
    fd_set fds;
    struct timeval tv;
    tv.tv_sec = 0;  // 非阻塞模式
    tv.tv_usec = 0;
    char buf[BUFFER_SIZE] = {0};
	int max_fd = (fdr > STDIN_FILENO) ? fdr : STDIN_FILENO;
	int ret_fd;
	// 开始循环
    while (1) {
		// 设置文件描述符集合
		FD_ZERO(&fds);
		FD_SET(STDIN_FILENO, &fds);
		FD_SET(fdr, &fds);
        ret_fd = select(max_fd + 1, &fds, NULL, NULL, &tv);
		ERROR_CHECK(ret_fd,-1,"select");
        if (FD_ISSET(fdr, &fds)) {  // 读取对方消息
			memset(buf, 0, sizeof(buf));
			ssize_t bytes_read = read(fdr, buf, sizeof(buf) - 1);
			ERROR_CHECK(ret_fd,-1,"read");
            if (bytes_read > 0) {
                buf[bytes_read] = '\0';
                printf("Received: %s", buf);
            }
        }
        if (FD_ISSET(STDIN_FILENO, &fds)) {  // 读取本地输入
			memset(buf, 0, sizeof(buf));
			ssize_t bytes_read = read(STDIN_FILENO, buf, sizeof(buf) - 1);
			ERROR_CHECK(ret_fd,-1,"read");
            if (bytes_read > 0) {
                buf[bytes_read] = '\0';
                write(fdw, buf, strlen(buf));  // 发送消息
            }
        }
    }

    close(fdr);
    close(fdw);
    return 0;
}

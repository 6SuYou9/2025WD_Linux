#include <2025Linux.h>
#include <sys/epoll.h>
#define IP "0.0.0.0"    // argv[1]
#define PORT "12345"      // argv[2]
#define BUFSIZE 4096
#define TIMEOUT 10      // 超时踢人时限
#define MAX 1024    // 就绪队列容量
// 设计一个数据结构数组，管理所有客户端的信息
typedef struct ConnInfo_s{
    int netfd;
    int isConnected;    // 0 未连接 1 已连接
    time_t lastactive;  // 该用户上次活跃时间
} ConnInfo_t;
int main(int argc,char *argv[])
{
    // ./5_server_charroom 0.0.0.0 12345 测试先用宏了
    ARGS_CHECK(argc,1);
    // 初始化变量
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(PORT));
    addr.sin_addr.s_addr = inet_addr(IP);
    // 创建socket文件对象
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(sockfd,-1,"socket");
    int flag = 1;
    int ret = setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&flag,sizeof(flag));
    ERROR_CHECK(ret,-1,"setsockopt");
    // 服务端需要bind
    ret = bind(sockfd,(struct sockaddr *)&addr,sizeof(addr));
    ERROR_CHECK(ret,-1,"bind");
    // 服务端需要listen
    ret = listen(sockfd,10);
    ERROR_CHECK(ret,-1,"listen");

    // 使用epoll
    int epfd = epoll_create(1); // 创建epoll文件对象
    struct epoll_event event;   // 创建event
    event.events = EPOLLIN;
    event.data.fd = sockfd;
    epoll_ctl(epfd,EPOLL_CTL_ADD,sockfd,&event);    // 将sockfd加入监听集合
    // 管理所有客户端信息的数据结构
    ConnInfo_t client[1024];
    for(int i=0;i<1024;i++){    // 初始化
        client[i].isConnected = 0;
    }
    int fdToidx[1024];  // 哈希表 已知netfd求client的下标
    for(int netfd=0;netfd<1024;netfd++){
        fdToidx[netfd] = -1;    // 每个netfd都没有在client数组中
    }
    int curidx = 0;     // 下一个客户端在client中的下标
    char buf[BUFSIZE];
    struct epoll_event events[MAX];     // 就绪队列
    while(1){
        int readynum = epoll_wait(epfd,events,MAX,1000);   // 1000ms = 1s
		time_t now = time(NULL);    // 记录当前的时间
        printf("now = %s\n",ctime(&now));
        for(int i=0;i<readynum;i++){
            if(sockfd==events[i].data.fd){  // 有新客户端接入
                // 向client数组中新加一个成员
                client[curidx].netfd = accept(sockfd,NULL,NULL);   // accept之后sockfd依然需要监听
                client[curidx].isConnected = 1;
                client[curidx].lastactive = now;     // 将新成员的上传活跃时间设为进入聊天室的时间
                printf("new client is isConnected!  id = %d, netfd = %d\n",curidx,client[curidx].netfd);
                // 把新客户端的netfd加入监听
                event.events = EPOLLIN;
                event.data.fd = client[curidx].netfd;
                epoll_ctl(epfd,EPOLL_CTL_ADD,client[curidx].netfd,&event);
                // 调整fdToidx
                fdToidx[client[curidx].netfd] = curidx;
                curidx++;   // 下标自增
            }else{  // 某个netfd就绪，客户端发消息或者断开
                // 读消息
                int netfd = events[i].data.fd;  // 在就绪队列events中，无需for循环就知道是谁就绪
                memset(buf,0,BUFSIZE);
                ssize_t sret = recv(netfd,buf,BUFSIZE,0);
                if(sret==0){    // 某个客户端断开了
                    epoll_ctl(epfd,EPOLL_CTL_DEL,netfd,NULL); // 移除对给netfd的监听
                    close(netfd);     // 断开连接
                    // 要改isconnected，要根据netfd --->> client的i ==>哈希查找
                    int idx = fdToidx[netfd];
                    client[idx].isConnected = 0;  // 修改client[i]设为未连接
                    fdToidx[netfd] = -1;    // 把数据从哈希表中移除掉
                    printf("netfd = %d, id = %d client is quit!\n",netfd,idx);
                    continue;
                }
                // 确实有消息
                printf("get message from id = %d, netfd = %d client\n",i,netfd);
                int idx = fdToidx[netfd];
				client[idx].lastactive = now;   // 更新活跃时间
                for(int j=0;j<curidx;j++){
                    if(client[j].isConnected==1 && j!=i){   // 遍历存活的其他client
                        send(client[j].netfd,buf,strlen(buf),0);
                    }
                }
            }
        }// for循环
        // 上面这个循环结束以后，所以netfd的lastactive该更新的都更新了
		for(int i=0;i<curidx;i++){	// 开始踢人
            if(client[i].isConnected==1 && now - client[i].lastactive>=TIMEOUT){   // 遍历所有存活的client，判断其上次活跃时间
                // 存活 && 距离上次活跃时间超过TIMEOUT
                epoll_ctl(epfd,EPOLL_CTL_DEL,client[i].netfd,NULL); // 移除对给netfd的监听
                close(client[i].netfd); 	// 断开连接
                client[i].isConnected = 0;  // 修改client[i]设为未连接
                fdToidx[client[i].netfd] = -1;  // 修改相关的哈希表
                printf("netfd = %d, id = %d client is timeout!\n",client[i].netfd,i);
                continue;
            }
        }
    }
    return 0;
}

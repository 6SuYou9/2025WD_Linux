#include <2025Linux.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct student{
    int num;    // 学号
    char name[10];  // 姓名
    float score;
}student;

int main(int argc,char *argv[])
{
    // 定义学生数组并初始化
    student s[3] = {
        {101, "Alice", 95.5},
        {102, "Bob", 88.0},
        {103, "Charlie", 92.5}
    };
    int fd = open("stu_test",O_WRONLY|O_CREAT|O_TRUNC,0666);
    ERROR_CHECK(fd,-1,"open");
    ssize_t ret = write(fd,s,sizeof(s));
    ERROR_CHECK(ret,-1,"write");
    close(fd);
    return 0;
}


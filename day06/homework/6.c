#include <2025Linux.h>
#include <stdio.h>
#include <unistd.h>
// 定义学生结构体
typedef struct student {
    int id;          // 学号
    char name[10];   // 姓名
    float score;     // 分数
}student;
int main(int argc,char *argv[])
{
    int fd = open("stu_test",O_RDONLY);
    ERROR_CHECK(fd,-1,"open");
    
    student s[3];
    ssize_t ret = read(fd,s,sizeof(s));
    ERROR_CHECK(ret,-1,"read");

    close(fd);
    // 打印学生信息
    printf("Student Information:\n");
    for (int i = 0; i < 3; i++) {
        printf("ID: %d, Name: %s, Score: %.2f\n", s[i].id, s[i].name, s[i].score);
    }

    return 0;
}


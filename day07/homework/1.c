#include <2025Linux.h>

typedef struct student{
    int id;
    char name[20];
    float score;
}student;

int main(int argc,char *argv[])
{
    // ./1 file
    ARGS_CHECK(argc,2);
    student s[3] = {
        {101,"Alice",99.99},
        {202,"Bob",88.88},
        {303,"Peter",88.99}
    };
    int fd = open(argv[1],O_RDWR|O_CREAT|O_TRUNC,0666);
    ERROR_CHECK(fd,-1,"open");
    ssize_t ret = write(fd,s,sizeof(s));
    ERROR_CHECK(ret,-1,"wirte");
    printf("读操作——————");    
    lseek(fd,0,SEEK_SET);
    student s2[3];
    ret = read(fd,s2,sizeof(s2));
    // 打印学生信息
    printf("Student Information:\n");
    for (int i = 0; i < 3; i++) {
        printf("ID: %d, Name: %s, Score: %.2f\n", s2[i].id, s2[i].name, s2[i].score);
    }
    
    return 0;
}


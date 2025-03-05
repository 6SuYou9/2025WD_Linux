#include <2025Linux.h>
#include <stdlib.h>
void log_message(const char *log_level, const char* filename, const char* message){
	 FILE *fp=fopen(filename,"a");
	 if(fp==NULL){
		 perror("Failed to open log file");
		 exit(EXIT_FAILURE);
	 }
	 fprintf(fp, "[%s] %s\n", log_level,  message);
	 fclose(fp);
 }
int main(int argc,char *argv[]){
    ARGS_CHECK(argc,4);
    log_message(argv[1],argv[2],argv[3]);
    log_message("INFO", "test.log", "how are you");
    return 0;
}

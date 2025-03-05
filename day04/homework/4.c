#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 64
#define MAX_LINE_LENGTH 128

typedef struct {
    char *name;
    int age;
    float salary;
} Employee;

void load_employee_info(const char* file_path, Employee* employee) {
    FILE* file = fopen(file_path, "r");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        if (strstr(line, "name=")) {
            char* name_start = strchr(line, '=') + 1;
            strncpy(employee->name, name_start, MAX_NAME_LENGTH - 1);
            employee->name[MAX_NAME_LENGTH - 1] = '\0'; // 确保字符串以 null 结尾
        }
        else if (strstr(line, "age=")) {
            char* age_start = strchr(line, '=') + 1;
            employee->age = atoi(age_start);
        }
        else if (strstr(line, "salary=")) {
            char* salary_start = strchr(line, '=') + 1;
            employee->salary = atof(salary_start);
        }
    }

    fclose(file);
}

int main() {
    Employee employee; 
    load_employee_info("employee_info.txt", &employee);
    printf("Loaded employee: %s, %d years old, Salary: %.2f\n",
           employee.name, employee.age, employee.salary);
    return 0;
}

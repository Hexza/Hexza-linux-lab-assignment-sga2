#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

struct Employee {
    int id;
    char name[30];
    float salary;
};

int main() {
    struct Employee employees[3] = {
        {101, "Alice", 50000.0},
        {102, "Bob", 55000.0},
        {103, "Charlie", 60000.0}
    };

    int fd = open("employees.dat", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open failed");
        exit(1);
    }

    for (int i = 0; i < 3; i++) {
        write(fd, &employees[i], sizeof(struct Employee));
    }
    printf("Created employees.dat with 3 records.\n");
    close(fd);

    fd = open("employees.dat", O_RDWR);
    if (fd < 0) {
        perror("reopen failed");
        exit(1);
    }

    struct Employee temp;
    int target_id = 102;
    float new_salary = 65000.0;

    for (int i = 0; i < 3; i++) {
        lseek(fd, i * sizeof(struct Employee), SEEK_SET);
        read(fd, &temp, sizeof(struct Employee));

        if (temp.id == target_id) {
            temp.salary = new_salary;
            lseek(fd, i * sizeof(struct Employee), SEEK_SET);
            write(fd, &temp, sizeof(struct Employee));
            printf("Updated employee ID %d (%s) salary to %.2f\n", temp.id, temp.name, temp.salary);
        }
    }

    printf("\nFinal records:\n");
    lseek(fd, 0, SEEK_SET);
    for (int i = 0; i < 3; i++) {
        read(fd, &temp, sizeof(struct Employee));
        printf("ID: %d | Name: %s | Salary: %.2f\n", temp.id, temp.name, temp.salary);
    }

    close(fd);
    return 0;
}

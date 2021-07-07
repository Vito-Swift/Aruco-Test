//
// Created by Vito Wu on 2021/7/7.
//

#include <iostream>
#include <string>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int fd;
    char *myfifo = "/tmp/myfifo";
    mkfifo(myfifo, 0666);

    char b[10];
    int i = 0;
    while (true) {
        fd = open(myfifo, O_WRONLY);
        b[0] = i++;
        write(fd, &b, 1);
        close(fd);
        sleep(1);
    }
}
#include <iostream>
#include <string>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int fd1;

    // FIFO file path
    char *myfifo = "/tmp/myfifo";

    // Creating the named file(FIFO)
    // mkfifo(<pathname>,<permission>)
    mkfifo(myfifo, 0666);

    char buff[100];
    while (1) {
        // First open in read only and read
        fd1 = open(myfifo, O_RDONLY);
        read(fd1, buff, 80);

        // Print the read string and close
        printf("%d\n", buff[0]);
        close(fd1);
    }
}
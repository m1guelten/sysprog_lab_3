#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 128

int main() {
    int fd;
    char buf[BUF_SIZE];

    // Відкриття файлу /proc/my_module_time
    fd = open("/proc/my_module_time", O_RDONLY);
    if (fd < 0) {
        perror("Failed to open /proc/my_module_time");
        return EXIT_FAILURE;
    }

    // Читання даних з файлу
    ssize_t bytesRead = read(fd, buf, BUF_SIZE);
    if (bytesRead < 0) {
        perror("Failed to read from /proc/my_module_time");
        close(fd);
        return EXIT_FAILURE;
    }

    // Вивід отриманих даних
    printf("Data read from /proc/my_module_time:\n%.*s\n", (int)bytesRead, buf);

    // Закриття файлу
    close(fd);

    return EXIT_SUCCESS;
}
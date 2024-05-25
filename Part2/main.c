#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>

#define SIZE 512

void lastError(const char *lastErr) {
    printf("\ndev: error %s\n", lastErr);
    printf("strerror: %s, errno = %d\n\n", strerror(errno), errno);
    exit(1);
}

struct Datum {
    int pid;
    time_t timer;
    char buf[SIZE];
};

int main(int argc, char** argv) {
    int fd_shm = shm_open("/object", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd_shm == -1)
        lastError("opening object shm_open()");
    if (ftruncate(fd_shm, sizeof(struct Datum)) == -1)
        lastError("ftruncate size Datum");
    struct Datum *datum = mmap(NULL, sizeof(struct Datum), PROT_EXEC | PROT_READ | PROT_WRITE, MAP_SHARED, fd_shm, 0);
    if (datum == MAP_FAILED)
        lastError("memory object mapping");
    char buf[SIZE] = {};
    while (1) {
        printf("\nInput string: ");
        fgets(buf, SIZE, stdin);
        if (msync(datum, sizeof(struct Datum), MS_SYNC) == -1)
            lastError("writing data msync");
        printf("\nDatum struct:\n\tpid = %d\n\ttimer = %s\tbuf = %s\n", datum->pid, ctime(&datum->timer), datum->buf);
        datum->pid = getpid();
        datum->timer = time(NULL);
        memcpy(datum->buf, buf, strlen(buf) + 1);
    }
    return 0;
}

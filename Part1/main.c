#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SIZE 128

int logFile = -1;

void lastError(const char *lastErr);
void writeLog(const char *str, const size_t *checkVal);
void signal_handler(int signo, siginfo_t *si, void *ucontext); 

int main(int argc, char** argv) {
    logFile = open("log.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (logFile == -1)
        lastError("opening log file");
    
    size_t checkVal = 0;
    char buf[SIZE] = { };
    checkVal = snprintf(buf, SIZE, "\n\nprogram started, pid = %d\n", getpid());
    writeLog(buf, &checkVal);
    
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = signal_handler;
    sa.sa_flags = SA_SIGINFO | SA_RESTART | SA_NOCLDSTOP;
    sigaction(SIGHUP, &sa, NULL);
    
    while(1) {
        checkVal = snprintf(buf, SIZE, "\nmain is working, pid = %d\n", getpid());
        writeLog(buf, &checkVal);
        sleep(5);
    }
    close(logFile);
    return 0;
}

void lastError(const char *lastErr) {
    close(logFile);
    printf("\ndev: error %s\n", lastErr);
    printf("strerror: %s, errno = %d\n\n", strerror(errno), errno);
    exit(1);
}

void writeLog(const char *str, const size_t *checkVal) {
    if ((str != NULL) || (*checkVal >= 0 && *checkVal < SIZE)) {
        if (write(logFile, str, *checkVal) != *checkVal)
            lastError("writing to log file");
    }
    else
        lastError("writing values");
}

void signal_handler(int signo, siginfo_t *si, void *ucontext) {
    size_t checkVal = 0;
    char buf[SIZE] = { };
    checkVal = snprintf(buf, SIZE, "\nsignal received, signo = %d\n", signo);
    writeLog(buf, &checkVal);
    checkVal = snprintf(buf, SIZE, "signal number, si_signo = %d\n", si->si_signo);
    writeLog(buf, &checkVal);
    checkVal = snprintf(buf, SIZE, "signal code, si_code = %d\n", si->si_code);
    writeLog(buf, &checkVal);
    checkVal = snprintf(buf, SIZE, "signal union sigval, si_value.sival_int = %d\n", si->si_value.sival_int);
    writeLog(buf, &checkVal);
    checkVal = snprintf(buf, SIZE, "signal union sigval, si_value.sival_ptr = %p\n", si->si_value.sival_ptr);
    writeLog(buf, &checkVal);
    checkVal = snprintf(buf, SIZE, "signal error, si_errno = %d\n", si->si_errno);
    writeLog(buf, &checkVal);
    checkVal = snprintf(buf, SIZE, "signal pid, si_pid = %d\n", si->si_pid);
    writeLog(buf, &checkVal);
    checkVal = snprintf(buf, SIZE, "signal uid, si_uid = %d\n", si->si_uid);
    writeLog(buf, &checkVal);
    checkVal = snprintf(buf, SIZE, "signal addr, si_addr = %p\n", si->si_addr);
    writeLog(buf, &checkVal);
    checkVal = snprintf(buf, SIZE, "signal status, si_status = %d\n", si->si_status);
    writeLog(buf, &checkVal);
    checkVal = snprintf(buf, SIZE, "signal band, si_band = %ld\n", si->si_band);
    writeLog(buf, &checkVal);
    checkVal = snprintf(buf, SIZE, "signal timer ID, si_timerid = %d\n", si->si_timerid);
    writeLog(buf, &checkVal);
    checkVal = snprintf(buf, SIZE, "signal overrun, si_overrun = %d\n", si->si_overrun);
    writeLog(buf, &checkVal);
    checkVal = snprintf(buf, SIZE, "signal utime, si_utime = %ld\n", si->si_utime);
    writeLog(buf, &checkVal);
    checkVal = snprintf(buf, SIZE, "signal stime, si_stime = %ld\n", si->si_stime);
    writeLog(buf, &checkVal);
    checkVal = snprintf(buf, SIZE, "signal int, si_int = %d\n", si->si_int);
    writeLog(buf, &checkVal);
    checkVal = snprintf(buf, SIZE, "signal fd, si_fd = %d\n", si->si_fd);
    writeLog(buf, &checkVal);
    checkVal = snprintf(buf, SIZE, "signal syscall, si_syscall = %d\n", si->si_syscall);
    writeLog(buf, &checkVal);
    checkVal = snprintf(buf, SIZE, "signal arch, si_arch = %d\n\n", si->si_arch);
    writeLog(buf, &checkVal);
    //if (raise(signo) == -1)
        //lastError("raise()");
    //sleep(5);
}

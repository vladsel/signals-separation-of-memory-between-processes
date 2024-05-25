# signals-separation-of-memory-between-processes

(05.01.2023)

Part 1. Signal processing. Make a program that: 

1. Describes a global log file descriptor. 
2. Describes the signal handler function of the prototype 
void signal_handler( int signo, siginfo_t *si, void * ucontext ); 
3. In the handler function, make an entry in the log file with a detailed disclosure of the structure 
siginfo_t, which is provided on the input. 
4. Opens the log file for recording. 
5. Marks in it the fact of its own launch and its pid. 
6. Describes the sigaction structure, in which the handler indicates the function. 
7. Registers a handler for the SIGHUP signal, saving the previous handler. 
8. Goes to an endless loop with falling asleep for a few seconds and markings in 
log files. 
9. Test the received program by sending signals to it with the kill utility, and 
observing the output in the log file. 
10. Explain the obtained results

Part 2. Distributed memory. Make a program that:

1. Describes a datum structure that contains an integer value for a process identifier, integer 
values for a fixed-length timestamp and period. 
2. Registers the distributed memory object through the shm_open call 
3. Brings it to a size that is a multiple of the size of the datum structure 
4. Displays the received object in memory through a pointer to the datum structure and 
call mmap 
5. Goes to an endless cycle in which: 
a. Asks for a term from the keyboard 
b. Reads and presents the contents of the datum structure 
c. Writes its process ID, current time and 
received term 
6. Test the resulting program by running two copies of it in different sessions.

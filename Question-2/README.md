# Question 2: Server Monitor (Fork/Zombie Process Handling)

## Command 1
gcc server_monitor.c -o server_monitor
**Explanation:** Compiled the C program with no errors, confirming the fork/wait/kill logic was syntactically correct.

![screenshot](screenshots/1-compile.png)

## Command 2
./server_monitor
**Explanation:** The parent process forked a child that simulated an unresponsive server. After 5 seconds, the parent detected the child hadn't exited, killed it with SIGKILL, and reaped it with waitpid() to prevent a zombie process.

![screenshot](screenshots/cmd2.png)

## Command 3
ps aux | grep server_monitor
**Explanation:** Verified that no zombie (Z state) process remained after termination — only the grep command itself appears in the process list, confirming proper cleanup.

![screenshot](screenshots/cmd2.png)

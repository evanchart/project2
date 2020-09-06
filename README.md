# project2
My project 2 from Operating Systems 421

Process isolation, or sandboxing, using system calls. Structure is a tree using a list of blocked processes. 
Modified task_pid_nr(current), called at runtime to check blocked process list. 
Locking implemented with pthread.

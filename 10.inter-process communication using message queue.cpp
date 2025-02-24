#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
struct message { long msg_type; 
char msg_text[100]; 
}; 
int main() { key_t key = ftok("msgqfile", 65); 
if (msgid == -1) { perror("msgget"); exit(EXIT_FAILURE); 
} 
struct message msg; 
msg.msg_type = 1; 
IPC_NOWAIT) == -1) { perror("msgsnd"); exit(EXIT_FAILURE); 
} 
 printf("Producer: Data sent to message queue: %s\n", msg.msg_text); 
} 
printf("Consumer: Data received from message queue: %s\n", 
msg.msg_text); 
} 
return 0; 
}

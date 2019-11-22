#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

// static void sig_usr(int);

// int  main() {
//     if(signal(SIGUSR1, sig_usr) == SIG_ERR)
//     {
//         printf("can't catch SIGNUSR1\n");
//     }else
//     {
//         printf("usr1 success~\n");
//     }
    

//     if(signal(SIGUSR2, sig_usr) == SIG_ERR)
//     {
//         printf("can't catch SIGUSER2\n");
//     }else
//     {
//         printf("usr2 success~\n");
//     }
    

//     for (;;)
//     {
//         pause();
//     }


    
//     return 0;
// }

// static void sig_usr(int signo)
// {
//     if(signo == SIGUSR1)
//     {
//         printf("sigusr1");
//     }else if (signo == SIGUSR2)
//     {
//         printf("siguise2");
//     }else
//     {
//         printf("received signal %d\n", signo);
//     }
    
// }

// int main(int argc, char const *argv[])
// {
//     char tlist_1[1024] = {0}, tlist_2[1024] = {0};
//     char fname[7][8] = {"a1", "b1", "c1", "d1", "e1", "f1", "g1"};
//     int i = 0, len_1, len_2 = 0;

//     len_1 = snprintf(tlist_1, 1024, "%s;", fname[0]);
//     len_2 = snprintf(tlist_2, 1024, "%s;", fname[0]);

//     for (i = 1; i < 2; i++)
//     {
//         len_1 = snprintf(tlist_1, 1024, "%s%s;", tlist_1, fname[i]);
//         len_2 = sprintf(tlist_2, "%s%s;", tlist_2, fname[i]);
//         printf("len_1 = %d\n", len_1);
//         printf("len_2 = %d\n", len_2);
//         printf("******************\n");
//     }

//     printf("tlist_1: %s\n", tlist_1);
//     printf("tlist_2: %s\n", tlist_2);
//     return 0;
// }

// str_to_copy(const char* str)
// {
//     unsigned char buffer[1024] = {0};
//     strncpy(buffer, str, sizeof(str));
//     printf(buffer);
// }

// char *cmd1 = "ls -l";
// char *cmd2 = "/bin/cat";
// char *argv1 = "/etc/passwd";
// char *argv2 = "/etc/group";

// int main(int argc, char const *argv[])
// {
//     printf("begin....\n");
//     pid_t pid = fork();
//     if (pid < 0)
//     {
//         perror("fork error");
//         exit(EXIT_FAILURE);
//     }else if (pid > 0)
//     {
//          wait(0);
//     }else
    
//     {
//       // int result = execl(cmd2, cmd2, argv1, argv2, NULL);
//        int result = execlp(cmd1, " ", (char *)0);
//        if (result == -1)
//        {
//            perror("exec error\n");
//         }

//     }
//     // system("ls");
//     printf("end....\n");
    
    
    
//     return 0;
// }
int sense_system(char* cmd);
int main(int argc, char const *argv[])
{
    printf("hello, world\n");
    sense_system("date");
    printf("end\n");

    return 0;
}



int sense_system(char* cmd)
{
    sigset_t blockMask, origMask;
    struct sigaction saIgnore, saOrigQuit, saOrigInt, saDefault;
    pid_t childPid;
    char* argVec[10] = {"sh", "-c", cmd, NULL};
    char* envVec[] = {NULL};
    int status, savedErron;

    if(cmd == NULL)
    {
        return -1;
    }
    
    sigemptyset(&blockMask);
    sigaddset(&blockMask, SIGCHLD);
    sigprocmask(SIG_BLOCK, &blockMask, &origMask);
    saIgnore.sa_handler = SIG_IGN;
    saIgnore.sa_flags = 0;
    sigemptyset(&saIgnore.sa_mask);
    sigaction(SIGINT, &saIgnore, &saOrigInt);
    sigaction(SIGQUIT, &saIgnore, &saOrigQuit);
    childPid = fork();
    switch (childPid)
    {
    case -1:
        
        status = -1;
        break;
    case 0:
        saDefault.sa_handler = SIG_DFL;
        saDefault.sa_flags = 0;
        sigemptyset(&saDefault.sa_mask);

        if (saOrigInt.sa_handler != SIG_IGN)
        {
            sigaction(SIGINT, &saDefault, NULL);
        }
        
        if (saOrigQuit.sa_handler != SIG_IGN)
        {
            sigaction(SIGQUIT, &saDefault, NULL);
        }

        sigprocmask(SIG_SETMASK, &origMask, NULL);
         // execl("/bin/sh", "sh", "-c", cmd, (char*)NULL);
         execve("/bin/sh", argVec, envVec);
         _exit(127);
    
    default:
        while (waitpid(childPid, &status, 0) == -1)
        {
            if(errno != EINTR)
            {
                status = -1;
                break;
            }
        }
        break;
    }

    savedErron = errno;
    sigprocmask(SIG_SETMASK, &origMask, NULL);
    sigaction(SIGINT, &saOrigInt, NULL);
    sigaction(SIGQUIT, &saOrigQuit, NULL);
    errno = savedErron;

    return status;
}

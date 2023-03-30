#include  <stdio.h> 
#include  <sys/types.h> 
#include  <unistd.h> 
#include  <sys/ipc.h> 
#include  <sys/shm.h> 
#include  <sys/wait.h> 
#include  <sys/time.h> 
#include  <iostream> 
using namespace std; 
void  ChildProcess(void);                 
void  ParentProcess(void);               
int  main() 
{
     int status;
     pid_t  pid; 
     pid = fork(); 
     if (pid == 0) 
    { 
        ChildProcess();
        cout<<"This is Child process PID = "<<getpid()<<", My parent's PID = "<<getppid()<<endl;
    } 
     else if(pid<0)
    {
    	cout<<"Fail"<<endl;
    }
     else 
    {
        cout<<"This is Parent process PID = "<<getpid()<<", waiting for my child"<<endl;
        ParentProcess();
        pid=wait(&status);
        cout<<"This is Parent process, catch my child, PID = "<<pid<<endl;
    } 
    return 0; 
} 
void  ChildProcess(void) 
{ 
 
} 
void  ParentProcess(void) 
{
 
}

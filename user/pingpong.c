#include "kernel/types.h"
#include "user.h"

int main(int argc,char* argv[]){

    int p_parent2child[2], p_child2parent[2];
    pipe(p_parent2child); 
    pipe(p_child2parent); 

    int pid_child, pid_parent;

    if((pid_child = fork()) < 0){
        printf("Fork Error!\n");
        exit(-1);
    }
    if(pid_child == 0){
        char ping[5];
        pid_child = getpid();  

        close(p_parent2child[1]);
        read(p_parent2child[0], ping, 5);
        close(p_parent2child[0]);
        printf("%d: received %s\n",pid_child, ping);

        close(p_child2parent[0]);
        write(p_child2parent[1], "pong", 5);
        close(p_child2parent[1]); 

        exit(0); //确保进程退出
    }else{
        char pong[5];
        pid_parent = getpid();
        
        close(p_parent2child[0]);
        write(p_parent2child[1], "ping", 5);
        close(p_parent2child[1]);

        close(p_child2parent[1]);
        read(p_child2parent[0], pong, 5);
        close(p_child2parent[0]);
        printf("%d: received %s\n",pid_parent,pong);
        
        exit(0); //确保进程退出
    }  
}
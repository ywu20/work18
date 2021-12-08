#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<string.h>
#include <sys/wait.h>
#define READ 0
#define WRITE 1

int main (){
  // unamed pipe
  int fds[2];
  pipe(fds);
  printf("pipe created. fds[0]: %d fds[1]: %d\n", fds[0], fds[1]);
  int fds2[2];
  pipe(fds2);

  int parent;
  parent = fork();

  if(parent){
    int status, w;
    close(fds[READ]);
    close(fds2[WRITE]);
    char inputs[10];

    while(strcmp("exit\n", inputs)){
      printf("Guess the word: \n");
      fgets(inputs,10,stdin);
      inputs[strlen(inputs)-1] = '\0';
      printf("You inputed: %s\n",inputs);
      write(fds[WRITE], inputs, sizeof(inputs));
      char len [10];
      read(fds2[READ],len,sizeof(len));
       printf("Response from child: %s\n", len);

   }


  }else{
    close(fds[WRITE]);
    close(fds2[READ]);
    char inputs[10];

    //printf("Reead : %d\n", read(fds[READ], inputs, sizeof(inputs)));
    while (read(fds[READ], inputs, sizeof(inputs))){

    printf("Child got: %s \n", inputs);

    int a= write(fds2[WRITE], "Blah", 4);
    printf("wrote %d bytes\n", a);
   }

  }
  return 0;
}

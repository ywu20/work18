#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<string.h>
#include <sys/wait.h>
#include<ctype.h>
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
    char inputs[50];

    while(strcmp("exit\n", inputs)){
      printf("Enter the word: \n");
      fgets(inputs,50,stdin);
      inputs[strlen(inputs)-1] = '\0';
      printf("You inputed: %s\n",inputs);
      write(fds[WRITE], inputs, 50);
      char result [50];
      read(fds2[READ],result,50);
       printf("Response from child: %s\n", result);

   }


  }else{
    close(fds[WRITE]);
    close(fds2[READ]);
    char inputs[50];

    //printf("Reead : %d\n", read(fds[READ], inputs, sizeof(inputs)));
    while (read(fds[READ], inputs, 50)){

    printf("Child got: %s \n", inputs);
    char response[50];
    int i;
    for(i=0;i<50;i++){
      response[i] = toupper(inputs[i]);
    }
    int a= write(fds2[WRITE], response, 50);
    //printf("wrote %d bytes\n", a);
   }

  }
  return 0;
}

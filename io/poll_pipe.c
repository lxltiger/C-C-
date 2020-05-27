#include "common.h"

//
/* 
创建无名管道
int pipe(int pipefd[2]);
pipefd[0]	管道数据出口
pipefd[1]	管道数据入口
 */
int main(int argc, char const *argv[]) {
  int numPipes = 10;
  int numWrites = 3;
  int ready, randPipe, j;
  struct pollfd *pollFd;
  // pfds是一个指针，指向int[2]数组
  int(*pfds)[2];

  //int *pfds[4]; pfds是一个指针数组，每一个指针都指向一个int型数据 

  pfds = Calloc(numPipes, sizeof(int[2]));
  pollFd = Calloc(numPipes, sizeof(struct pollfd));

  //创建指定数目的管道
  for (j = 0; j < numPipes; j++) {
    if (pipe(pfds[j]) == -1) errExit("pipe %d", j);
  }

  srandom((int)time(NULL));
  for (j = 0; j < numWrites; j++) {
    randPipe = random() % numPipes;
    printf("writing to fd:%3d(read fd:%3d)\n", pfds[randPipe][1],
           pfds[randPipe][0]);
    //往管道写入数据
    Write(pfds[randPipe][1], "a", 1);
  }

  for (j = 0; j < numPipes; j++) {
    pollFd[j].fd = pfds[j][0];
    pollFd[j].events = POLLIN;
  }
  //已经写入，不需要阻塞等待
  ready = poll(pollFd, numPipes, 0);

  if (ready == -1) errExit("poll");

  printf("poll() returned: %d\n", ready);

  for (j = 0; j < numPipes; j++) {
    if (pollFd[j].revents & POLLIN) printf("Readable: %3d\n", pollFd[j].fd);
  }

  exit(EXIT_SUCCESS);
}
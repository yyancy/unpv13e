#include <stdio.h>

#include "tinylog.h"
#include "unp.h"
FILE *dbgstream;
int debug_level;
int main(int argc, char **argv) {
  int sockfd;
  struct sockaddr_in servaddr;
  dbgstream = stdout;
  debug_level = 5;
  LOG_DBG("I/O error %s occured while opening file %s", strerror(errno),
      argv[0]);
  if (argc != 2) err_quit("usage: tcpcli <IPaddress>");

  sockfd = Socket(AF_INET, SOCK_STREAM, 0);

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(SERV_PORT);
  Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

  Connect(sockfd, (SA *)&servaddr, sizeof(servaddr));

  str_cli(stdin, sockfd); /* do it all */

  exit(0);
}

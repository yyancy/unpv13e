#include "unp.h"

void show_address(int sockfd) {
  struct sockaddr_in ss;
  socklen_t len = sizeof(ss);

  if (getsockname(sockfd, (struct sockaddr *)&ss, &len) < 0)
    err_sys("getsockname error");
  char ip4[INET_ADDRSTRLEN];
  printf("ip adress = %s ; port = %d\n",
         inet_ntop(AF_INET, &ss.sin_addr, ip4, sizeof(ip4)),
         ntohs(ss.sin_port));
}

int main(int argc, char **argv) {
  int sockfd, n;
  char recvline[MAXLINE + 1];
  struct sockaddr_in servaddr;

  if (argc != 2) err_quit("usage: a.out <IPaddress>");

  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) err_sys("socket error");

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(13); /* daytime server */
  if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
    err_quit("inet_pton error for %s", argv[1]);
  if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) < 0)
    err_sys("connect error");

  show_address(sockfd);
  int counter = 0;
  while ((n = read(sockfd, recvline, MAXLINE)) > 0) {
    counter++;
    recvline[n] = 0; /* null terminate */
    if (fputs(recvline, stdout) == EOF) err_sys("fputs error");
  }
  printf("counter is %d\n", counter);
  if (n < 0) err_sys("read error");

  exit(0);
}

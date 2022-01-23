#include	"unp.h"

void
str_cli(FILE *fp, int sockfd)
{
	char	sendline[MAXLINE], recvline[MAXLINE];

int counter = 0;
int n;
	// while ((n = Read(0, sendline, MAXLINE)) != 0) { // solution for 5.2
	while ((Fgets(sendline, MAXLINE, fp)) != NULL) {

		Writen(sockfd, sendline, strlen(sendline));

		if (Readline(sockfd, recvline,MAXLINE) == 0)
			err_quit("str_cli: server terminated prematurely");

		Fputs(recvline, stdout);
	}
}

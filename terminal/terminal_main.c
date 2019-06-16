/* Use standard echo server; baseline measurements for nonblocking version */
#include	"unp.h"
#include    "terminal.h"

int
main(int argc, char **argv)
{
	int					sockfd;
	struct sockaddr_in	servaddr;

    char *facilityName;
    int state = FacilityState_Close;

	if (argc != 2)
        err_quit("usage: terminal no name");

    facilityName = argv[1];

    printf(" facilityName   =    %s\n", facilityName);

	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	Inet_pton(AF_INET, SERVERIP, &servaddr.sin_addr);

	Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

    printf("Please input +, -:\n");
	str_terminal(stdin, sockfd, facilityName, &state);		/* do it all */

	exit(0);
}

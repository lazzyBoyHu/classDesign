#include	"unp.h"
#include    "terminal.h"

void
str_terminal(FILE *fp, int sockfd, char * terminalName, int * state)
{
    // stdineof 一个出错标志
    int			maxfdp1, stdineof;
    fd_set		rset;
    char		buf[MAXLINE];
    char timeBuffer[BUFLEN];
    char facilityState[BUFLEN];
    int		n;
    int flag = 1;
    time_t t = time(0);

    stdineof = 0;
    FD_ZERO(&rset);
    for ( ; ; ) {
        if (stdineof == 0)
            FD_SET(fileno(fp), &rset);
        FD_SET(sockfd, &rset);
        maxfdp1 = max(fileno(fp), sockfd) + 1;
        Select(maxfdp1, &rset, NULL, NULL, NULL);       // Select 函数的第一个参数是所有的文件描述符的值的最大值+1

        if (FD_ISSET(sockfd, &rset)) {	/* socket is readable */
            if ( (n = Read(sockfd, buf, MAXLINE)) == 0) {       // 从 socked 中读数据, 如果长度为0, 进判断
                if (stdineof == 1)
                    return;		/* normal termination */
                else
                    err_quit("str_cli: server terminated prematurely"); // 服务器过早的被终结, 表示没有关闭写连接, 服务器应该回应消息, 但是没有则服务器挂了
            }

            Write(fileno(stdout), buf, n);
            if (strstr(buf, "ok") == NULL)
            {
                Write(fileno(stdout), "repeat trans data\n", 18);
                strcat(facilityState, "T; name: ");
                strcat(facilityState, terminalName);
                strcat(facilityState, ";");
                getFacilityByType(facilityState, *state);
                strftime(timeBuffer, BUFLEN, "timestp: %Y%m%d%H%M%S;", localtime(&t));
                strcat(facilityState, timeBuffer);
                Writen(sockfd, facilityState, n);
                memset(facilityState, 0, BUFLEN);
            }
        }

        if (FD_ISSET(fileno(fp), &rset)) {  /* input is readable */
            if ( (n = Read(fileno(fp), buf, MAXLINE)) == 0) {
                stdineof = 1;
                Shutdown(sockfd, SHUT_WR);
                /* send FIN
                 * 关闭 tcp 的写这一半, 在网络连接中, 对于客户端来说, 一般都是客户端发送消息,
                 * 服务器接收消息, 并返回客户端所需要的数据, 在这里如果读到的数据为空,
                 * 则可以表示客户端不需要项服务器发送消息, 就可以关闭写一半的连接, 并且添加一个标志来标示已经关闭了写连接,
                 * 然后可以在接收到数据后就可以关闭连接 */
                FD_CLR(fileno(fp), &rset);
                continue;
            }

            if (buf[0] == '+')
            {
                if (*state >= FacilityState_Open)
                    flag = 0;
                else
                {
                    strcat(facilityState, "T; name: ");
                    strcat(facilityState, terminalName);
                    strcat(facilityState, ";");
                    getFacilityByType(facilityState, *state);
                    (*state)++;
                    strftime(timeBuffer, BUFLEN, "timestp: %Y%m%d%H%M%S;", localtime(&t));
                    strcat(facilityState, timeBuffer);
                }
            }
            else if (buf[0] == '-')
            {
                if (*state <= 0)
                    flag = 0;
                else
                {
                    strcat(facilityState, "T; name: ");
                    strcat(facilityState, terminalName);
                    strcat(facilityState, ";");
                    getFacilityByType(facilityState, *state);
                    (*state)--;
                    strftime(timeBuffer, BUFLEN, "timestp: %Y%m%d%H%M%S;", localtime(&t));
                    strcat(facilityState, timeBuffer);
                }
            }
            else
                flag = 0;

            if (flag)
            {
                strcat(facilityState, "\n");
                n = strlen(facilityState);
                Writen(sockfd, facilityState, n);
                memset(facilityState, 0, BUFLEN);
            }
            Write(fileno(stdout), "Please input +, -:\n", 19);
        }
    }
}

void getFacilityByType(char * buffer, int type)
{
    if (type == FacilityState_Close)
        strcat(buffer, " state: close; ");
    else if (type == FacilityState_One)
        strcat(buffer, " state: one; ");
    else if (type == FacilityState_Two)
        strcat(buffer, " state: two; ");
    else if (type == FacilityState_Three)
        strcat(buffer, " state: three; ");
    else if (type == FacilityState_Four)
        strcat(buffer, " state: four; ");
    else if (type == FacilityState_Five)
        strcat(buffer, " state: five; ");
    else if (type == FacilityState_Six)
        strcat(buffer, " state: six; ");
    else if (type == FacilityState_Seven)
        strcat(buffer, " state: seven; ");
    else if (type == FacilityState_Eight)
        strcat(buffer, " state: eight; ");
    else if (type == FacilityState_Nine)
        strcat(buffer, " state: nine; ");
    else if (type == FacilityState_Ten)
        strcat(buffer, " state: ten; ");
    else
        strcat(buffer, " state: max; ");
}

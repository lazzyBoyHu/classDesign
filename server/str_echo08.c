#include <stdio.h>

#include	"unp.h"
#include    "str_echo08.h"

void do_server(int sockfd)
{
    ssize_t		n;
    char		line[MAXLINE];
    char        name[20];
    int         begin = 0;
    int         end = 0;
    int         result;
    FILE*       file;
    int         resultOp;

    for ( ; ; ) {
        if ( (n = Read(sockfd, line, MAXLINE)) == 0)
            return;		/* connection closed by other end*/

        if (line[0] == 'T')
        {
            if ((result = getName(line, &n, &begin, &end)) == 0)
                continue;

            strncpy(name, line+begin, end-begin);
            begin = 0;
            end = 0;

            strcat(name, ".txt");
            if (file = fopen(name, "w+") == NULL)
                continue;
            fprintf(file, line);
            fclose(file);
            memset(name, 0, 20);

            Writen(sockfd, "ok", 2);
        }
        else if (line[0] == 'S')
        {
            if ((result = getName(line, &n, &begin, &end)) == 0)
                continue;

            strncpy(name, line+begin, end-begin);
            strcat(name, ".txt");
            begin = 0;
            end = 0;

            if ((resultOp = getOperateType(line, &n, &begin, &end)) == 0)
                continue;

            begin = 0;
            end = 0;
            if (line[begin] == 'g')
            {
                if ((file = fopen(name, "w+")) == NULL)
                    continue;

                while (!feof(file))                                   //循环读取每一行，直到文件尾
                {
                    fgets(line,MAXLINE,file);                     //将fp所指向的文件一行内容读到strLine缓冲区
                    printf("%s", line);                          //输出所读到的内容
                }
                fclose(file);
                Writen(sockfd, line, strlen(line));
                memset(name, 0, MAXLINE);
            }
        }
    }
}

int getName(char * state, int *length, int *begin, int *end)
{
    char name[20];
    char ch;
    int times = 0;

    for (int index = 0; index < *length; index++)
    {
        if (state[index] != ';')
            continue;

        times++;
        if (times == 1)
            *begin = index;
        if (times == 2)
        {
            *end = index;
            break;
        }
    }

    if ((*begin) <= 0 || (*end) <= 0)
        return 0;
    if (*end <= *begin)
        return 0;

    while (*begin < *end)
        if (state[(*begin)++] == ':')
            break;

    if (++(*begin) >= *end)
        return 0;
    return 1;
}

int getOperateType(char * line, int *length, int *begin, int *end)
{
    char *ch;
    int offset = 0;
    int index;

    if (line[0] != 'S')
        return 0;
    if ((ch = strstr(line, "opType")) == NULL)
        return 0;

    offset = ch - line;
    if (offset <= 0)
        return 0;

    *begin = offset+9;
    for (index = *begin; index < length; index++)
        if (line[index] == ';')
        {
            *end = index - 1;
            break;
        }

    if (*end == 0)
        return 0;
    return 1;
}

int stringSplite(char * buff, int len, char flag)
{
}



/*
   int main(int argc, char **argv)
   {
       char buffer[400] = "T; name: lamb; state: one; time: 0000";
       int begin = 0;
       int end = 0;
       int leng = 38;
       if (getName(buffer, &leng, &begin, &end))
       {
           printf("begin = %d, end = %d\n", begin, end);
       }

       return 0;
   }
   */

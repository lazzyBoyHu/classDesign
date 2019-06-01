#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include <sys/types.h>
#include <sys/socket.h>


#define SERVERIP "127.0.0.1"
#define UPDATETIME 30
#define BUFLEN 256


enum FacilityState
{
    FacilityState_Close,
    FacilityState_One,
    FacilityState_Two,
    FacilityState_Three,
    FacilityState_Four,
    FacilityState_Five,
    FacilityState_Six,
    FacilityState_Seven,
    FacilityState_Eight,
    FacilityState_Nine,
    FacilityState_Ten,
    FacilityState_Open,
};

// 根据状态拼接信息
void getFacilityByType(char * buffer, int type)
{
    if (type == FacilityState_Close)
        strcat(buffer, " state: facility close. ");
    else if (type == FacilityState_One)
        strcat(buffer, " state: one. ");
    else if (type == FacilityState_Two)
        strcat(buffer, " state: two. ");
    else if (type == FacilityState_Three)
        strcat(buffer, " state: three. ");
    else if (type == FacilityState_Four)
        strcat(buffer, " state: four. ");
    else if (type == FacilityState_Five)
        strcat(buffer, " state: five. ");
    else if (type == FacilityState_Six)
        strcat(buffer, " state: six. ");
    else if (type == FacilityState_Seven)
        strcat(buffer, " state: seven. ");
    else if (type == FacilityState_Eight)
        strcat(buffer, " state: eight. ");
    else if (type == FacilityState_Nine)
        strcat(buffer, " state: nine. ");
    else if (type == FacilityState_Ten)
        strcat(buffer, " state: ten. ");
    else
        strcat(buffer, " state: facility while close. ");
}

// 参数是设备名
int main(int argc, char **argv)
{
    int state = FacilityState_Close;
    char timeBuffer[BUFLEN];
    char facilityState[BUFLEN];
    char *facilityName;
    time_t t = time(0);

    int sockfd;
    struct sockaddr_in servaddr;

    if (argc != 2)
        err_quit("usage: terminal no name");

    facilityName = argv[1];
    strcat(facilityState, "facilityName: ");
    strcat(facilityState, argv[1]);

    // 建立连接
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port(8888);

    if (inet_pton(AF_INET, SERVERIP, &servaddr.sin_addr) <= 0)
        err_quit("inet_pton error for %s", SERVERIP);

    if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
        err_sys("connect error");

    // 每隔30秒跟新信息
    while (1)
    {
        if (state == FacilityState_Open)
            break;

        // 拼接 state 数据
        getFacilityByType(facilityState, state);
        state++;
        strftime(timeBuffer, BUFLEN, "%Y%m%d%H%M%S", localtime(&t));
        strcat(facilityState, timeBuffer);

        // 使用 socket 发送数据

        sleep(UPDATETIME);
    }

    return 0;
}


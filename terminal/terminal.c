#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>



#define SERVERIP 127.0.0.1
#define UPDATETIME 30
#define BUFFER 256


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

// 参数是设备名
int main(int argc, char **argv)
{
    int state = FacilityState_Close;
    char timeBuffer[BUFFER];
    string * facilityState;
    string facilityName;

    int sockfd;
    struct sockaddr_in  servaddr;

    if (argc != 2)
        err_quit("usage: terminal no name");

    facilityName = argv[1];

    // 每隔30秒跟新信息
    while (1)
    {
        if (state == FacilityState_Open)
            break;

        state;
    }

    return 0;
}

string * getFacilityByType(string * buffer, int type)
{
    if (type == FacilityState_Close)
        buffer->
    return buffer;
}

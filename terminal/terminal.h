#define SERVERIP    "127.0.0.1"
#define UPDATETIME  30
#define BUFLEN      256
#define PORT        9999

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
void getFacilityByType(char * buffer, int type);

void str_terminal(FILE *fp, int sockfd, char * terminalName, int * state);

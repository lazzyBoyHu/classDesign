enum DataStructType
{
    DataStructType_Terminal,
    DataStructType_Moblie,
};

struct dataStruct
{
    int type;
    char name;
    char state;
    char tstp;
};

void do_server(int sockfd);

int getName(char * state, int *length, int *begin, int *end);

int stringSplite(char * buff, int len, char flag);

int getOperateType(char * line, int *length, int *begin, int *end);

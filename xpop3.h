#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <dirent.h>

using namespace std;

#define PORT 110
#define MAX_CLIENTS 32
#define BUF_SIZE 1024

int mail_stat = 0;
const char data_dir[] = "/home/user/data/";
const char userinfo[] = "userinfo";
const char userstat[] = "userstat";
char rcpt_user[50] = "";
char rcpt_pass[50] = "";

const char reply_code[][50]={
		{" \r\n"},  //0
		{"+OK Welcome\r\n"},   //1
		{"+OK\r\n"},  //2
		{"-ERR bad command\r\n"},   //3
		{"+OK Ready\r\n"},  //4
		{"+OK Bye\r\n"},  //5
		{"+OK OK\r\n"},  //6
		{"+OK User not local;\r\n"},  //7
		{"+OK Ready\r\n"},  //8
		{"+OK Bye\r\n"},  //9
		{"+OK OK\r\n"},  //10
		{"+OK User not local;\r\n"},  //11
};



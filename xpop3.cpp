/////////////////////////////////////////////////////////////////////////////
//
// pop3.cpp
//
// POP3 start-up code
//
/////////////////////////////////////////////////////////////////////////////

#include "xpop3.h"

int quit(int arg);
void *mail_proc(void* param);
void respond(int client_sockfd, char* request);
void send_data(int sockfd, const char* data);
int check_user(char* username);
int check_name_pass(char* name, char* pass);

int main() {
	//signal(SIGINT, (void*) quit); //go to MiniWebQuit when Ctrl+C key pressed.
	//signal(SIGTERM, (void*) quit); //terminal signal
	signal(SIGPIPE, SIG_IGN); //ignore pipe signal.For more see http://www.wlug.org.nz/SIGPIPE

	int server_sockfd, client_sockfd;
	socklen_t sin_size;
	struct sockaddr_in server_addr, client_addr;

	memset(&server_addr, 0, sizeof(server_addr));
	//create socket
	if ((server_sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("S:socket create error！\n");
		exit(1);
	}

	//set the socket's attributes
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	bzero(&(server_addr.sin_zero), 8);

	//create a link
	if (bind(server_sockfd, (struct sockaddr *) &server_addr,
			sizeof(struct sockaddr)) == -1) {
		perror("S:bind error！\n");
		exit(1);
	}
	// set to non-blocking to avoid lockout issue
	//fcntl(server_sockfd, F_SETFL, fcntl(server_sockfd, F_GETFL, 0)|O_NONBLOCK);

	//listening requests from clients
	if (listen(server_sockfd, MAX_CLIENTS - 1) == -1) {
		perror("S:listen error！\n");
		exit(1);
	}

	//accept requests from clients,loop and wait.
	while (1) {
		cout << "-XPOP3 mail server by XBC started..." << endl;
		sin_size = sizeof(client_addr);
		if ((client_sockfd = accept(server_sockfd,
				(struct sockaddr *) &client_addr, &sin_size)) == -1) {
			perror("S:accept error!\n");
			sleep(10);
			continue;
		}
		cout << "S:received a connection from " << inet_ntoa(
				client_addr.sin_addr) << " at " << time(NULL) << endl;

		pthread_t id;
		pthread_create(&id, NULL, mail_proc, &client_sockfd);
		pthread_join(id, NULL);

		close(client_sockfd);
	}
	return 0;
}

int quit(int arg) {
	if (arg)
		printf("\nS:Caught signal (%d). Mail server shutting down...\n\n", arg);
	return 1;
}

void *mail_proc(void* param) {
	int client_sockfd, len;
	char buf[BUF_SIZE];

	memset(buf, 0, sizeof(buf));
	client_sockfd = *(int*) param;

	send_data(client_sockfd, reply_code[1]); //send +OK
	mail_stat = 1;

	while (1) {
		memset(buf, 0, sizeof(buf));
		len = recv(client_sockfd, buf, sizeof(buf), 0);
		if (len > 0) {
			cout << "Request stream: " << buf;
			respond(client_sockfd, buf);
		} else {
			cout
					<< "S: no data received from client. The server exit permanently.\n";
			break;
		}
		cout << "S:[" << client_sockfd << "] socket closed by client." << endl;
		cout
				<< "============================================================\n\n";
	}
	return NULL;
}

void respond(int client_sockfd, char* request) {
	char output[1024];
	memset(output, 0, sizeof(output));

	//pop3
	if (strncmp(request, "USER", 4) == 0) {
		char *pa,*pb;
		pa = strchr(request, ' ');
		pb = strchr(request,'\r');
		strncpy(rcpt_user, pa + 1, pb-pa - 1);
		cout << "DEBUG:" << rcpt_user << endl;
		if (check_user(rcpt_user)) {
			send_data(client_sockfd, reply_code[2]);
		} else {
			send_data(client_sockfd, reply_code[3]);
		}
	} else if (strncmp(request, "PASS", 4) == 0) {
		char *p;
		p = strchr(request, ' ');
		strcpy(rcpt_pass, p + 1);
		if (check_name_pass(rcpt_user, rcpt_pass)) {
			send_data(client_sockfd, reply_code[2]);
		}
	} else if (strncmp(request, "APOP", 4) == 0) {
		send_data(client_sockfd, reply_code[2]);
	} else if (strncmp(request, "AUTH", 4) == 0) {
		send_data(client_sockfd, reply_code[2]);
	} else if (strncmp(request, "CAPA", 4) == 0) {
		send_data(client_sockfd, reply_code[2]);
	} else if (strncmp(request, "DELE", 4) == 0) {
		send_data(client_sockfd, reply_code[2]);
	} else if (strncmp(request, "LIST", 4) == 0) {
		send_data(client_sockfd, reply_code[2]);
	} else if (strncmp(request, "NOOP", 4) == 0) {
		send_data(client_sockfd, reply_code[2]);
	} else if (strncmp(request, "QUIT", 4) == 0) {
		send_data(client_sockfd, reply_code[2]);
		close(client_sockfd);
	} else if (strncmp(request, "RETR", 4) == 0) {
		send_data(client_sockfd, reply_code[2]);
	} else if (strncmp(request, "RSET", 4) == 0) {
		send_data(client_sockfd, reply_code[2]);
	} else if (strncmp(request, "STAT", 4) == 0) {
		send_data(client_sockfd, reply_code[2]);
	} else if (strncmp(request, "STLS", 4) == 0) {
		send_data(client_sockfd, reply_code[2]);
	} else if (strncmp(request, "TOP", 4) == 0) {
		send_data(client_sockfd, reply_code[2]);
	} else if (strncmp(request, "UIDL", 4) == 0) {
		send_data(client_sockfd, reply_code[2]);
	} else if (strncmp(request, "XTND", 4) == 0) {
		send_data(client_sockfd, reply_code[2]);
	} else {
		send_data(client_sockfd, reply_code[3]);
	}
}

void send_data(int sockfd, const char* data) {
	if (data != NULL) {
		send(sockfd, data, strlen(data), 0);
		cout << "Reply stream: " << data;
	}
}

int check_user(char* username) {
	FILE* fp;
	char file[80] = "";
	char data[60];

	strcpy(file, data_dir);
	strcat(file, userinfo);

	fp = fopen(file, "r");
	while (fread(data, 1, sizeof(data), fp) > 0) {
		if (strncmp(username, data, strlen(username)) == 0)
			return 1;
	}
	return 0;
}

int check_name_pass(char* name, char* pass) {
	FILE* fp;
	char file[80], data[60];

	strcpy(file, data_dir);
	strcat(file, userinfo);
	fp = fopen(file, "r");
	while (fgets(data, sizeof(data), fp) > 0) {
		if (strncmp(data, name, strlen(name)) == 0) {
			char *p;
			p = strchr(data, ' ');
			if (strncmp(p + 1, pass, strlen(pass)) == 0) {
				fclose(fp);
				strcpy(file, data_dir);
				strcat(file, userstat);
				fp = fopen(file, "w+");
				strcat(name, " on");
				fwrite(name, 1, strlen(name), fp);
				fclose(fp);
				return 1;
			} else {
				return 0;
			}
		}
	}
	return 0;
}

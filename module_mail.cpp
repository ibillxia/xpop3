/*
 * Copyright (C) 2011-2014
 * Bill Xia
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 */

/*
 * This is a header file, mainly about mailing events processing.
 * 
 */

#include "module_mail.h"
#include "module_user.h"

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
			cout << "S: no data received from client. The server exit permanently.\n";
			break;
		}
	}
	cout << "S:[" << client_sockfd << "] socket closed by client." << endl;
	cout << "============================================================\n\n";
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
		cout << "DEBUG:" << rcpt_user << " " << rcpt_pass << endl;
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

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
 * This is the use management module, includes user check and authentication.
 * 
 */

#include "module_user.h"
#include "module_mail.h"

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
				break;
			}
		}
	}
	fclose(fp);
	return 0;
}

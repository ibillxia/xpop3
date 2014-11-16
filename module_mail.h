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

#ifndef __XPOP3_MODULE_MAIL_H
#define __XPOP3_MODULE_MAIL_H

#include "common.h"

void *mail_proc(void* param);
void respond(int client_sockfd, char* request);
void send_data(int sockfd, const char* data);

#endif /* #ifndef __XPOP3_MODULE_MAIL_H */

// Local Variables:
// mode: C++
// End:
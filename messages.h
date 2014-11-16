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
  * This is a header file, include the main messages respond to the client.
  * 
  */

#ifndef __XPOP3_MESSAGES_H
#define __XPOP3_MESSAGES_H


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

#endif  /* #ifndef __XPOP3_MESSAGES_H */

// Local Variables:
// mode: C++
// End:

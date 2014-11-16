# xpop3 

A simple POP3 mail server, a tiny but complete realization of pop3 protocol.


## Features

- OS: only for Linux/Unix plantform  
- Multithread: create a thread for each client's request  
- Authentication: store username and passwd to a file

## Usage  
1) Get the source    

```
git clone https://github.com/ibillxia/xpop3.git
cd xpop3
```

2) Edit Config
Set the user data storage directory:

```
vim conf.h
```

Set the variable `data_dir` to `/home/YourName/data` and make a new directory `data` in your home folder. 

3) Recieve e-mail from a mail server
Run the executable file in one terminal:  

```
sudo ./pop3
```

This started the mail server. And now you can recieve e-mail from the server in **another terminal** like this: 

```
telnet localhost 110
S: +OK Welcome
C: USER alice@localhost.com
S: +OK
C: PASS 123456
S: +OK
C: STAT
S: +OK
C: LIST
S: +OK
C: QUIT
S: +OK
```

Well done!

## About POP3 protocal  

This program is a simple mail receiver via pop3 protocol. It runs only on Linux/Unix plantforms.
For more about pop3 and it's RFC documents, please refer to wiki and RFC doc: 
[Post_Office_Protocol](http://en.wikipedia.org/wiki/Post_Office_Protocol)  
[Post Office Protocol - Version 3(STD 53)](http://tools.ietf.org/html/rfc1939)  


## Lisense

The MIT License (MIT)
Copyright (C) 2011-2014 Bill Xia (ibillxia@gmail.com) 
All rights reserved.


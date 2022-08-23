## 📌 Useful Links 
  
 * [My personal notes on Shell & Shell Scripting](https://www.notion.so/Shell-Shell-Scripting-6e0f0290a0304dad93a1d25ba15d92fe) 
 * [harm-smits' 42 Docs - minishell](https://harm-smits.github.io/42docs/projects/minishell) 
 * [Bash Guide for Beginners](https://tldp.org/LDP/Bash-Beginners-Guide/html/index.html) 
 * [The Open Group Base Specifications - Shell Command Language](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html) 
 * [Introduction to Systems Programming: a Hands-on Approach - Chapter 5. Writing Your Own Shell ](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf) 
  
  
 ### Definition 
  
 TLDR: The shell is a command language interpreter. - [_Source_](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html) 
  
 > The UNIX shell program interprets user commands, which are either directly entered by the user, or which can be read from a file called the shell script or shell program. Shell scripts are interpreted, not compiled. The shell reads commands from the script line per line and searches for those commands on the system, while a compiler converts a program into machine readable form, an executable file - whic get the value of a capability, depending on the type of value the capability has. 
  

shell 
 int        tgetnum (char *name); 
 

  
 Used to get a capability value that is numeric. 
  
 * @param char *name - the two-letter code name of the capability. 
 * @returns int - if the capability name is present in the terminal description, the numeric value (which is nonnegative); else -1. 
  

shell 
 int        tgetflag (char *name); 
 

  
 Used to get a boolean value. 
  
 * @param char *name - the two-letter code name of the capability. 
 * @returns int - if the capability name is present in the terminal description, 1; else 0. 
  

shell 
 char        *tgetstr (char *name, char **area); 
 

  
 Used to get a string value. 
  
 * @param char *name - the two-letter code name of the capability. 
 * @param char area** - pointer to where the return will be copied to. If given a null pointer, tgetstr will use malloc to allocate storage big enough for the value; you should free it when you are finished with it. 
 * @returns char * - a pointer to a string which is the capability value, or a null pointer if the capability is not present in the terminal description. 
  

shell 
 int        tputs(const char *str, int affcnt, int (*putc)(int)); 
 

  
 Applies padding information to the string str and outputs it (STDOUT). 
  
 * @param const char *str - a terminfo string variable or the return value from tparm, tiparm, tgetstr, or tgoto. 
 * @param int affcnt - the number of lines affected, or 1 if not applicable. 
 * @param int (*putc)(int) - a putchar-like routine to which the characters are passed, one at a time. 
 * @returns char * - ERR upon failure (if the string parameter is null) and OK upon successful completion. 
  
 The termios Structure 
  
 Routines that need to control certain terminal I/O (Input/Output) characteristics do so by using the termios structure (see code below) as defined in the header <termios.h>. 
  

C 
 typedef unsigned char        cc_t; 
 typedef unsigned int        speed_t; 
 typedef unsigned int        tcflag_t; 
  
 #define NCCS 32 
 struct termios 
   { 
     tcflag_t c_iflag;                /* input mode flags */ 
     tcflag_t c_oflag;                /* output mode flags */ 
     tcflag_t c_cflag;                /* control mode flags */ 
     tcflag_t c_lflag;                /* local mode flags */ 
     cc_t c_line;                /* line discipline */ 
     cc_t c_cc[NCCS];                /* control characters */ 
     speed_t c_ispeed;                /* input speed */ 
     speed_t c_ospeed;                /* output speed */ 
 #define _HAVE_STRUCT_TERMIOS_C_ISPEED 1 
 #define _HAVE_STRUCT_TERMIOS_C_OSPEED 1 
   }; 
 

  
 Two general kinds of input processing are available, determined by whether the terminal device file is in [canonical](https://pubs.opengroup.org/onlinepubs/7908799/xbd/termios.html#tag_008_001_006) mode or [non-canonical](https://pubs.opengroup.org/onlinepubs/7908799/xbd/termios.html#tag_008_001_007) mode. When and how data is provided to a process reading from a terminal device file is dependent on whether the terminal file is in canonical or non-canonical mode. Additionally, input characters are processed according to the c_iflag and c_lflag fields. The special control characters values are defined by the array c_cc. 
  
 In non-canonical mode input processing, input bytes are not assembled into lines, and erase and kill processing does not occur. The values of the MIN and TIME members of the c_cc array are used to determine how to process the bytes received. MIN represents the minimum number of bytes that should be received when the read() function returns successfully. TIME is a timer of 0.1 second granularity that is used to time out bursty and short-term data transmissions.
shell 
 int        tcgetattr(int fd, struct termios *termios_p); 
 

  
 Gets the parameters associated with the terminal referred by fd and stores them in the termios structure referenced by termios_p. This function may be invoked from a background process; however, the terminal attributes may be subsequently changed by a foreground process. 
  
 * @param int fd - an open file descriptor associated with a terminal. 
 * @param struct termios *termios_p - a pointer to a termios structure. 
 * @returns int - upon successful completion, 0; otherwise, -1 and errno is set to indicate the error. 
  

shell 
 int        tcsetattr(int fd, int optional_actions, const struct termios *termios_p); 
 

  
 Sets the parameters associated with the terminal referred to by the open file descriptor fd (an open file descriptor associated with a terminal) from the termios structure referenced by termios_p as follows: 
  
 * If optional_actions is TCSANOW, the change will occur immediately. 
 * If optional_actions is TCSADRAIN, the change will occur after all output written to fd is transmitted. This function should be used when changing parameters that affect output. 
 * If optional_actions is TCSAFLUSH, the change will occur after all output written to fd is transmitted, and all input so far received but not read will be discarded before the change is made. 
  
 . 
  
 * @param int fd - an open file descriptor associated with a terminal. 
 * @param struct termios *termios_p - a pointer to a termios structure. 
 * @returns int - will return successfully if it was able to perform any of the requested actions, even if some could not be performed. It will set all the attributes that implementation supports as requested and leave all the attributes not supported by the implementation unchanged. If no part of the request can be honoured, it will return -1 and set errno. 
  
 \- [_Source 1_](https://www.gnu.org/software/termutils/manual/termcap-1.3/), [_Source 2_](https://pubs.opengroup.org/onlinepubs/7908799/xbd/termios.html), [_Source 3_](https://man7.org/linux/man-pages/man3/termios.3.html) 
  
 ### Functions allowed in this project 
  
 | Function                | Manual Page                | From lib                        | Description 
 | :--                        | :--                                | :--                                | :-- 
 | fork                | fork                | <unistd.h>                | create a child process 
 | wait                | wait                | <sys/wait.h>        | wait for process to change state 
 | waitpid        | waitpid                | <sys/wait.h>        | wait for process to change state 
 | wait3                | wait3                | <sys/wait.h>        | (obsolete) wait for process to change state, BSD style 
 | wait4                | wait4                | <sys/wait.h>        | (obsolete) wait for process to change state, BSD style
 | getcwd        | getcwd                | <unistd.h>                | get current working directory 
 | chdir                | chdir                | <unistd.h>                | change working directory 
 | stat                | stat                | <sys/stat.h>        | get file status by pathname 
 | lstat                | lstat                | <sys/stat.h>        | get file status by pathname (for symlinks) 
 | fstat                | fstat                | <sys/stat.h>        | get file status by fd 
 | execve        | execve                | <unistd.h>                | execute program 
 | dup                | dup                        | <unistd.h>                | duplicate a file descriptor 
 | dup2                | dup2                | <unistd.h>                | duplicate a file descriptor 
 | pipe                | pipe                | <unistd.h>                | create pipe 
 | opendir        | opendir                | <dirent.h>                | open a directory 
 | readdir        | readdir                | <dirent.h>                | read a directory 
 | closedir        | closedir        | <dirent.h>                | close a directory 
 | strerror        | strerror        | <string.h>                | return string describing error number 
 | errno                | errno                | <errno.h>                | number of last error 
 | termcap        | termcap, termios                | <term.h>                | direct curses interface to the terminfo capability database 
  
 --- 

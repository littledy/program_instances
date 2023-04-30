## GDB 常用命令

以`bugging.c`文件为例：

```c
/* bugging.c */

#include <stdio.h>

int foo(int n)
{
    
    int sum;
    int i;

    for (i=0; i<=n; i++)
    {
        sum = sum+i;
    }

    return sum;
}

int main(int argc, char** argv)
{
    int result = 0;
    int N = 100;

    result = foo(N);

    printf("1+2+3+...+%d= %d\n", N, result);

    return 0;

}
```

安装`gdb`

```shell
sudo apt install update
sudo apt install gdb
```



如果要调试程序，编译时加上`-g`参数。`-m32`编译为32位程序，如果是64位操作系统，默认编译为64位程序。

```shell
gcc bugging.c -o bugging -g -m32
```

如果报错安装`libc6-dev-i386`。

```shell
sudo apt install libc6-dev-i386
```

**Note**: `mac`下暂无`arm`架构的`gdb`可以安装（2022-11-19）。



输入`gdb bugging`进入调试界面：	

```shell
dy:gdbtest/ $ gdb bugging                                     [14:11:58]
GNU gdb (Ubuntu 7.11.1-0ubuntu1~16.5) 7.11.1
Copyright (C) 2016 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from bugging...done.
```



在`gdb`命令行界面，输入`run`执行待调试程序：

```shell
(gdb) run
Starting program: /home/dy/gdbtest/bugging 
1+2+3+...+100= -136153930
[Inferior 1 (process 2672) exited normally]
```



在`gdb`命令行界面，输入`quit`退出`gdb`：

```shell
(gdb) quit
```



`list`用来显示源文件中的代码

```shell
(gdb) list
7	    
8	    int sum;
9	    int i;
10	
11	    for (i=0; i<=n; i++)
12	    {
13	        sum = sum+i;
14	    }
15	
16	    return sum;
```



`list 文件名:行号`，显示某一个文件某一行附近的代码，用于多个源文件的情况。

```shell
1	/* bugging.c */
2	
3	#include <stdio.h>
4	
5	int foo(int n)
6	{
7	    
8	    int sum;
9	    int i;
10	
```



`list 函数名`，用于显示某个函数附近的代码。

```shell
(gdb) list main
15	
16	    return sum;
17	}
18	
19	int main(int argc, char** argv)
20	{
21	    int result = 0;
22	    int N = 100;
23	
24	    result = foo(N);
```



`list 文件名:函数名`，显示某一个文件某一个函数附近的代码，用于多个源文件的情况。继续回车会打印之后的代码。



`break`命令用来设置断点。

- `break 行号`，断点设置在该行开始处，注意：该行并未执行。

  ```shell
  (gdb) break 19
  Breakpoint 1 at 0x8048442: file bugging.c, line 19.
  ```

- `break 文件名:行号`，适用于有多个源文件的情况。

- `break 函数名`，断点设置在该函数的开始处，断点所在行未被执行。

  ```shell
  (gdb) break foo
  Breakpoint 2 at 0x8048411: file bugging.c, line 11.
  ```

- `break 文件名:函数名`，适用于有多个源文件的情况。



`info breakpoints`命令用来显示当前断点信息。

```shell
(gdb) info breakpoints
Num     Type           Disp Enb Address    What
1       breakpoint     keep y   0x08048442 in main at bugging.c:19
2       breakpoint     keep y   0x08048411 in foo at bugging.c:11
```

- `Num`列代表断点编号，该编号可作为`delete/enable/disable`等控制断电命令的参数
- `Type`列代表断点类型，一般为`breakpoint`
- `Disp`列代表断点被命中后，该断点保留(keep)、删除(del)还是关闭(dis)
- `Enb`列代表该断点是`enable(y)`还是`disable(n)`
- `Address`列代表该断点处虚拟内存的地址
- `What`列代表该断点在源文件中的信息



`delete`命令用于删除断点。

`delete Num`，删除置顶断点，断点编号可通过`info breakpoints`获得。

`delete`，不带任何参数，默认删除所有断点。



`disable`命令和`enable`命令分别用于关闭和启用断点。`disable`和`enable`命令影响的是`info breakpoints`的`Enb`列，表示该断点是启用还是关闭。

`disable Num`，关闭指定断点，断点编号可通过`info breakpoints`获得。

`disable`，不带任何参数，默认关闭所有断点。

`enable Num`，启动指定断点，断点编号可通过`info breakpoints`获得。

`enable`，不带任何参数，默认启用所有断点。

`enable`命令还可以用来设置断点被执行的次数。



`enable once Num`，断点命中一次之后关闭该断点。

`enable delete Num`，断点命中一次之后删除该断点。

这两个命令影响的是`info breakpoints`的`Disp`列，表示该断点被命中之后的行为。



`info locals`

打印当前断点处所在函数的所有局部变量的值，不包括函数参数。

`print 变量或表达式`

打印表达式的值，可显示当前函数的变量的值、全局变量的值等。

`print/FMT`可以控制打印的格式，常见的有`x`（十六进制）、`t`（二进制）、`c`（字符）等。



`run`命令用于启动待调试程序，并运行到断点处停下。

`run`，不带任何参数，启动待调试程序，不传递参数。

`run 参数`，有些程序需要跟参数，直接带上参数列表即可，会传递给`main`函数的`argc`和`argv`。



`next`，`step`，`finish`，`continue`，`until`用于控制整个调试过程中，程序执行的流程，

`next`单步执行，函数调用当作一条指令，不会进入被调函数内部。

`next N`表示单步执行`N`次。

`step`单步执行，会进入到被调函数内部。

`step N`表示单步执行`N`次。

`finish`执行程序到当前函数结束。

`continue`执行程序到下个断点。

`until`

`until N`执行程序到程序的某一行。



`info proc mappings`可以查看待调试进程的内存分布情况

```shell
(gdb) info proc mappings
process 2682
Mapped address spaces:

	Start Addr   End Addr       Size     Offset objfile
	 0x8048000  0x8049000     0x1000        0x0 /home/dy/gdbtest/bugging
	 0x8049000  0x804a000     0x1000        0x0 /home/dy/gdbtest/bugging
	 0x804a000  0x804b000     0x1000     0x1000 /home/dy/gdbtest/bugging
	0xf7e0d000 0xf7e0e000     0x1000        0x0 
	0xf7e0e000 0xf7fbb000   0x1ad000        0x0 /lib32/libc-2.23.so
	0xf7fbb000 0xf7fbc000     0x1000   0x1ad000 /lib32/libc-2.23.so
	0xf7fbc000 0xf7fbe000     0x2000   0x1ad000 /lib32/libc-2.23.so
	0xf7fbe000 0xf7fbf000     0x1000   0x1af000 /lib32/libc-2.23.so
	0xf7fbf000 0xf7fc2000     0x3000        0x0 
	0xf7fd3000 0xf7fd4000     0x1000        0x0 
	0xf7fd4000 0xf7fd7000     0x3000        0x0 [vvar]
	0xf7fd7000 0xf7fd9000     0x2000        0x0 [vdso]
	0xf7fd9000 0xf7ffc000    0x23000        0x0 /lib32/ld-2.23.so
	0xf7ffc000 0xf7ffd000     0x1000    0x22000 /lib32/ld-2.23.so
	0xf7ffd000 0xf7ffe000     0x1000    0x23000 /lib32/ld-2.23.so
	0xfffdd000 0xffffe000    0x21000        0x0 [stack]
```



`backtrace`查看函数调用栈的情况，可以简写为`bt`，也可以用`where`、`info stack`。

`backtrace full`、`where full`、`info stack full`查看函数调用情况的同时，打印所有局部变量的值。

```shell
(gdb) bt full
#0  foo (n=100) at bugging.c:11
        sum = -136158980
        i = 1
#1  0x08048458 in main (argc=1, argv=0xffffd364) at bugging.c:24
        result = 0
        N = 100

```



`info frame Num`查看某个函数栈帧的详细信息。

```shell
(gdb) info frame 0
Stack frame at 0xffffd29c:
 eip = 0x8048411 in foo (bugging.c:11); saved eip = 0x8048458
 called by frame at 0xffffd2d0
 source language c.
 Arglist at 0xffffd294, args: n=100
 Locals at 0xffffd294, Previous frame's sp is 0xffffd29c
 Saved registers:
  ebp at 0xffffd294, eip at 0xffffd298
(gdb) info frame 1
Stack frame at 0xffffd2d0:
 eip = 0x8048458 in main (bugging.c:24); saved eip = 0xf7e26647
 caller of frame at 0xffffd29c
 source language c.
 Arglist at 0xffffd2b8, args: argc=1, argv=0xffffd364
 Locals at 0xffffd2b8, Previous frame's sp is 0xffffd2d0
 Saved registers:
  ebp at 0xffffd2b8, eip at 0xffffd2cc
```





**附：**

部分`gdb`常用命令：

|       命令       | 简写形式  |             说明             |
| :--------------: | :-------: | :--------------------------: |
|       list       |     l     |           查看源码           |
|    backtrace     | bt, where |        打印函数栈信息        |
|       next       |     n     |          执行下一行          |
|       step       |     s     | 一次执行一行，遇到函数会进入 |
|      finish      |           |        运行到函数结束        |
|     continue     |     c     |           继续运行           |
|      break       |     b     |           设置断点           |
| info breakpoints |           |         显示断点信息         |
|      delete      |     d     |           删除断点           |
|      print       |     p     |        打印表达式的值        |
|       run        |     r     |           启动程序           |
|      until       |     u     |         执行到指定行         |
|       info       |     i     |           显示信息           |
|       help       |     h     |           帮助信息           |



查询命令用法：

```shell
(gdb) help command
```



执行`shell`命令

```shell
(gdb) !shell_cmd
```


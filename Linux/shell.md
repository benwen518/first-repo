# shell
Shell是用户和系统（内核）之间的接口，是一个交互的命令解释器，它提供一组公用程序，利用Kernel（内核）功能完成用户提出的任务。
	Shell的任务：
	（a）分析命令；
	（b）处理通配符、重定向、管道和作业控制；
	（c）搜索命令并执行。

```linux
ls *
//列出所有非隐藏文件
```

### shell的种类
- （1）/bin/sh－－B-shell由R.Bourne在Bell实验室开发，Unix的准Shell
- （2）/bin/csh－－C-shell由Bill Joy在加州大学开发，提供历史机制和别名替换
- （3）/bin/bash－－Bourne Again Shell Linux标准Shell，其兼容B-Shell。

#### bash基本功能
##### 名称补全
- 命令别名
alias  dir=‘ls – –color=tty’增加一个别名
unalias dir	删除一个别名
- 命令历史机制
history
列出命令史（有记录限制）
- 每次登录后定义后才可使用
- shell配置文件可自动执行

alias dir='ls -color=auto'
dir

### shell结构
第一行一般写作：
\#！**/bin/bash**
\#! 称为一个幻数，内核用它来标识来解释执行命令表中行的程序。该行必须在命令表的顶部。

可执行语句和Bourne shell 结构: 一个Bourne shell 程序由Linux命令、 Bourne  shell 命令、控制语句和注释组成。

注释（comments），是那些前面有一个井号（#）的行。其可以是自成一行，或跟在一个命令（可执行语句）之后。对命令表和命令行进行注释。

### Shell脚本的执行方式
- 输入重定向到脚本
bash<脚本名
- 将脚本作为bash的参数
bash  脚本名
- 为脚本添加可执行权限后，直接执行
chmod a+x 脚本名
./脚本名

```linux
vim a.sh
#！bin/bash
echo hello my class
echo today is 'date'
ls

bash < a.sh
bash a.sh
chmod a+x a.sh
./a.sh
```

### Bash shell环境配置文件
- 全局配置文件
  - /etc/profile
  - /etc/bashrc
- 用户配置文件
  - ~/.bash_profile、~/.bash_login、~/.profile 
  - ~/.bashrc
  - ~/.bash_logout

```
cat /etc/profile
vim /etc/profile
```

### Shell 变量
shell变量分为两类：
- 一是标准shell变量，用户登录时Shell为建立用户环境而注册的变量，也称环境变量；
- 另一类是用户自己定义的变量，即用户变量(临时变量)。
### 用户变量与环境变量在脚本与()中的差异
环境变量会被子进程所继承
```
(ls)#启动子shell
{ls；}#当前进程执行

echo $a#显示用户变量a
(echo $a)#显示用户变量a,()所启动的子进程会继承当前shell的所有变量，包括用户变量

vim a.sh
#！/bin/bash
echo $a

./a.sh#不显示环境变量a是由于脚本执行会启动子进程，只继承环境变量，不会继承用户变量
```

```
echo $HOME#输出环境变量

vim a.sh
#！/bin/bash
echo $HOME

./a.sh#也会输出环境变量
```

#### 变量命名
以字母或下划线开始，后可以是字母、数字和下划线，注意区分大小写。

#### 变量赋值
变量名=值     
注意：赋值号两边没有**空格**

#### 变量引用
```
a="/e"
echo $a
echo  "$a is value of \$a"
cd "${a}tc/httpd" #
cd "$atc/httpd" #变量指向atc而不是a
```
shell中变量可以任意变换，而且没有浮点型（小数）
```
a=1
a=sd
```

### shell变量
eg：文件名填充至数组中
- ```
	a=`ls`
	#``或$()	命令替换
	echo $a

	f=('echo $a')

	echo ${f[0]}

	x=(`ls`)#ls执行结果替换到括号中，再执行赋值

	h=(*)

eg:文件内容作为数组元素进行填充
- ```
	fg=(`cat a.sh`)

### 环境变量
环境变量是Shell为了维护用户的使用环境而定义的一些变量。Linux环境（Shell环境）由许多变量组成，这些变量决定了用户环境的外观。环境变量是被**导出的变量**。
- **环境变量**可以被当前Shell下启动的子进程(子Shell) 所继承，
- **局部（用户）变量**不被继承；

而且子进程的环境变量独立于父进程，子进程中对环境变量的修改不影响父进程变量的值。
eg:shell脚本修改当前工作路径，当退出脚本时，工作路径不会发生变化
- ```
 	vim a.sh

 	#!/bim/bash
 	cd /etc
 	ls

	./a/sh
	#可正常执行，但当前工作路径未发生变化

	#脚本执行时会启动子进程进行实现，不会对当前进程产生任何影响
  ```
eg:脚本执行对当前进程产生影响的方法
- ```
	. ./a.sh
  ```
com:脚本的执行不会对当前环境与变量产生影响

### 常用环境变量
- \$HOME	   用户的注册目录（用户主目录）；同～
- \$SHELL       设置用户的shell类型
- \$USER	   保存当前的用户名
- \$PATH	 定义查找命令的目录列表，目录名用冒号隔开
- \$PWD		保存用户当前在文件系统的位置
- \$PS1		定义shell的主提示符
- \$PS2		定义shell的副提示符
- \$IFS		域内分隔符

eg:添加当前工作目录至path
- ```
	echo $PATH
	#执行脚本不再加./前缀
	#原有的path值不能改动
	PATH=$PATH:./
	
	PATH=./:$PATH
	#首先搜索当前目录，会导致
	echo $PATH
	a.sh
	#可直接执行
  ```





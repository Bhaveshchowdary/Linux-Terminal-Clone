# Linux-Terminal-Clone
Developed a custom Linux terminal with essential Unix commands.

This terminal can execute ls,cp,mv,grep,ps commands with few options:

1)ls:
	ls [OPTION]
	This works as original command ls.
	This sub options for this command that can be executed are:
	1) -l  2) -a  3) -s 4) -o 5) -g

2)ps:
        ps [OPTION]
        This works as original command ps.
        This sub options for this command that can be executed are:
        1) -a  2) -af  3) -aF 4) -p

3)cp:
        cp [OPTION] [SOURCE] [DESTINATION]
        This works as original command cp.
        This sub options for this command that can be executed are:
        1) -i  2) -v  3) -n 4) -u

4)mv:
        mv [OPTION] [SOURCE] [DESTINATION]
        This works as original command mv.
        This sub options for this command that can be executed are:
        1) -i  2) -v  3) -n 4) -u 

5)grep:
        grep [OPTION] PATTERN [FILE] [FILE] ...
        This works as original command grep.
        This sub options for this command that can be executed are:
        1) -c  2) -v  3) -n 4) -m

Type 'man [COMMAND]'  and ENTER for detailed usage of options for each command.

cd command is executed using chdir() function.

The requirements to execute this terminal are:
-->A linux ubuntu machine.
-->GCC should be installed in the machine :
	If GCC is not installed in your machine,do the following:
	open the terminal on your machine and run the following commands:
		--> "sudo apt update"
		--> "sudo apt install build-essential"
		OR
		--> "sudo apt install gcc"
	To check if installed then run the following command:
		--> "gcc --version"
--> libreadline:
Install libreadline in your machine:
For that run the following command on your terminal:
		--> "sudo apt-get install libreadline8 libreadline-dev"
Now you are ready to execute the terminal!

steps to execute:

-->change the directory to the directory where the files are located.
-->Now run the following commands:
	--> "make" (To compile the executable files.)
	--> "./myshell" (To execute the terminal.)

Now you can run whichever command you want to run from the above mentioned commands.

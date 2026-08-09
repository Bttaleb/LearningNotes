## **Main Idea**
- Interactive programs are *menu-based*; menus operate by:
	1. presenting user with list of commands
	2. after user selects command, program performs action
	3. prompting user for another command
	4. program continues until user selects "exit" or "quit"
### **Pseudocode**
```c
for (;;) {
	prompt user to enter a command;
	read command;
	execute command;
}
```
the `executing command` requires a switch statement that reads like:
```c
switch (command) {
	case command_1: perform operation_1; break;
	case command_2: perform operation_2; break;
	.
	.
	.
	case command_n: perform operation_n; break;
	default: print error message; break;
}
```
### **Goal**
Develop a program that maintains a checkbook balance
Offer user a menu of choices
1. clear account balance
2. credit money to account
3. debit money from account
4. display current balance
5. exit program
## What the session looks like
```c
Commands: 0=clear, 1=credit, 2=debit, 3=balance, 4=exit

Enter command: 1
Enter amount of credit: 1042.56
Enter command: 2
Enter amount of debit: 133.79
Enter command: 1
Enter amount of credit: 1754.32
Enter command: 2
Enter amount of debit: 1400
Enter command: 2
Enter amount of debit: 68
Enter command: 2
Enter amount of debit: 50
Enter command: 3
Current balance: $1145.09
Enter command: 4
```

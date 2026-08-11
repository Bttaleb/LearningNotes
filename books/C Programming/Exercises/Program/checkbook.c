#include <stdio.h>

/*
 * 1. Present our user with list of Commands
 * 2. User selects one of the Commands
 * 3. Program performs the action
 * 4. Program prompts user for another Command
 * 5. Program continues until user selects "exit command"
 */

int main () {
    float balance, credit, debit = 0.00f;
    int cmd;
    for (;;) {
        printf("Commands: 0=clear, 1=credit, 2=debit, 3=balance, 4=exit");
        scanf("%d", &cmd);
    }

}

#include <stdio.h>

/*
 * 1. Present our user with list of Commands
 * 2. User selects one of the Commands
 * 3. Program performs the action
 * 4. Program prompts user for another Command
 * 5. Program continues until user selects "exit command"
 */

int main () {
    float balance = 0.00f, credit, debit;
    int cmd;
    for (;;) {
        printf("Commands: 0=clear, 1=credit, 2=debit, 3=balance, 4=exit\n");
        scanf("%d", &cmd);
        switch (cmd) {
            case 0:
                balance = 0.00f;
                break;
            case 1:
                printf("Enter amount of credit: ");
                scanf("%f", &credit); // %f for floating point, & to assign the input to "credit" variable
                balance += credit;
                break;
            case 2:
                printf("Enter amount of debit: ");
                scanf("%f", &debit); //read floating point, assign to "debit" variable
                balance -= debit;
                break;
            case 3:
                printf("$%.2f\n", balance);
                break;
            case 4:
                return 0;
            default:
                printf("Commands: 0=clear, 1=credit, 2=debit, 3=balance, 4=exit\n");
                break;
        }
    }

}

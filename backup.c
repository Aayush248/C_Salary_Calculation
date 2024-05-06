#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *fptr;

struct payroll
{
    float hours;
    float rate;
};
struct user_info
{
    char name[50];
    char job[20];
    char date[50];
    struct payroll pay[50];
};

void printMessageCenter(const char *message)
{
    int len = 0;
    int pos = 0;
    // calculate how many space need to print
    len = (78 - strlen(message)) / 2;
    printf("\t\t\t");
    for (pos = 0; pos < len; pos++)
    {
        // print space
        printf(" ");
    }
    // print message
    printf("%s", message);
}

// Head message
void headMessage(const char *message)
{
    system("cls");
    printf("\t\t\t###########################################################################");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t############                  Salary Calculation               ############");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t###########################################################################");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printMessageCenter(message);
    printf("\n\t\t\t---------------------------------------------------------------------------");
}

// functions to generate biils
void generateBillHeader(char name[50], char job[20], char date[30])
{
    printf("\n\n");
    headMessage("Invoice");
    printf("\n\n\n\t\t\t\t\tDate: %s", date);
    printf("\n\t\t\t\t\tPaycheque To: %s", name);
    printf("\n\t\t\t\t\tRole: %s", job);
    printf("\n");
    printf("\t\t\t\t\t---------------------------------------\n");
    // printf("Job\t\t");
    printf("\t\t\t\t\tRate");
    printf("\t\tHours");
    printf("\t\tTotal");
    printf("\n\t\t\t\t\t---------------------------------------");
    printf("\n\n");

    fprintf(fptr, "Name: %s", name);
    fprintf(fptr, "\nDate: %s", date);
    fprintf(fptr, "\nRole: %s", job);
}

void generateBillBody(float rate, float hours)
{
    // printf("%s\t\t",job);
    printf("\t\t\t\t\t%.2f\t\t", rate);
    printf("%.2f\t\t", hours);
    printf("%.2f", rate * hours);
    printf("\n");
}

void generateBillFooter(float total)
{
    printf("\n");
    float pf = 0.1 * total; // pf = provident fund
    float netTotal = total - pf;
    float tax = 0.12 * netTotal;
    float grandTotal = netTotal - tax;

    fprintf(fptr, "\nSub Total: %.2f", total);
    fprintf(fptr, "\nPF: %.2f", pf);
    fprintf(fptr, "\nNet Total: %.2f", netTotal);
    fprintf(fptr, "\nTax: %.2f", tax);
    fprintf(fptr, "\nGrand Total: %.2f\n", grandTotal);
    fprintf(fptr, "\n");

    printf("\t\t\t\t\t---------------------------------------\n");
    printf("\t\t\t\t\tSub Total\t\t\t%.2f", total);
    printf("\n\t\t\t\t\tProvident Fund @10%s\t\t%.2f", "%", pf);
    printf("\n\t\t\t\t\t\t\t\t\t-------");
    printf("\n\t\t\t\t\tNet Total\t\t\t%.2f", netTotal);
    printf("\n\t\t\t\t\tTax @12%s\t\t\t%.2f", "%", tax);
    printf("\n\t\t\t\t\t---------------------------------------");
    printf("\n\t\t\t\t\tGrand Total\t\t\t%.2f", grandTotal);
    printf("\n\t\t\t\t\t---------------------------------------\n");
}

void information()
{
    int i;
    float hours_worked, rate;
    struct user_info user;
    char flag = 'y';
    float sumTotal = 0;

    fptr = fopen("userData.txt", "a");

    headMessage("USER INFORMATION");

    printf("\n\n\t\t\t\tEnter the name of the employee: ");
    fgets(user.name, 50, stdin);
    user.name[strlen(user.name) - 1] = 0; // to absorb \n, store gaarda " ram\n store gardinxa"

    printf("\n\t\t\t\tEnter your job: ");
    fgets(user.job, 20, stdin);
    user.job[strlen(user.job) - 1] = 0;

    printf("\n\t\t\t\tEnter the hours you have worked: ");
    scanf("%f", &user.pay[0].hours);

    printf("\n\t\t\t\tEnter your pay per hour : $");
    scanf("%f", &user.pay[0].rate);

    // catches "/n" from above scanf, else the program doesnt take input for scanf flag
    fgetc(stdin);

    printf("\n\t\t\t\tDid you work extra hours [y/n]: ");
    scanf("%c", &flag);

    if (flag == 'y')
    {
        printf("\n\t\t\t\tEnter the extra hours you have worked: ");
        scanf("%f", &user.pay[1].hours);

        printf("\n\t\t\t\tEnter your pay per hour for over time: $");
        scanf("%f", &user.pay[1].rate);
    }
    strcpy(user.date, __DATE__);

    generateBillHeader(user.name, user.job, user.date);
    if (flag == 'y')
    {
        for (i = 0; i < 2; i++)
        {
            generateBillBody(user.pay[i].rate, user.pay[i].hours);
            sumTotal = sumTotal + (user.pay[i].rate * user.pay[i].hours);
        }
    }
    else
    {
        generateBillBody(user.pay[0].rate, user.pay[0].hours);
        sumTotal = sumTotal + (user.pay[0].rate * user.pay[0].hours);
    }
    fprintf(fptr, "\nHours Worked: %.2f", user.pay[0].hours);
    fprintf(fptr, "\nNormal Rate: %.2f", user.pay[0].rate);
    fprintf(fptr, "\nNormal Pay: %.2f", user.pay[0].hours * user.pay[0].rate);
    fprintf(fptr, "\nOT Hour: %.2f", user.pay[1].hours);
    fprintf(fptr, "\nOT Rate: %.2f", user.pay[1].rate);
    fprintf(fptr, "\nOT Pay: %.2f", user.pay[1].hours * user.pay[1].rate);

    generateBillFooter(sumTotal);
}

void show_all_paycheques()
{
    char read_data[150];
    system("clear");
    fptr = fopen("userData.txt", "r");

    if (fptr != NULL)
    {
        while (fgets(read_data, 150, fptr))
        {
            printf("%s", read_data);
        }
    }
    fclose(fptr);
}

void search_paycheques()
{
    FILE *fp;
    fp = fopen("userData.txt", "r"); // open file

    char apple[256], search[25];
    int f = 0;
    char read_data[150];
    int check = 0;

    printf("\t\t\t\tEnter a name: ");
    scanf("%s", search);


    while (fgets(apple, sizeof(apple), fp))
    {
        f++;
        if (strstr(apple, search) != NULL)
        {
            printf("\n\n\t\t\t\t%s", apple);
            for (int i = 1; i <= 14; i++)
            {
                fgets(read_data, 150, fp);
                printf("\t\t\t\t%s", read_data);
            }
            check = 1;
        }
    }
    if (check == 0)
    {
        printf("\n\n\t\t\t\t\t\tName Not Found!!!\n\n\n");
    }
}

int main()
{
    int choice;

    headMessage("MAIN MENU");
    printf("\n\n\t\t\t\tPlease select your prefered operation");
    printf("\n\n\t\t\t\t1. Generate Paycheque");
    printf("\n\t\t\t\t2. Show all Paycheque");
    printf("\n\t\t\t\t3. Search Paycheque");
    printf("\n\t\t\t\t4. Exit");

    printf("\n\n\t\t\t\tYour choice: ");
    scanf("%d", &choice);
    fgetc(stdin); // to absorb \n form scan f

    switch (choice)
    {
    case 1:
        information();
        break;
    case 2:
        show_all_paycheques();
        break;
    case 3:
        search_paycheques();
        break;
    case 4:
        printf("\n\n\n\t\t\t\t\t\tThank you!!!\n\n\n\n\n");
        exit(1);
        break;
    default:
        printf("\n\n\n\t\t\t\t\tINVALID INPUT!!! Try again...");
    }
}

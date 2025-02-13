#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
typedef struct
{
    int month;
    int year;
} Date;

typedef struct
{
    char account_number[11];
    char name[50];
    char email_address[50];
    double balance;
    char mobile[20];
    Date Do;
} Account;

typedef struct
{
    char username[20];
    char pass[20];
} User;

Account accounts[100];
User users[100];
int countU=0;
int countA=0;
void menu()
{
    char accNumber[11],accSender[11],accReceiver[11],keyword[20];
    char x[20];
    Load();
    printf("\nChoose an option:");
    printf("\n1.ADD\n2.DELETE\n3.MODIFY\n4.SEARCH\n5.ADVANCED SEARCH\n6.WITHDRAW\n7.DEPOSIT\n8.TRANSFER\n9.REPORT\n10.PRINT\n11.QUIT\n");
    printf("Enter the number of your choice: ");
    gets (x);
    if(strcmp(x,"1")==0)
        add();
    else if(strcmp(x,"2")==0)
    {
        do
        {
            printf("Enter account number to delete: ");
            gets(accNumber);
        }
        while(!ValidAcc(accNumber));
        Delete(accNumber);
    }
    else if(strcmp(x,"3")==0)
    {
        do
        {
            printf("Enter account number to modify: ");
            gets(accNumber);
        }
        while(!ValidAcc(accNumber));
        Modify(accNumber);
    }
    else if(strcmp(x,"4")==0)
    {
        do
        {
            printf("Enter account number to search: ");
            gets( accNumber);
        }
        while(!ValidAcc(accNumber));
        Search(accNumber);
    }
    else if(strcmp(x,"5")==0)
    {
        printf("Enter a keyword to search for: ");
        getchar();
        gets(keyword);
        advancedSearch(keyword);
    }
    else if(strcmp(x,"6")==0)
    {
        do
        {
            printf("Enter account number to withdraw: ");
            gets( accNumber);
        }
        while(!ValidAcc(accNumber));
        Withdraw(accNumber);
    }
    else if(strcmp(x,"7")==0)
    {
        do
        {
            printf("Enter account number to deposit: ");
            gets(accNumber);
        }
        while(!ValidAcc(accNumber));
        Deposit(accNumber);

    }
    else if(strcmp(x,"8")==0)
    {
        do
        {
            printf("Enter account number of sender and receiver :\n ");
            gets(accSender);
            gets(accReceiver);
        }
        while(!ValidAcc(accSender)&&!ValidAcc(accReceiver));
        Transfer(accSender,accReceiver);
    }

    else if(strcmp(x,"9")==0)
    {
        do
        {
            printf("Enter account number: ");
            gets(accNumber);
        }
        while(!ValidAcc(accNumber));
        Report(accNumber);
    }
    else if(strcmp(x,"10")==0)
        Print();
    else if(strcmp(x,"11")==0)
        exit(0);
    else
    {
        printf("Invalid");
        menu();
    }


}
int ValidEmail(char email[20])
{
    int i,j,k,x,flag1=0,flag2=0,flag3=0,flag4=0;
    for(i=0; i<strlen(email); i++)
    {
        if(email[i]=='@')
            x=i;
        if(email[i]=='@'&&(email[i+1]!='.'||email[i-1]!='.'))
            flag1=1;
        else if((email[i+1]!='@'||email[i-1]!='@')&&email[i]=='.')
            flag2=1;
    }
    for(k=0; k<strlen(email); k++)
        if(email[k]=='@'&&k!=x)
            flag4=1;
    for(j=x+2; j<strlen(email); j++)
        if(email[j]=='.')
            flag3=1;
    if (flag1==1&&flag2==1&&flag3==1&&flag4==0)
        return 1;
    else
        return 0;
}
int ValidMobile(char mobile[12])
{
    for(int i=0; i<strlen(mobile); i++)
        if(!(mobile[i]>='0'&&mobile[i]<='9'))
            return 0;
    return 1;
}
int ValidAcc(char acc[11])
{
    int c=0;
    for(int i=0; i<strlen(acc); i++)
        if(acc[i]>='0'&&acc[i]<='9')
        {
            c++;
        }
    if (c==10)
        return 1;
    else
        return 0;
}
int ValidBalance(char balance[20])
{
    int flag=0;
    for(int i=0; i<strlen(balance); i++)
        if(balance[i]>='0'&&balance[i]<='9')
            flag=1;
    if (flag==1)
        return 1;
    else
        return 0;
}
void Uppercase(char a[])
{
    int i;
    for(i=0; i<strlen(a); i++)
    {
        if(a[i]>='a'&&a[i]<='z')
            a[i]=a[i]-32;
    }
}
void Load()
{
    countA=0;
    float balance;
    int i;
    char line[100];
    FILE *F2 = fopen("accounts.txt", "r");
    if(F2== NULL)
    {
        printf("file not found");
        return ;
    }
    while (!feof(F2))
    {
        char *token;
        fgets(line,100,F2);
        token =strtok(line,",-");
        strcpy(accounts[countA].account_number,token);
        token =strtok(NULL,",-");
        strcpy(accounts[countA].name,token);
        token =strtok(NULL,",-");
        strcpy(accounts[countA].email_address,token);
        token=strtok(NULL,",-");
        balance=atof(token);
        accounts[countA].balance=balance;
        token =strtok(NULL,",-");
        strcpy(accounts[countA].mobile,token);
        token =strtok(NULL,",-");
        accounts[countA].Do.month = atoi(token);
        token =strtok(NULL,",-");
        accounts[countA].Do.year = atoi(token);
        countA++;
    }
    fclose(F2);
}
void SortByName()
{
    Account temp;
    for(int i=0; i<countA; i++)
    {
        for(int j=i+1; j<countA; j++)
        {
            if(strcasecmp(accounts[i].name,accounts[j].name)>1)
            {
                temp=accounts[j];
                accounts[j]=accounts[i];
                accounts[i]=temp;
            }
        }

    }

}
void SortByBalance()
{
    int i,j;
    Account temp;
    for(i=0; i<countA; i++)
    {
        for(j=i+1; j<countA; j++)
        {
            if(accounts[j].balance>accounts[i].balance)
            {
                temp=accounts[j];
                accounts[j]=accounts[i];
                accounts[i]=temp;
            }
        }
    }
}
void SortByDate()
{
    Account temp;
    for(int i=0; i<countA; i++)
    {
        for(int j=i+1; j<countA; j++)
        {
            if(accounts[j].Do.year>accounts[i].Do.year)
            {
                temp=accounts[j];
                accounts[j]=accounts[i];
                accounts[i]=temp;
            }
            else if(accounts[j].Do.year==accounts[i].Do.year)
            {
                if(accounts[j].Do.month>accounts[i].Do.month)
                {
                    temp=accounts[j];
                    accounts[j]=accounts[i];
                    accounts[i]=temp;
                }

            }
        }

    }
}
char* changeMonth(int x)
{
    char*a=malloc(20);
    if(x==1)
        strcpy(a,"January");
    else if(x==2)
        strcpy(a,"February");
    else if(x==3)
        strcpy(a,"March");
    else if(x==4)
        strcpy(a,"April");
    else if(x==5)
        strcpy(a,"May");
    else if(x==6)
        strcpy(a,"June");
    else if(x==7)
        strcpy(a,"July");
    else if(x==8)
        strcpy(a,"August");
    else if(x==9)
        strcpy(a,"September");
    else if(x==10)
        strcpy(a,"October");
    else if(x==11)
        strcpy(a,"November");
    else
        strcpy(a,"December");
    return a;
}
void Login()
{
    char username[20], pass[20];
    int i, is_user_found=0;
    printf("Enter username: ");
    gets(username);
    printf("Enter password: ");
    gets(pass);
    FILE *f1=fopen("users.txt","r");

    if(f1 == NULL)
    {
        printf("Not found");
        exit(0);
    }

    while(!feof(f1))
    {
        fscanf(f1,"%s",users[countU].username);
        fscanf(f1,"%s",users[countU].pass);
        if (!strcmp(username, users[countU].username) && !strcmp(pass, users[countU].pass))
        {
            is_user_found=1;
            fclose(f1);
            menu();
            break;
        }

        countU++;
    }

    if(is_user_found==0)
    {
        printf("Incorrect username or password\n");
        mainMenu();
    }
}
void save()
{
    FILE*f1=fopen("accounts.txt","w");
    for(int i=0; i<countA; i++)
    {
        fprintf(f1,"%s,",accounts[i].account_number);
        fprintf(f1,"%s,",accounts[i].name);
        fprintf(f1,"%s,",accounts[i].email_address);
        fprintf(f1,"%lf,",accounts[i].balance);
        fprintf(f1,"%s,",accounts[i].mobile);
        fprintf(f1,"%d-%d",accounts[i].Do.month,accounts[i].Do.year);
        if(i!=countA-1)
            fprintf(f1,"\n");
    }
    fclose(f1);
}
void advancedSearch(char a[])
{
    Uppercase(a);
    int i,flag=0;
    char x[20];
    char n[20];
    char*ptr;
    for(i=0; i<countA; i++)
    {
        strcpy(n,accounts[i].name);
        Uppercase(n);
        ptr=strstr(n,a);
        if(ptr!=NULL)
        {
            flag=1;
            printf("Account Number:%s\n", accounts[i].account_number);
            printf("Name:%s\n", accounts[i].name);
            printf("E-mail:%s\n", accounts[i].email_address);
            printf("Balance:%lf$\n", accounts[i].balance);
            printf("Mobile:%s\n", accounts[i].mobile);
            char *x=changeMonth(accounts[i].Do.month);
            printf("Date opened:%s %d\n\n",x, accounts[i].Do.year);
        }
    }
    if(flag==0)
        printf("No matches are found\n");
    menu();
}


void Search(char accNo[11])
{
    int i, flag = 0;
    for (i = 0; i < countA; i++)
    {
        if (!strcmp(accNo, accounts[i].account_number))
        {
            flag = 1;
            break;
        }
    }
    if (flag == 1)
    {
        printf("Account Number:%s\n", accounts[i].account_number);
        printf("Name:%s\n", accounts[i].name);
        printf("E-mail:%s\n", accounts[i].email_address);
        printf("Balance:%lf$\n", accounts[i].balance);
        printf("Mobile:%s\n", accounts[i].mobile);
        char *x=changeMonth(accounts[i].Do.month);
        printf("Date opened:%s  %d",x, accounts[i].Do.year);
    }
    else
        printf("%s not found\n", accNo);
    menu();
}
void mainMenu()
{

    int  flag = 0;
    char x[20];
    do
    {
        printf("1.Login\n2.Quit\n");
        printf("Enter 1 or 2: ");
        gets(x);
        if (strcmp(x,"1")==0)
        {
            flag = 1;
            Login();
        }
        else if(strcmp(x,"2")==0)
            exit(0);
        else
        {
            printf("Invalid\n");
            mainMenu();
        }
    }
    while (flag == 0);
}
void add()
{
    char x[20];
    time_t t=time(NULL);
    struct tm tm=*localtime(&t);
    int m=tm.tm_mon +1;
    int y=tm.tm_year+1900;
    int i, flag=0;
    char balance[20];
    Account a;
    do
    {
        printf("Enter the account number: ");
        gets(a.account_number);
    }
    while(!ValidAcc(a.account_number));

    printf("Enter name: ");
    gets(a.name);
    do
    {
        printf("Enter email address: ");
        gets(a.email_address);
    }
    while(!ValidEmail(a.email_address));
    do
    {
        printf("Enter balance: ");
        gets(balance);
    }
    while(!ValidBalance(balance));
    a.balance=atof(balance);
    do
    {
        printf("Enter mobile: ");
        gets(a.mobile);
    }
    while(!ValidMobile(a.mobile));
    for(i=0; i<countA; i++)
    {
        if(!strcmp(a.account_number,accounts[i].account_number))
            flag=1;
    }
    if(flag==1)
        printf("Error duplicated account number");
    else
    {
        printf("1.Save\nAny key to Discard\n");
        gets(x);
        if(strcmp(x,"1")==0)
        {
            accounts[countA]=a;
            accounts[countA].Do.month=m;
            accounts[countA].Do.year=y;
            countA++;
            save();
            printf("Account created successfully");
        }
        else
            printf("Your data is discarded");
    }
    menu();
}
void Delete(char accnum[11])
{
    char x[20];
    int i,flag=0;
    for(i=0; i<countA; i++)
    {
        if(!strcmp(accnum,accounts[i].account_number))
        {
            flag=1;
            break;
        }
    }
    if(flag==1)
    {
        if(accounts[i].balance!=0.0)
            printf("Can't delete it,Balance greater than zero");
        else
        {
            printf("Are you sure to delete %s account",accnum);
            printf("\n1.Yes\n2.No\n");
            gets(x);
            if(strcmp(x,"1")==0)
            {
                accounts[i]=accounts[countA-1];
                countA--;
                save();
                printf("Account is deleted successfully");
            }
            else
                printf("Account isn't deleted");

        }

    }
    else
        printf("Account isn't found");
    menu();
}
void Modify(char accnum[20])
{
    int flag=0;
    char name[20],mobile[20],email[20],x[20],j[20];
    int i;
    FILE*f1=fopen("accounts.txt","a");
    for(i=0; i<countA; i++)
        if(!strcmp(accnum,accounts[i].account_number))
        {
            flag=1;
            break;

        }
    if(flag==1)
    {
        do
        {
            printf("Enter the data you want to modify: ");
            printf("\n1.Name\n2.Mobile\n3.Email\n");
            gets(x);
        }
        while(!strcmp(x,"1")==0&&!strcmp(x,"2")==0&&!strcmp(x,"3")==0);
        if(strcmp(x,"1")==0)
        {
            printf("Enter new name: ");
            gets(name);
            strcpy(accounts[i].name,name);
        }
        else if(strcmp(x,"2")==0)
        {
            do
            {
                printf("Enter new mobile: ");
                gets(mobile);
            }
            while(!ValidMobile(mobile));
            strcpy(accounts[i].mobile,mobile);
        }
        else if(strcmp(x,"3")==0)
        {
            do
            {
                printf("Enter new email: ");
                gets(email);
            }
            while(!ValidEmail(email));
            strcpy(accounts[i].email_address,email);
        }


        do
        {
            printf("1.Save\n2.Discard\n");
            gets(j);
        }
        while(!strcmp(j,"1")==0&&!strcmp(j,"2")==0);
        if(strcmp(j,"1")==0)
        {
            save();
            printf("Account is updated");
        }
        else
            printf("Your data is discarded");
    }

    else
        printf("Account number not found");
    menu();
}
void Withdraw(char accnum[20])
{
    char x[20];
    int flag=0,i;
    double amountW;
    do
    {
        printf("Enter amount you need to withdraw: ");
        gets(x);
    }
    while(!ValidBalance(x));
    amountW=atof(x);
    for(i=0; i<countA; i++)
    {
        if(!strcmp(accnum,accounts[i].account_number))
        {
            flag=1;
            break;
        }
    }
    if(flag==1)
    {
        if(amountW>10000||accounts[i].balance<amountW)
            printf("the transaction failed");
        else
        {
            accounts[i].balance=accounts[i].balance-amountW;
            printf("Successful transaction");
            save();
            char x[15];
            strcpy(x,accnum);
            strcat(x,".txt");

            FILE *f1=fopen(x,"a");
            fprintf(f1,"%f is withdrawn from the account\n",amountW);
            fclose(f1);

        }
    }
    else
        printf("Account not found");
    menu();
}
void Deposit(char accnum[20])
{
    char x[20];
    int flag=0,i;
    double amountD;
    do
    {
        printf("Enter amount you need to deposit: ");
        gets(x);
    }
    while(!ValidBalance(x));
    amountD=atof(x);
    for(i=0; i<countA; i++)
    {
        if(!strcmp(accnum,accounts[i].account_number))
        {
            flag=1;
            break;
        }
    }
    if(flag==1)
    {
        if(amountD>10000)
            printf("the transaction failed");
        else
        {
            accounts[i].balance=accounts[i].balance+amountD;
            printf("Successful transaction");
            save();
            char x[15];
            strcpy(x,accnum);
            strcat(x,".txt");

            FILE *f1=fopen(x,"a");
            fprintf(f1,"%f is added to the account\n",amountD);
            fclose(f1);
        }
    }
    else
        printf("Account not found");
    menu();
}
void Transfer(char accSender[11],char accReceiver[11])
{
    int flag1=0,flag2=0,j,i;
    char x[20];
    double amountT;
    do
    {
        printf("Enter amount you need to transfer: ");
        gets(x);
    }
    while(!ValidBalance(x));
    amountT=atof(x);
    for(i=0; i<countA; i++)
    {
        if(!strcmp(accReceiver,accounts[i].account_number))
        {
            flag1=1;
            break;
        }
    }

    for(j=0; j<countA; j++)
    {
        if(!strcmp(accSender,accounts[j].account_number)&&accounts[j].balance>=amountT)
        {
            flag2=1;
            break;
        }
    }
    if(flag1==1&&flag2==1)
    {

        accounts[j].balance=accounts[j].balance-amountT;
        accounts[i].balance=accounts[i].balance+amountT;
        printf("Successful transaction");
        save();
        char y[15];
        strcpy(y,accReceiver);
        strcat(y,".txt");

        FILE *f1=fopen(y,"a");
        fprintf(f1,"%f is received from %s\n",amountT,accSender);
        fclose(f1);

        char x[15];
        strcpy(x,accSender);
        strcat(x,".txt");

        FILE *f2=fopen(x,"a");
        fprintf(f2,"%f is sent to %s\n",amountT,accReceiver);
        fclose(f2);

    }
    else
        printf("Transaction failed");
    menu();
}
void Report(char accnum[11])
{
    int i,count=0;
    char x[15],a[100];
    strcpy(x,accnum);
    strcat(x,".txt");
    FILE* f1=fopen(x,"r");
    char line[200][200];
    if(f1==NULL)
        printf("No transaction");
    else
    {
        while(!feof(f1))
        {
            fgets(line[count],200,f1);

            count++;
        }
        for(i=count-1; i>count-7&&i>=0; i--)
        {
            printf("%s",line[i]);
        }
    }
    menu();
}
void Print()
{
    int i;
    char x[10],a[countA];
    do
    {
        printf("1.Sort by name\n2.Sort by balance\n3.Sort by date opened\n");
        gets(x);
    }
    while(strcmp(x,"1")!=0&&strcmp(x,"2")!=0&&strcmp(x,"3")!=0);

    if(strcmp(x,"1")==0)
        SortByName();
    else if (strcmp(x,"2")==0)
        SortByBalance();
    else if(strcmp(x,"3")==0)
        SortByDate();

    for(i=0; i<countA; i++)
    {
        printf("Account Number:%s\n", accounts[i].account_number);
        printf("Name:%s\n", accounts[i].name);
        printf("E-mail:%s\n", accounts[i].email_address);
        printf("Balance:%lf$\n", accounts[i].balance);
        printf("Mobile:%s\n", accounts[i].mobile);
        char *x=changeMonth(accounts[i].Do.month);
        printf("Date opened:%s  %d\n",x, accounts[i].Do.year);
        printf("\n");
    }
    menu();
}
int main()
{
    mainMenu();
    return 0;
}

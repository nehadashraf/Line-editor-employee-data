#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <ctype.h>

#define EXTENDED -32
#define enter 13
#define ESC 27
#define TAB 9
#define right 77
#define left 75
#define home 71
#define end 79
#define backspace 8
#define delete 83

struct Employee
{
    int SSN;
    char name[18];
    int age;
    float salary;
    float commission ;
    float deduction;
    float netsalary;

};

void gotoxy( int column, int row )
{
    COORD coord;
    coord.X = column;
    coord.Y = row;
    SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
}
void textattr(int i)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
}
char* lineEditor(int _size,int col,int row,int startKey,int endKey)
{
    char *arr=malloc(_size * sizeof(char));
    int first,curr, last;
    first=curr= last=col;
    char *pfirst, *pcurr, *plast;
    pfirst= pcurr=plast=arr;

    int flag=0;
    char ch;
    gotoxy(col,row);

    do
    {
        gotoxy(curr,row);
        ch=getch();
        switch (ch)
        {

        case EXTENDED:
            ch=getch();
            switch(ch)
            {
            case home:
                pcurr=pfirst ;
                curr=first ;

                break;
            case end:
                pcurr=plast;
                curr=last;
                break;
            case left:
                if(pcurr>pfirst)
                {
                    pcurr-- ;
                    curr-- ;
                }
                break;

            case right:
                if(pcurr<plast)
                {
                    pcurr++ ;
                    curr++ ;
                }
                break;

            case delete:
                if (pcurr < plast)
                {
                    *(plast - 1) = '\0';
                    plast--;
                    last--;

                    gotoxy(curr, row);
                    gotoxy(first, row);
                    printf("%-30s", arr);
                }
                break;


            }
            break;
        case backspace:
            if (pcurr > pfirst)
            {
                pcurr--;
                curr--;

                *(plast - 1) = '\0';
                plast--;
                last--;
                gotoxy(curr, row);
                gotoxy(first, row);
                printf("%-30s", arr);
            }
            break;
        case enter:
        case ESC :
            *plast='\0' ;
            flag=1;

            break;

        default:
            if(isprint(ch))
            {
                if(pcurr <pfirst+29)
                {
                    *pcurr=ch;
                    printf("%c", ch);
                    pcurr++;
                    curr++;
                    plast++;
                    last++;
                }
            }
            else
            {
                *pcurr=ch;
                *pcurr++;
                curr++;
            }
            break;
        }
    }
    while(flag==0);
    return arr;
}

int main()
{
    int _size,col,row;
    struct Employee e1;
    gotoxy (5,5);
    printf("SSN: ");

    gotoxy (55,5);
    printf("Name: ");

    gotoxy (5,10);
    printf("Age: ");

    gotoxy (55,10);
    printf("Salary: ");

    gotoxy (5,15);
    printf("Commission: ");

    gotoxy (55,15);
    printf("Deduction: ");

    e1.SSN=atoi(lineEditor(5,10,5,48,57));

    strcpy(e1.name,lineEditor(15,61,5,65,104));
    _flushall();

    e1.age=atoi( lineEditor(5,10,10,48,57));
    _flushall();

    e1.salary=atof( lineEditor(5,63,10,48,57));
    _flushall();

    e1.commission=atof( lineEditor(5,17,15,48,57));
    _flushall();

    e1.deduction=atof( lineEditor(5,65,15,48,57));

    system("cls");

    gotoxy (10,4);
    printf("SSN:%i",e1.SSN);

    gotoxy (10,6);
    printf("Name:%s",e1.name);

    gotoxy (10,8);
    printf("Age:%i",e1.age);

    gotoxy (10,10);
    printf("Salary:%f",e1.salary);

    gotoxy (10,12);
    printf("Commission:%f",e1.commission);

    gotoxy (10,14);
    printf("Deduction:%f \n",e1.deduction);

    gotoxy (10,14);
    return 0;
}

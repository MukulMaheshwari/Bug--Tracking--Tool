#include<stdio.h>
int main()
{
    printf("These are common bug tracking tool commands used in various situations: \n\n");
    printf("For Tester module: \n\n");
    printf("bgt tester view     \t To view the bugs for current tester\n");
    printf("bgt tester create   \t To create a new bug\n\n\n");
     printf("For developer module: \n\n");
    printf("bgt developer view     \t To view the bugs for current developer\n");
    printf("bgt developer update   \t To update status of specific bug \n\n\n");
     printf("For project manager module: \n\n");
    printf("bgt pm view     \t To view all the bugs\n");
    printf("bgt pm assign   \t To assign bug to a developer \n\n\n");
    return 0;
}
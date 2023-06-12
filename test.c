# include<stdio.h>
# include <windows.h>
#include<string.h>
#include<conio.h>
int main(){
    char a[19] ,b[20] , c[20];
     a[strcspn(a, "\n")] = '\0';
          
    return 0;
}
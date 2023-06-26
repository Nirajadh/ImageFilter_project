# include<stdio.h>
#include<time.h>
int main(){
   time_t currentTime=time(NULL);
 struct tm *localTime = localtime(&currentTime);
  int year = localTime->tm_year + 1900;  
    int month = localTime->tm_mon + 1;     
    int day = localTime->tm_mday;         
    int hour = localTime->tm_hour;       
    int minute = localTime->tm_min;       
    int second = localTime->tm_sec;        

    printf("Current date and time: %04d-%02d-%02d %02d:%02d:%02d\n",
           year, month, day, hour, minute, second);
    return 0;
    
  
}
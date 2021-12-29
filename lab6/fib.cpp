#include<stdlib.h>
#include<stdio.h>
int main(){
    short r0;
    scanf("%hd",&r0);
    short r1=0,r2=0,r3=1;
    short r4=1023;
    short r7=0,r5=-3;
    do{
    r5=r5+1;
    if(r5>0){
        r1=r1+r1;
    }
    r7=r1+r3;
    r7=r7&r4;
    r1=r2;
    r2=r3;
    r3=r7;
    r0=r0-1;
    }while(r0>=0);
    printf("%hd",r7);
}
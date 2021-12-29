#include<stdlib.h>
#include<stdio.h>
int main(){
    short r1=0,r2=0,r3=0;
    short r4=0,r6=0;
    short r7=0,r5=0;
    short r0;
    scanf("%hd",&r0);
    r0=r0-20;
    if(r0>=0){
        do{
        r6=-128;
        r0=r0+r6;
        }while(r0>=0);
        r7=128;
        r0=r0+r7;
    }
    r0=r0+20;
    r3=1;
    r5=-3;
    r4=1023;
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
#include<stdio.h>
#include<stdlib.h>
int main(){
    short a,b,c=0;
    scanf("%hd%hd",&a,&b);
    do{
        c=c+a;
        b=b-1;
    }while(b!=0);
    printf("%hd",c);
}
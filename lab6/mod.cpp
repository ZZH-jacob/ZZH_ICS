#include<stdlib.h>
#include<stdio.h>
void A(short &r4,short &r1,short &r2,short &r3);
int main(){
    short r1,r2,r4,r3,r0;
    r1=288;
    //scanf("%hd",&r1);
    do{
    A(r4,r1,r2,r3);
    r2=r1&0x7;
    r1=r4+r2;
    r0=r1-7;
    }while(r0>0);
    r0=r1-7;
    if(r0>=0){
        r1=r1-7;
    }
    printf("%hd\n",r1);
    return 0;
}
void A(short &r4,short &r1,short &r2,short &r3){
    short r5;
    r2=1;
    r3=8;
    r4=0;
    do{
        r5=r1&r3;
        if(r5!=0){
            r4=r4+r2;
        }
        r2=r2+r2;
        r3=r3+r3;
    }while(r3!=0);
    return;
}

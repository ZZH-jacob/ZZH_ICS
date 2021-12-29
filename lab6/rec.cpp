#include<stdlib.h>
#include<stdio.h>
void A(short &r0,short &r1,short &t);
int main(){
    short t=5,r1;
    short r0=0;
    A(r0,r1,t);
    printf("%hd\n",r0);
    printf("%hd\n",r1);
    return 0;
}
void A(short &r0,short &r1,short &t){
    r0=r0+1;
    r1=t;
    r1=r1-1;
    t=r1;
    if(r1!=0){
        A(r0,r1,t);
    }
    return;
}
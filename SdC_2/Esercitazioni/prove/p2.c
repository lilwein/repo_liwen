#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

int f(int* reg, int old, int new){
    int old_reg_val = *reg;
    if(old_reg_val==old) *reg = new;
    return old_reg_val;
}

int main(int argc, char const *argv[]){
    
    int bolt=0;
    printf("bolt=%d\t--->\t",bolt);
    int res = f(&bolt, 0, 1);

    printf("res=%d\tbolt=%d\n",res,bolt);
    

    return 0;
}

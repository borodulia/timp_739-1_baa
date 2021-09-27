#include <stdio.h>

int main(){
    long int n, x, i, min = 0, flag = 0;
    if(scanf("%ld", &n) == 1){
        for(i = 1; i <= n; i++){
            if(scanf("%ld", &x) == 1){
                if(flag == 0){
                    min = x;
                    flag = 1;
                }
                else if(x < min){
                    min = x;
                }
            }
        }
        printf("%ld", min);
    }
    return 0;
}

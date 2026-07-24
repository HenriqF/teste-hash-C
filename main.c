#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char letras[] = "abcdefghijklmnopqrstuvwxyz0123456789_";
int letras_len = 37;

int transform(int self, int other, char* str, int bloco_size){
    for (int i = 0; i < bloco_size; i++){
        int m = (other >> 3) + self * (int)str[i];
        self += m;
    }
    
    return self;
}

char* hash(char* input){
    int nums[] = {67, 7001, 173, 127, 181, 193, 10037, 27487, 9281, 7583}; //top 10 numeros alearotios
    int qtd_numeros = sizeof(nums)/ sizeof(nums[0]);
    
    char from[8] = {0};
    int bloco_size = sizeof(from)/ sizeof(from[0]) -1;
    
    char padding[] = "calasewing";
    
    int offset = 0;
    for (int i = 0; i < strlen(input); i++){
        from[offset++] = input[i];
        if (offset % bloco_size == 0){
            for (int k = 0; k < 9; k++){
                nums[k] = transform(nums[k], nums[k+1], from, bloco_size);
                nums[k+1] = transform(nums[k+1], nums[k], from, bloco_size);
            }
            offset = 0;
        }
    }

    if (offset != 0){
        strncpy(padding, from, offset);
        for (int k = 0; k < qtd_numeros-1; k++){
            nums[k] = transform(nums[k], nums[k+1], padding, offset);
            nums[k+1] = transform(nums[k+1], nums[k], padding, offset);
        }
    }


    char* res = malloc((qtd_numeros+1)*sizeof(char));
    for (int i = 0; i < qtd_numeros; i++){
        res[i] = letras[abs(nums[i])%letras_len];
    }
    res[qtd_numeros] = '\0';

    return res;
}

int main(){
    char teste[] = "aura";
    printf("%s <- [%s]\n", hash(teste), teste);
    return 0;
}
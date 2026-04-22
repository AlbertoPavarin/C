#include <stdio.h>
#include <string.h>
#include <math.h>

int main(){
    char s[50];
    const char b64_table[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int carry = 0;
    int term1 = 0;
    int term2 = 0;
    int slide = 2;
    int j = 0;
    int len = 0;
    fgets(s, sizeof(s), stdin);
    s[strcspn(s, "\n")] = 0;
    
    printf("%d\n", strlen(s)*sizeof(char));
    len = strlen(s);
    int dimbased = len*4/3;
    char based[dimbased]; // spazio calcolato con il rapporto 4/3 ---> 50*4/3
    carry = len % 3;
    
    if (carry == 0) {
        for (int i = 0; i < len;){
            char b0 = s[i++];
            char b1 = s[i++];
            char b2 = s[i++];
            based[j++] = b64_table[(b0 >> 2)];
            based[j++] = b64_table[((b0 & 3)<<4)|(b1>>4)];
            based[j++] = b64_table[((b1 & 15)<<2)|(b2>>6)];
            based[j++] = b64_table[b2 & 63];
        }
    }

    for (int i = 0; i < dimbased; i++)
        printf("%c ", based[i]);
    
    printf("\n");
    return 0;
}

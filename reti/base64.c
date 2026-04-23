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
    
    len = strlen(s);
    carry = len % 3;    
    int dimbased = (carry == 0) ? len*4/3 :  len*4/3+(4-carry);
    char based[dimbased]; // spazio calcolato con il rapporto 4/3 e un appropriato padding
    for (int i = 0; i < len;) {
        char b0 = s[i++];
        char b1 = (i < len) ? s[i++] : 0;
        char b2 = (i < len) ? s[i++] : 0;
        based[j++] = b64_table[(b0 >> 2)];
        based[j++] = b64_table[((b0 & 3)<<4)|(b1>>4)];
        based[j++] = (b1 == 0) ? '=' : b64_table[((b1 & 15)<<2)|(b2>>6)];
        based[j++] = (b2 == 0) ? '=' : b64_table[b2 & 63];
    }

    for (int i = 0; i < dimbased; i++)
        printf("%c", based[i]);
    
    printf("\n");
    return 0;
}

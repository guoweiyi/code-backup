#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void swap(unsigned char *a, unsigned char *b) {
    unsigned char t = *a;
    *a = *b;
    *b = t;
}

void key_schedule(unsigned char s[256], unsigned char key[], int key_length) {
    int i,j,t;
    unsigned char tmp[256];

    memset(tmp, 0, 256);
    for (i = 0; i < 256; i++) {
        s[i] = i;
        tmp[i] = key[i % key_length];
    }

    j = t = 0;
    for (i = 0; i < 256; i++) {
        t = (t + s[i] + tmp[i]) % 256;
        swap(&s[i], &s[t]);
    }
}

void rc4(unsigned char s[256], unsigned char *data, int data_length) {
    int i, j, t, k;
    unsigned char tmp;

    i = j = 0;
    for (k = 0; k < data_length; k++) {
        i = (i + 1) % 256;
        j = (j + s[i]) % 256;
        swap(&s[i], &s[j]);
        
        t = (s[i] + s[j]) % 256;
        tmp = s[t]; // 生成密钥流字节
        
        data[k] ^= tmp; // 异或解密
    }
}

void rc4_decrypt(unsigned char *data, int data_length, unsigned char key[], int key_length) {
    unsigned char s[256];
    key_schedule(s, key, key_length);
    rc4(s, data, data_length); 
}

int main() {
    // 1. 从反编译代码中提取的 Key
    unsigned char key[] = "12345678abcdefghijklmnopqrspxyz";
    
    // 2. 从 byte_14013B000 提取的硬编码密文
    unsigned char cipher_data[] = {
        0x9E, 0xE7, 0x30, 0x5F, 0xA7, 0x01, 0xA6, 0x53, 0x59, 0x1B, 0x0A,
        0x20, 0xF1, 0x73, 0xD1, 0x0E, 0xAB, 0x09, 0x84, 0x0E, 0x8D, 0x2B
    };

    int data_length = sizeof(cipher_data);
    int key_length = strlen((const char *)key);

    printf("原始硬编码数据提取成功，长度: %d\n", data_length);

    for (int i = 0; i < data_length; i++) {
        cipher_data[i] ^= 0x22;
    }

    rc4_decrypt(cipher_data, data_length, key, key_length);

    char flag[100] = {0};
    memcpy(flag, cipher_data, data_length);
    
    printf("Flag: %s\n", flag);

    return 0;
}
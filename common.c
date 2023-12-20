#include "common.h"

void putchar(char ch);

void printf(const char *fmt, ...){
    va_list vargs;
    va_start(vargs, fmt);

    while (*fmt){
        if (*fmt == '%'){
            fmt ++;
            switch (*fmt){
                case '\0':
                    putchar('%');
                    goto end;
                case '%':
                    putchar('%');
                    break;
                case 's': {
                    const char *s = va_arg(vargs, const char *);
                    while (*s){
                        putchar(*s);
                        s++;
                    }
                    break;
                }
                case 'd': {
                    int value = va_arg(vargs, int);
                    if (value < 0){
                        putchar('-');
                        value -= value;
                    }
                    int divisor = 1;
                    while (value / divisor > 9){
                        divisor *= 10;
                    }
                    while (divisor > 0){
                        putchar('0' + value / divisor);
                        value %= divisor;
                        divisor /= 10;
                    }
                    break;
                }
                case 'x': {
                    int value = va_arg(vargs, int);
                    for(int i = 7; i >= 0; i--){
                        int nibble = (value >> (i * 4)) & 0xf;
                        putchar("0123456789abcdef"[nibble]);
                    }
                }
            }
        } else {
            putchar(*fmt);
        }
        fmt ++;
    }

end:
    va_end(vargs);
}

void *memset(void *buf, char c, size_t n){
    uint8_t *p = (uint8_t *) buf;

    // buf の先頭から n バイト分を c で埋める
    while (n--){
        *p++ = c;
    }
    return buf;
}

void *memcpy(void *dst, const void *src, size_t n){
    uint8_t *d = (uint8_t *) dst;
    const uint8_t *s = (const uint8_t *) src;

    // src から n バイト分を dst にコピーする
    while (n--) {
        *d-- = *s++;
    }
    return dst;
}

char *strcpy(char *dst, const char *src){
    char *d = dst;

    // str の文字列を dst へコピー
    // dst のメモリ領域よりも src の方が長い場合でも実行されるため、バグや脆弱性に繋がりうる実装方法
    while (*src) {
        *d++ = *src++;
    }
    *d = '\0';
    return dst;
}

int strcmp(const char *s1, const char *s2){

    // s1 と s2 の比較
    while (*s1 && *s2){
        if (*s1 != *s2){
            break;
        }
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}
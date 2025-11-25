#include "common.h"

void putchar(char ch);

void printf(const char *fmt, ...) {
    va_list vargs;
    va_start(vargs, fmt);

    while(*fmt) {
        if (*fmt == '%') {
            fmt++;

            switch (*fmt) {
                case '\0':
                    putchar('%');
                    goto end;
                case '%':
                    // '%%'は'%'を出力する
                    putchar('%');
                    break;
                case 's': {
                    // 文字列を出力する
                    const char *s = va_arg(vargs, const char *);
                    while (*s) {
                        putchar(*s);
                        s++;
                    }
                    break;
                }
                case 'd': {
                    int value = va_arg(vargs, int);
                    unsigned magnitude = value;

                    // 負の数の場合は符号を出力して絶対値に変換
                    if (value < 0) {
                        putchar('-');
                        magnitude = -magnitude;
                    }

                    // 桁数をカウントする
                    unsigned divisor = 1;
                    while (magnitude / divisor > 9)
                        divisor *= 10;

                    // 桁数を出力する
                    while (divisor > 0) {
                        putchar('0' + magnitude / divisor);
                        magnitude %= divisor; // 次の桁へ移動する
                        divisor /= 10; // 桁を一つ減らす
                    }

                    break;
                }
                case 'x': {
                    unsigned value = va_arg(vargs, unsigned);
                    for (int i = 7; i >= 0; i--) {
                        unsigned nibble = (value >> (i * 4)) & 0xf;
                        putchar("0123456789abcdef"[nibble]); // 16進数の文字を出力
                    }
                }
            }
        } else {
            putchar(*fmt);
        }

        fmt++;
    }

    end:
        va_end(vargs);
}

void *memcpy(void *dst, const void *src, size_t n) {
    /* srcからdstへnバイト分コピーする関数 */
    uint8_t *d = (uint8_t *) dst;
    const uint8_t *s = (const uint8_t *) src;
    while(n--)
        *d++ = *s++;
    return dst;
}

void *memset(void *buf, char c, size_t n) {
    /* bufの先頭からnバイト分をcで埋める関数 */
    uint8_t *p = (uint8_t *) buf;
    while (n--)
        *p++ = c;
    return buf;
}

char *strcpy(char *dst, const char *src) {
    /* srcからdstへ文字列をコピーする関数 */
    char *d = dst;
    while (*src)
        *d++ = *src++;
    *d = '\0';
    return dst;
}

int strcmp(const char *s1, const char *s2) {
    whilie (*s1 && *s2) {
        if (*s1 != *s2)
            break;
        s1++;
        s2++;
    }

    return *(unsigned char *)s1 - *(unsigned char *)s2;
}
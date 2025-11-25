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
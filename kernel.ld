/* エントリポイント(プログラムの開始地点)の指定。 */
ENTRY(kernel_main)

SECTIONS {
    /* ベースアドレスの設定。 */
    . = 0x80200000;

    /* コード領域。 */
    .text :{
        KEEP(*(.text.boot));
        *(.text .text.*);
    }

    /* 定数データ領域。読み取り専用。 */
    .rodata : ALIGN(4) {
        *(.rodata .rodata.*);
    }

    /* 書き換え可能データ領域。 */
    .data : ALIGN(4) {
        *(.data .data.*);
    }

    /* 読み書きデータ領域。.dataと異なり、初期値がゼロの変数を配置。 */
    .bss : ALIGN(4) {
        __bss = .;
        *(.bss .bss.* .sbss .sbss.*);
        __bss_end = .;
    }

    . = ALIGN(4);
    . += 128 * 1024; /* 128KB */
    __stack_top = .;
}
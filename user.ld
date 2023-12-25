/* アプリケーションの実行ファイルを配置する場所を定義 */
ENTRY(start)

SECTIONS {
    /* カーネルアドレスと被らない領域に配置 */
    . = 0x1000000;

    .text :{
        KEEP(*(.text.start));
        *(.text .text.*);
    }

    .rodata : ALIGN(4) {
        *(.rodata .rodata.*);
    }

    .data : ALIGN(4) {
        *(.data .data.*);
    }

    .bss : ALIGN(4) {
        *(.bss .bss.* .sbss .sbss.*);

        . = ALIGN(16); /* https://github.com/nuta/operating-system-in-1000-lines/pull/23 */
        . += 64 * 1024; /* 64KB */
        __stack_top = .;

       /* アプリケーションの末尾が 0x1800000 を超える場合、リンク処理を失敗させる */
       ASSERT(. < 0x1800000, "too large executable");
    }
}
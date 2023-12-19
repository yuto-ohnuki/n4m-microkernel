typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef uint32_t size_t;

// リンカスクリプト内で定義されている各シンボル
extern char __bss[], __bss_end[], __stack_top[];

void *memset(void *buf, char c, size_t n){
    uint8_t *p = (uint8_t *) buf;
    while (n--)
        *p++ = c;
    return buf;
}

void kernel_main(void) {
    memset(__bss, 0, (size_t) __bss_end - (size_t) __bss);

    for (;;);
}

// 最初に起動する関数。
// リンカスクリプトで用意したスタック領域の末尾アドレスをスタックポインタ (sp) に設定し、
// kernel_main関数へジャンプ
__attribute__((section(".text.boot")))
__attribute__((naked))
void boot(void) {
    __asm__ __volatile__(
        "mv sp, %[stack_top]\n"
        "j kernel_main\n"
        :
        : [stack_top] "r" (__stack_top)
    );
}
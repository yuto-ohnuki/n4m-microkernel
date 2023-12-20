#pragma once

// SBI の処理結果を返すための構造体
struct sbiret {
    long error;
    long value;
};

// kernel panic
// **_VA_ARGS__: コンパイラ拡張機能。## により、可変長引数が空の時に直前の , を削除
#define PANIC(fmt, ...)                                                        \
    do {                                                                       \
        printf("PANIC: %s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__);  \
        while (1) {}                                                           \
    } while (0)
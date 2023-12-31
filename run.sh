#!/bin/bash
set -xue

# QEMU　file path
QEMU=qemu-system-riscv32

# clang path
CC=/opt/homebrew/opt/llvm/bin/clang

# Args:
#   -std=c11: C11 の使用
#   -O2: 最適化の有効化・効率の良い機械語の生成
#   -g3: デバッグ情報の出力
#   -Wall, -Wextra: 警告を有効
#   --target=riscv32: 32 bit RISC-V 用にコンパイル
#   -ffreestanding: ホスト環境の標準ライブラリを使用しない
#   -nostdlib: 標準ライブラリをリンクしない
CFLAGS="-std=c11 -O2 -g3 -Wall -Wextra --target=riscv32 -ffreestanding -nostdlib"

# convert .elf -> raw binary
OBJCOPY=/opt/homebrew/opt/llvm/bin/llvm-objcopy

# shell build
$CC $CFLAGS -Wl,-Tuser.ld -Wl,-Map=shell.map -o shell.elf shell.c user.c common.c
$OBJCOPY --set-section-flags .bss=alloc,contents -O binary shell.elf shell.bin
$OBJCOPY -Ibinary -Oelf32-littleriscv shell.bin shell.bin.o
# カーネルのビルド
# Args:
#   -Wl,-Tkernel.ld: リンカスクリプトを指定する
#   -Wl,-Map=kernel.map: マップファイルを出力する
$CC $CFLAGS -Wl,-Tkernel.ld -Wl,-Map=kernel.map -o kernel.elf \
  kernel.c common.c

# QEMU の起動
# Args:
#   -machine virt: virt マシンとして起動
#   -bios default: デフォルトの BIOS (OpenSBI) を使用
#   -nographic: QEMU をウィンドウなしで起動
#   -serial mon:stdio: QEMU の標準入出力を仮想マシンのシリアルポートに接続
#   --no-reboot: クラッシュ時には、再起動せずに停止
$QEMU -machine virt -bios default -nographic -serial mon:stdio --no-reboot \
  -kernel kernel.c common.c shell.bin.o

# /opt/homebrew/Cellar/llvm/17.0.6/bin
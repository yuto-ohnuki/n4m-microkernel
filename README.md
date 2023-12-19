# Link
https://operating-system-in-1000-lines.vercel.app/ja/welcome

# Overview
```
 ├── disk/     - ファイルシステムの中身
 ├── common.c  - カーネル・ユーザー共通ライブラリ: printf関数やmemset関数など
 ├── common.h  - カーネル・ユーザー共通ライブラリ: 各種構造体・定数などの定義
 ├── kernel.c  - カーネル: プロセス管理、システムコール、デバイスドライバ、ファイルシステム
 ├── kernel.h  - カーネル: 各種構造体・定数などの定義
 ├── kernel.ld - カーネル: リンカスクリプト (メモリレイアウトの定義)
 ├── shell.c   - コマンドラインシェル
 ├── user.c    - ユーザー用ライブラリ: システムコールの呼び出し関数など
 ├── user.h    - ユーザー用ライブラリ: 各種構造体・定数などの定義
 ├── user.ld   - ユーザー: リンカスクリプト (メモリレイアウトの定義)
 └── run.sh    - ビルドスクリプト
```
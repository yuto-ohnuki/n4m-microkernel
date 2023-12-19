#pragma once

// SBI の処理結果を返すための構造体
struct sbiret {
  long error;
  long value;
};
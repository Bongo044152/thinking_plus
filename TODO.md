# TODO

## CRT
- 實作 CRT：將 `.bss` 清零，將 `.data` 從 flash 複製到 DTIM
- 修 linker script：補 `.data` 的 `AT()`，expose `__bss_start`/`__bss_end`、`__data_start`/`__data_end`/`__data_load`
- 在 `entry.S` 的 `call start` 之前接上 CRT 的初始化邏輯

## 標頭檔整理
- 目前各模組高度耦合（例如 `uart.h` 拉進了 `gpio.h`、`trap.h`）
- 梳理 include 依賴，讓標頭檔反映實際耦合關係
- 考慮將 MMIO 暫存器定義與函式宣告分開

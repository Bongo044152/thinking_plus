# SparkFun RED-V Thing Plus - SiFive RISC-V FE310 SoC

基於學習目的的裸機韌體專案，目標是在不依賴 OS 或 stdlib 的情況下驅動 FE310 的基本功能。
main 分支持續開發中，尚未完成。

## Memory Layout

![memory layout](images/memory_layout.png)

## Build

**環境需求**

- `riscv32-unknown-elf-gcc`（支援 rv32imac_zicsr）

```sh
make          # 編譯，產生 think_plus.hex
make DEBUG=yes  # 帶 -g 的 debug build
make clean
make format   # clang-format（需安裝）
```

## Reference

### SparkFun RED-V Thing Plus
- Datasheet: https://sifive.cdn.prismic.io/sifive/034760b5-ac6a-4b1c-911c-f4148bb2c4a5_fe310-g002-v1p5.pdf
- sparkfun Software Development Guide: https://learn.sparkfun.com/tutorials/red-v-development-guide
- sparkfun shopping: https://www.sparkfun.com/sparkfun-red-v-thing-plus-sifive-risc-v-fe310-soc.html#content-overview

### Riscv GCC
- https://gcc.gnu.org/onlinedocs/gcc/RISC-V-Options.html

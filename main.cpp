//
// Simple C64 program with LLVM-MOS using the IRQ vector
// to show a white rasterbar.
// (c) 2023 by Volker Schwaberow <volker@schwaberow.de>
//

#include <cstdint>
#include <cstdio>

void myirq()
{

    asm volatile(
        "lda #$01\n\t"
        "sta $d019\n\t"
        "lda #$38\n\t"
        "wait2:\n\t"
        "cmp $d012\n\t"
        "bne wait2\n\t"
        "ldx #$0b\n\t"
        "myloop:\n\t"
        "dex\n\t"
        "bne myloop\n\t"
        "lda #$01\n\t"
        "sta $d020\n\t"
        "sta $d021\n\t"
        "ldx #$0a\n\t"
        "myloop2:\n\t"
        "dex\n\t"
        "bne myloop2\n\t"
        "lda #$00\n\t"
        "sta $d020\n\t"
        "sta $d021\n\t"
        "jmp $ea81\n\t");
}

int main()
{

    uint8_t lowirq = (uint8_t)((uint16_t)myirq & 0x00ff);
    uint8_t highirq = (uint8_t)(((uint16_t)myirq & 0xff00) >> 8);

    std::puts("HELLO C64");

    asm volatile(
        "sei\n\t"
        "lda #0\n\t"
        "sta $d020\n\t"
        "sta $d021\n\t"
        "jsr $ff84\n\t"
        "jsr $ff81\n\t"
        "lda #$01\n\t"
        "sta $d01a\n\t"
        "lda #$7f\n\t"
        "sta $dc0d\n\t"
        "lda %0\n\t"
        "ldx %1\n\t"
        "sta $0314\n\t"
        "stx $0315\n\t"
        "cli\n\t"
        "wait:\n\t"
        "jmp wait\n\t"
        :
        : "r"(lowirq), "r"(highirq)
        : "memory");
    return 0;
}

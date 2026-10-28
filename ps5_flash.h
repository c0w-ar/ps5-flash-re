#include <stdint.h>

typedef struct _flash_header {
    char        magic[0x20];            // "SONY COMPUTER ENTERTAINMENT INC."
    uint32_t    version;
    uint32_t    LBA_A_start;
    uint32_t    LBA_B_start;
    uint32_t    A_size_sectors;         // 1
    uint32_t    B_size_sectors;         // 1
    uint32_t    bank_selector;          // default (0x80 >> 7) -> Sector B
    uint32_t    selector_size_sectors;  // 1
    uint32_t    unk;
} flash_header;

typedef struct _MBR_entry {
    uint32_t    LBA_start;
    uint32_t    size_sectors;
    uint32_t    type;                   // 0x20 (32) or 0x29 (41)
    uint32_t    flags;                  // if 1 --> 'b'
    uint32_t    unk;
} MBR_entry;

typedef struct _flash_MBR {
    char        magic[0x20];            // "Sony Computer Entertainment Inc."
    uint32_t    n_entries;
    uint32_t    total_sectors;
    uint32_t    unk1;
    uint32_t    unk2;
    uint32_t    unk3;
    uint32_t    unk4;
    uint32_t    unk5;
    uint32_t    unk6;
    MBR_entry   entries[16]    
} flash_MBR;

typedef struct _PS5_flash {
    uint8_t     blobs[0x120000];        // Main section for firmware
    /**************************************************/
    /*                 Default Layout                 */
    /**************************************************/
    /* 0x000000  flash_header                         */
    /* 0x001000  bank_switch                          */
    /* 0x002000  MBR_A ( )                            */
    /* 0x003000  MBR_B (*)                            */
    /* 0x004000  sector_32   - Salina EMC FW          */
    /* 0x082000  sector_32_b - Salina EMC FW          */
    /* 0x100000  sector_41   - USB-C FW - Not present */
    /* 0x110000  sector_41_b - USB-C FW               */
    /**************************************************/
    uint8_t     unk1[0xA4020];
    uint8_t     eth_mac1[6];            // 1C4020
    uint8_t     unk2[0x2FEB];
    uint8_t     disc_or_digital;        // 1C7011 - 02 Disc - 03 Digital
    uint8_t     unk3[0x1EE];
    uint8_t     mb_serial[0x10];        // 1C7200
    uint8_t     console_serial[0x20];   // 1C7210
    uint8_t     console_model[0x20];    // 1C7230
    uint8_t     other_serial[0x10];     // 1C7250
    uint8_t     unk4[0x160];
    uint8_t     wifi_mac1[6];           // 1C73C0
    uint8_t     wifi_mac2[6];           // 1C73C6
    uint8_t     wifi_mac3[6];           // 1C73CC
} PS5_flash;
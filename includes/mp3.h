#ifndef MP3_H
#define MP3_H

#include <stdio.h>
#include <stdint.h>

/* ID3 header structure */
typedef struct
{
    char tag[3];
    uint8_t version;
    uint8_t revision;
    uint8_t flags;
    uint32_t size;
} ID3Header;

/* Frame header structure */
typedef struct
{
    char id[5];
    uint32_t size;
    uint16_t flags;
} FrameHeader;

/* header functions */
int read_id3_header(FILE *fp, ID3Header *header);

/* frame functions */
void parse_frames(FILE *fp, uint32_t tag_size);

void read_id3v1(FILE *fp);

/* utils */
uint32_t syncsafe_to_int(uint8_t bytes[4]);
uint32_t big_endian_to_int(uint8_t bytes[4]);

#endif
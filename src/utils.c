#include "mp3.h"
#include <string.h>

/* Convert syncsafe integer to normal integer */
uint32_t syncsafe_to_int(uint8_t bytes[4])
{
    uint32_t value = 0;

    value |= (bytes[0] & 0x7F) << 21;
    value |= (bytes[1] & 0x7F) << 14;
    value |= (bytes[2] & 0x7F) << 7;
    value |= (bytes[3] & 0x7F);

    return value;
}

/* Convert big endian bytes to integer */
uint32_t big_endian_to_int(uint8_t bytes[4])
{
    return (bytes[0] << 24) |
           (bytes[1] << 16) |
           (bytes[2] << 8) |
           (bytes[3]);
}

void read_id3v1(FILE *fp)
{
    char buffer[128];

    fseek(fp, -128, SEEK_END);

    fread(buffer, 1, 128, fp);

    if (strncmp(buffer, "TAG", 3) != 0)
    {
        printf("No ID3v1 tag found\n");
        return;
    }

    printf("\n------ ID3v1 METADATA ------\n");

    char title[31], artist[31], album[31], year[5];

    memcpy(title, buffer + 3, 30);
    memcpy(artist, buffer + 33, 30);
    memcpy(album, buffer + 63, 30);
    memcpy(year, buffer + 93, 4);

    title[30] = '\0';
    artist[30] = '\0';
    album[30] = '\0';
    year[4] = '\0';

    printf("%-8s : %s\n", "Title", title);
    printf("%-8s : %s\n", "Artist", artist);
    printf("%-8s : %s\n", "Album", album);
    printf("%-8s : %s\n", "Year", year);
}
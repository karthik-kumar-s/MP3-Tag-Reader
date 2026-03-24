#include "mp3.h"

/* Read ID3 header */
int read_id3_header(FILE *fp, ID3Header *header)
{
    uint8_t size_bytes[4];

    if (fread(header->tag, 1, 3, fp) != 3)
        return -1;

    if (header->tag[0] != 'I' ||
        header->tag[1] != 'D' ||
        header->tag[2] != '3')
        return -1;

    fread(&header->version, 1, 1, fp);
    fread(&header->revision, 1, 1, fp);
    fread(&header->flags, 1, 1, fp);

    fread(size_bytes, 1, 4, fp);
    header->size = syncsafe_to_int(size_bytes);

    return 0;
}
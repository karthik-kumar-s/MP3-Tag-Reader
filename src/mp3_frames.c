#include "mp3.h"
#include <string.h>
#include <stdlib.h>

// Parse all frames inside tag
void parse_frames(FILE *fp, uint32_t tag_size)
{
    uint32_t bytes_read = 0;

    while (bytes_read < tag_size)
    {
        FrameHeader frame;
        uint8_t size_bytes[4];

        // read frame id
        if (fread(frame.id, 1, 4, fp) != 4)
            break;

        frame.id[4] = '\0';

        // padding reached
        if (frame.id[0] == 0)
            break;

        // read frame size
        if (fread(size_bytes, 1, 4, fp) != 4)
            break;

        frame.size = big_endian_to_int(size_bytes);

        // read flags
        if (fread(&frame.flags, 1, 2, fp) != 2)
            break;

        bytes_read += 10;

        // safe validation
        if (frame.size == 0 || frame.size > tag_size)
            break;

        char *data = malloc(frame.size + 1);
        if (!data)
            return;

        if (fread(data, 1, frame.size, fp) != frame.size)
        {
            free(data);
            break;
        }

        data[frame.size] = '\0';
        bytes_read += frame.size;

        char *text = data + 1;

        if (strcmp(frame.id, "TIT2") == 0)
            printf("%-8s : %s\n", "Title", text);

        else if (strcmp(frame.id, "TPE1") == 0)
            printf("%-8s : %s\n", "Artist", text);

        else if (strcmp(frame.id, "TALB") == 0)
            printf("%-8s : %s\n", "Album", text);

        else if (strcmp(frame.id, "TYER") == 0)
            printf("%-8s : %s\n", "Year", text);

        else if (strcmp(frame.id, "APIC") == 0)
        {
            printf("%-8s : Album Art\n", "Image");
            printf("           Frame ID : %s\n", frame.id);
            printf("           Size     : %u bytes\n", frame.size);
        }

        free(data);
    }
}
#include "mp3.h"
#include <string.h>

void show_help(char *prog)
{
    printf("\n############################################\n");
    printf("MP3 TAG READER - HELP\n");
    printf("############################################\n\n");

    printf("Usage:\n");
    printf("  %s <mp3-file>\n\n", prog);

    printf("Options:\n");
    printf("  -h       Show help menu\n\n");

    printf("Features:\n");
    printf("  * Reads ID3v2.3 metadata\n");
    printf("  * Reads ID3v1 metadata\n");
    printf("  * Displays Title / Artist / Album / Year\n");
    printf("  * Shows Album Art info if present\n\n");

    printf("############################################\n\n");
}

int main(int argc, char *argv[])
{
    FILE *fp;
    ID3Header header;

    if (argc != 2)
    {
        show_help(argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-h") == 0)
    {
        show_help(argv[0]);
        return 0;
    }

    fp = fopen(argv[1], "rb");
    if (!fp)
    {
        perror("Error opening file");
        return 1;
    }

    if (read_id3_header(fp, &header) != 0)
    {
        printf("\nNo ID3v2 tag found. Trying ID3v1...\n");
        read_id3v1(fp);
        fclose(fp);
        return 0;
    }

    printf("\n############################################\n");
    printf("            MP3 TAG READER\n");
    printf("############################################\n\n");

    printf("ID3 Version : 2.%d.%d\n", header.version, header.revision);
    printf("Tag Size    : %u bytes\n\n", header.size);

    printf("--------------------------------------------\n");
    printf("METADATA INFORMATION\n");
    printf("--------------------------------------------\n");

    parse_frames(fp, header.size);

    fclose(fp);

    printf("\n############################################\n\n");

    return 0;
}
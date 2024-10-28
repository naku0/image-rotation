#include <stdlib.h>
#include "bmp.h"
#include "image.h"

enum read_status from_bmp(FILE *file, struct image *image) {
    struct bmp_header header;
    if (fread(&header, sizeof(struct bmp_header), 1, file) != 1) {
        return READ_INVALID_HEADER;
    }
    if (header.bfType != 0x4D42) {
        return READ_INVALID_SIGNATURE;
    }
    if (header.biBitCount != 24) {
        return READ_INVALID_BITS;
    }
    image->width = header.biWidth;
    image->height = header.biHeight;
    image->data = malloc(image->width * image->height * sizeof(struct pixel));
    if (image->data == NULL) {
        return READ_INVALID_HEADER;
    }
    fseek(file, header.bOffBits, SEEK_SET);
    uint32_t padding = (4 - (image->width * sizeof(struct pixel)) % 4) % 4;

    for (uint64_t y = 0; y < image->height; ++y) {
        if (fread(image->data + y * image->width, sizeof(struct pixel), image->width, file) != image->width) {
            free(image->data);
            return READ_INVALID_HEADER;
        }

        fseek(file, padding, SEEK_CUR);
    }

    return READ_OK;
}

enum write_status to_bmp(FILE *out, struct image const *img) {
    struct bmp_header header;

    header.bfType = 0x4D42;
    header.bfileSize = sizeof(struct bmp_header) + img->width * img->height * sizeof(struct pixel);
    header.bOffBits = sizeof(struct bmp_header);
    header.biSize = 40;
    header.biWidth = img->width;
    header.biHeight = img->height;
    header.biPlanes = 1;
    header.biBitCount = 24;
    header.biCompression = 0;
    header.biSizeImage = img->width * img->height * sizeof(struct pixel);
    header.biXPelsPerMeter = 2835;
    header.biYPelsPerMeter = 2835;
    header.biClrUsed = 0;
    header.biClrImportant = 0;

    if (fwrite(&header, sizeof(struct bmp_header), 1, out) != 1) {
        return WRITE_ERROR;
    }

    uint32_t padding = (4 - (img->width * sizeof(struct pixel)) % 4) % 4;

    for (uint64_t y = 0; y < img->height; ++y) {
        if (fwrite(img->data + y * img->width, sizeof(struct pixel), img->width, out) != img->width) {
            return WRITE_ERROR;
        }

        for (uint32_t p = 0; p < padding; ++p) {
            fputc(0, out);
        }
    }

    return WRITE_OK;
}
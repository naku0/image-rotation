#include "utils.h"
#include "bmp.h"
#include "transform.h"
#include <stdio.h>
#include <unistd.h>
#include "stdlib.h"

struct image load_image(const char *filename) {
    FILE *file = fopen(filename, "rb");
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working dir: %s\n", cwd);
        if (!file) {
            printf("Error: could not open input file\n");
            exit(1);
        }
    }

    struct image img;
    if (from_bmp(file, &img) != READ_OK) {
        printf("Error: failed to read BMP file\n");
        fclose(file);
        exit(1);
    }

    fclose(file);
    return img;
}

void save_image(const char *filename, struct image *img) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Error: could not open output file\n");
        exit(1);
    }

    if (to_bmp(file, img) != WRITE_OK) {
        printf("Error: failed to write BMP file\n");
        fclose(file);
        exit(1);
    }

    fclose(file);
}

struct image transform_image(struct image img) {
    return rotate_img(img);
}

struct facade create_image_facade() {
    return (struct facade){ load_image, save_image, transform_image };
}

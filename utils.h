#ifndef UTILS_H
#define UTILS_H

#include "image.h"

struct facade {
    struct image (*load_image)(const char *filename);
    void (*save_image)(const char *filename, struct image *img);
    struct image (*transform_image)(struct image img);
};

struct facade create_image_facade();

#endif

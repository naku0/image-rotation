#include <stdlib.h>
#include "image.h"

struct image create_image(uint64_t width, uint64_t height) {
    struct image image;
    image.width = width;
    image.height = height;
    image.data = malloc(width * height * sizeof(uint32_t));
    return image;
}

void free_image(struct image* image) {
    free(image->data);
    image->data = NULL;
}
#include "utils.h"
#include "image.h"
#include <stdio.h>

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Usage: %s <source-image> <transformed-image>\n", argv[0]);
        return 1;
    }

    struct facade facade = create_image_facade();

    struct image img = facade.load_image(argv[1]);
    struct image rotated_img = facade.transform_image(img);
    facade.save_image(argv[2], &rotated_img);

    free_image(&img);
    free_image(&rotated_img);

    return 0;
}

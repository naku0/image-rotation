#include "transform.h"

struct image rotate_img(const struct image src){
    struct image res = create_image(src.width, src.height);
    if (res.data == NULL){
        struct image empty_image = {0};
        return empty_image;
    }
    for(uint64_t i = 0; i < src.height; i++){
        for(uint64_t j = 0; j < src.width; j++){
            res.data[j * res.width + (src.height - i - 1)] = src.data[i * src.width + j];
        }
    }
    return res;
}

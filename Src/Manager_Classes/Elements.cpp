#include "Elements.hpp"

Rectangle Bases::getImageSrc(Vector2 srcPos) {

    imageSrc.x = imageSrc.width * srcPos.x;
    imageSrc.y = imageSrc.height * srcPos.y;

    return imageSrc;
}

void Bases::setImage(const Texture2D &image) {

    imageSrc.width = (image.width / 2.0f);
    imageSrc.height = (image.height / 3.0f);
}

Rectangle Bases::imageSrc;
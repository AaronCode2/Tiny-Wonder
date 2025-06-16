#include "Elements.hpp"

Rectangle BasesImage::getImageSrc(const Vector2 srcPos) {

    imageSrc.x = imageSrc.width * srcPos.x;
    imageSrc.y = imageSrc.height * srcPos.y;

    return imageSrc;
}

void BasesImage::setImage(const Texture2D &image) {

    imageSrc.width = (image.width / 2.0f);
    imageSrc.height = (image.height / 3.0f);
}

Rectangle BasesImage::imageSrc;

Rectangle ButtonImage::getImageSrc(const Vector2 srcPos) {

    imageSrc.x = imageSrc.width * srcPos.x;
    imageSrc.y = imageSrc.height * srcPos.y;

    return imageSrc;
}

void ButtonImage::setImage(const Texture2D &image) {

    imageSrc.width = (image.width / 3.0f);
    imageSrc.height = (image.height / 3.0f);
}

Rectangle ButtonImage::imageSrc;
#include "ImageItem.h"

ImageItem::ImageItem(): m_image(nullptr)
{
    connect(this, &ImageItem::imageChanged, this, [&]{update();});
}

void ImageItem::setImage(ImageWrap *image)
{
    if(!m_image || image->getImage() != m_image->getImage())
    {
        m_image = image;
        emit imageChanged();
    }
}

ImageWrap* ImageItem::getImage() const
{
    return m_image;
}

void ImageItem::paint(QPainter * painter)
{
    if(!m_image)
        return;

    auto rect = boundingRect();
    painter->drawImage(rect, *m_image->getImage(), m_image->getImage()->rect());
}

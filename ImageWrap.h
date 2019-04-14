#pragma once

#include <QObject>
#include <QImage>
#include "IBinaryImage.h"

class ImageWrap : public QObject
{
    Q_OBJECT
public:
    explicit ImageWrap(QImage&& image,QObject* parent = nullptr) : QObject(parent),
        m_image(image)
    {

    }
    explicit ImageWrap(QObject* parent = nullptr) : QObject(parent)
    {

    }

    static std::unique_ptr<ImageWrap> fromBinaryImage(const IBinaryImage& image)
    {
        QImage q_image(image.GetWidth(), image.GetHeight(), QImage::Format::Format_RGB32);
        for (int j = 0; j < image.GetHeight(); j++)
        {
            for (int i = 0; i < image.GetWidth(); i++)
            {
                q_image.setPixelColor(i, j, image.GetPixel(i, j) ? QColor("black") : QColor("white"));
            }
        }
        return std::make_unique<ImageWrap>(std::move(q_image));
    }

    QImage* getImage() { return &m_image; }
    void setImage(QImage* image) { m_image = *image; }

private:
    QImage m_image;
};

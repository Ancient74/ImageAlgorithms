#pragma once
#include <QQuickPaintedItem>
#include <QImage>
#include <QPainter>
#include "ImageWrap.h"
class ImageItem : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(ImageWrap* image READ getImage WRITE setImage NOTIFY imageChanged)
public:
    ImageItem();

    ImageWrap* getImage() const;
    void setImage(ImageWrap*);

    void paint(QPainter*) override;

signals:
    void imageChanged();

private:
    ImageWrap* m_image;
};

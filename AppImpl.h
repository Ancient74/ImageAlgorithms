#pragma once
#include <QObject>
#include <ImageWrap.h>
class AppImpl : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isImageReady READ getIsImageReady NOTIFY imageChanged)
    Q_PROPERTY(bool isProcessedImageReady READ getIsImageReady NOTIFY imageProcessed)
    Q_PROPERTY(ImageWrap* image READ getImage NOTIFY imageChanged)
    Q_PROPERTY(ImageWrap* processedImage READ getProcessedImage NOTIFY imageProcessed)

public:
    explicit AppImpl(QObject *parent = nullptr);

    ImageWrap* getImage() const;
    ImageWrap* getProcessedImage() const;

    bool getIsImageReady() const { return m_image != nullptr; }
    bool getIsProcessedImageReady() const { return m_image_processed != nullptr; }

signals:
    void imageChanged();
    void imageProcessed();

public slots:
    void selectImage();
    void onImageChanged();

private:
    std::unique_ptr<ImageWrap> m_image;
    std::unique_ptr<ImageWrap> m_image_processed;
};

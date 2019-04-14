#include "AppImpl.h"
#include <QFileDialog>
#include"QtBrightImage.h"
#include "BinaryImage.h"
#include "OtsuTreshHoldAlgorithm.h"

AppImpl::AppImpl(QObject *parent) : QObject(parent),
    m_image(nullptr),
    m_image_processed(nullptr)
{
    connect(this, &AppImpl::imageChanged, this, &AppImpl::onImageChanged);
}

void AppImpl::onImageChanged()
{
    auto bright = QtBrightImage::FromQtImage(*m_image->getImage());
    OtsuTreshHoldAlgorithm alg;
    auto binary = BinaryImage::FromBrightImage(*bright, alg);
    m_image_processed = ImageWrap::fromBinaryImage(*binary);
    emit imageProcessed();
}

void AppImpl::selectImage()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::FileMode::ExistingFile);
    dialog.setNameFilter(tr("Images (*.png *.jpg *.bmp)"));

    if(dialog.exec())
    {
        QStringList file_image = dialog.selectedFiles();
        m_image = std::make_unique<ImageWrap>(QImage(file_image.first()));
        emit imageChanged();
    }
}

ImageWrap* AppImpl::getImage() const
{
    return m_image.get();
}

ImageWrap* AppImpl::getProcessedImage() const
{
    return m_image_processed.get();
}


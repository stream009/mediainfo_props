#ifndef MEDIAINFO_WIDGET_123B9A99_E168_497B_958F_C4C5C2DC342F
#define MEDIAINFO_WIDGET_123B9A99_E168_497B_958F_C4C5C2DC342F

#include <memory>

#include <QtWidgets/QTextEdit>

#include <MediaInfoDLL/MediaInfoDLL.h>

class MediaInfo
{
public:
    MediaInfo(const std::string &filename)
    {
        if (m_mediaInfo.Open(filename) == 0) {
            throw std::runtime_error {
                std::string { "MediaInfo::Open " } + filename };
        }
    }

    ~MediaInfo() { m_mediaInfo.Close(); }

    std::string str() const
    {
        const auto &result =
            const_cast<MediaInfoDLL::MediaInfo&>(m_mediaInfo).Inform();
        if (result.empty()) {
            throw std::runtime_error {
                "MediaInfo::Inform"
            };
        }
        return result;
    }

private:
    MediaInfoDLL::MediaInfo m_mediaInfo;
};

class MediaInfoWidget : public QTextEdit
{
public:
    MediaInfoWidget(const char *filename)
    {
        this->setStyleSheet("font: 9pt \"Monospace\";");
        this->setReadOnly(true);

        MediaInfo mediaInfo { filename };

        m_document.reset(new QTextDocument {
            QString::fromStdString(mediaInfo.str())
        });
        if (!m_document) {
            throw std::runtime_error { "QTextDocument" };
        }

        this->setDocument(m_document.get());
    }

private:
    std::unique_ptr<QTextDocument> m_document;
};

#endif // MEDIAINFO_WIDGET_123B9A99_E168_497B_958F_C4C5C2DC342F

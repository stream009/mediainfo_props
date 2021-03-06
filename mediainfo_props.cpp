#include "mediainfo_props.hpp"

#include "mediainfo_widget.hpp"

#include <kdemacros.h>
#include <KDebug>
#include <KLocalizedString>
#include <KPluginFactory>
#include <KPluginLoader>

K_PLUGIN_FACTORY(MediaInfoPropsPluginFactory,
                 registerPlugin<MediaInfoPropsPlugin>();)
K_EXPORT_PLUGIN(MediaInfoPropsPluginFactory("mediainfo props"))

MediaInfoPropsPlugin::
MediaInfoPropsPlugin(QObject *parent, const QList<QVariant> &)
    : KPropertiesDialogPlugin { static_cast<KPropertiesDialog*>(parent) }
{
    try {
        const auto &items = this->properties->items();
        if (items.size() != 1) {
            return;
        }
        const auto &item = items.at(0);
        if (!item.isLocalFile()) {
            return;
        }

        const auto &path = item.localPath().toLocal8Bit();
        auto * const edit = new MediaInfoWidget { path.constData() };

        this->properties->addPage(edit, i18nc("@title:tab", "MediaInfo"));
    }
    catch (const std::exception &e) {
        kDebug() << "Exception: " << e.what();
    }
    catch (...) {
        kDebug() << "Unknown exception has caught.";
    }
}

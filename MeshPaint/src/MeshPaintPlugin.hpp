#ifndef MESHPAINTPLUGIN_HPP_
#define MESHPAINTPLUGIN_HPP_

#include <Core/CoreMacros.hpp>
#include <Core/Utils/Color.hpp>

#include <PluginBase/RadiumPluginInterface.hpp>
#include <QAction>
#include <QColor>
#include <QObject>
#include <QtPlugin>

#include <UI/MeshPaintUI.h>

#include <MeshPaintPluginMacros.hpp>

namespace Ra {
namespace Engine {
class RadiumEngine;
class Entity;
} // namespace Engine
} // namespace Ra

namespace MeshPaintPlugin {
class MeshPaintComponent;

// Due to an ambigous name while compiling with Clang, must differentiate plugin class from plugin
// namespace
class MeshPaintPluginC : public QObject, Ra::Plugins::RadiumPluginInterface
{
    Q_OBJECT
    Q_RADIUM_PLUGIN_METADATA
    Q_INTERFACES( Ra::Plugins::RadiumPluginInterface )

  public:
    MeshPaintPluginC();
    ~MeshPaintPluginC();

    void registerPlugin( const Ra::Plugins::Context& context ) override;

    bool doAddWidget( QString& name ) override;
    QWidget* getWidget() override;

    bool doAddMenu() override;
    QMenu* getMenu() override;

    bool doAddAction( int& nb ) override;
    QAction* getAction( int id ) override;

  signals:
    void askForUpdate();

  public slots:
    void onCurrentChanged( const QModelIndex& current, const QModelIndex& prev );
    void activePaintColor( bool on );
    void changePaintColor( const QColor& color );
    void bakeToDiffuse();

  private:
    MeshPaintUI* m_widget;

    Ra::GuiBase::SelectionManager* m_selectionManager;
    Ra::Gui::PickingManager* m_PickingManager;

    class MeshPaintSystem* m_system;

    Ra::Core::Utils::Color m_paintColor;
    bool m_isPainting;
};

} // namespace MeshPaintPlugin

#endif // MESHPAINTPLUGIN_HPP_

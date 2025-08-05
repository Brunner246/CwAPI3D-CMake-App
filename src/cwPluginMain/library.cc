//
// Created by MichaelBrunner on 28/07/2025.
//

#include <iostream>
#include <memory>
#include <QMainWindow>
#include <cwapi3d/CwAPI3D.h>

#include "app/CommandProcessor.hh"
#include "presentation/ui/commanddialog.hh"

CWAPI3D_PLUGIN bool plugin_x64_init(CwAPI3D::ControllerFactory *factory)
{
    const auto hwnd = factory->getUtilityController()->get3DHWND();
    const auto mainWidget = QWidget::find(reinterpret_cast<WId>(hwnd));


    if (const auto mainWindow = qobject_cast<QMainWindow *>(mainWidget)) {
        auto commandProcessor = std::make_unique<app::element::service::CommandProcessor>();
        QDockWidget *dialog = new app::element::ui::CommandDialog(std::move(commandProcessor), mainWidget);
        // dockWidget->setWidget(&dialog);
        mainWindow->addDockWidget(Qt::TopDockWidgetArea, dialog);
        dialog->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable);
        // dockWidget->setAttribute(Qt::WA_DeleteOnClose, true);

        dialog->show();
        dialog->raise();
        dialog->activateWindow();

        return false;
    }

    return true;
}

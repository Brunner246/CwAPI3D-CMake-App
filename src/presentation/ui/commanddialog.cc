//
// Created by MichaelBrunner on 27/07/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_CommandDialog.h" resolved

#include <presentation/ui/commanddialog.hh>
#include "ui_CommandDialog.h"
#include <presentation/viewmodel/CommandViewModel.hh>

#include <QQmlApplicationEngine>
#include <QQuickWidget>
#include <QDockWidget>
#include <QMainWindow>
#include <QQmlContext>

namespace app::element::ui
{
CommandDialog::CommandDialog(std::unique_ptr<ICommandProcessor> commandProcessor, QWidget *parent)
    : QDockWidget(parent),
      ui(new Ui::CommandDialog)
      , m_commandProcessor(std::move(commandProcessor))
{
    ui->setupUi(this);

    {
        Qt::WindowFlags flags = Qt::Window;
        flags |= Qt::WindowTitleHint;
        flags |= Qt::WindowCloseButtonHint;
        this->setWindowFlags(flags);
    }
    commandViewModel = std::make_unique<viewmodel::CommandViewModel>(m_commandProcessor.get(), this);
    ui->quickWidget->rootContext()->setContextProperty("commandViewModel", commandViewModel.get());
    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/qml/CommandDock.qml")));
    ui->quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);

    this->setAttribute(Qt::WA_DeleteOnClose, true);
}

CommandDialog::~CommandDialog()
{
    delete ui;
}
} // app::element::ui

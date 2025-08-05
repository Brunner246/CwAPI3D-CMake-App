//
// Created by MichaelBrunner on 27/07/2025.
//

#pragma once

#ifndef Q_MOC_RUN
#include <ui/exports.h>
#endif

#include <QDockWidget>
#include <qglobal.h>


#include "models/presentation/ICommandProcessor.hh"

namespace app::element::viewmodel
{
class CommandViewModel;
}

QT_BEGIN_NAMESPACE

namespace Ui
{
class CommandDialog;
}

QT_END_NAMESPACE

namespace app::element::ui
{
class UI_API CommandDialog: public QDockWidget
{
    Q_OBJECT

public:
    explicit CommandDialog(std::unique_ptr<ICommandProcessor> commandProcessor, QWidget *parent = nullptr);
    ~CommandDialog() override;

private:
    Ui::CommandDialog *ui;
    std::unique_ptr<ICommandProcessor> m_commandProcessor;
    std::unique_ptr<viewmodel::CommandViewModel> commandViewModel;
};
} // app::element::ui

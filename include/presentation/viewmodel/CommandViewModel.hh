//
// Created by MichaelBrunner on 27/07/2025.
//

#pragma once

#ifndef Q_MOC_RUN
#include <presentation/viewmodel/exports.h>
#endif

#include <QObject>
#include <QStringList>


class ICommandProcessor;

namespace app::element::viewmodel
{
class VM_QT_API CommandViewModel: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList availableCommands READ availableCommands NOTIFY availableCommandsChanged)
    Q_PROPERTY(QString commandInput READ commandInput WRITE setCommandInput NOTIFY commandInputChanged)

public:
    explicit CommandViewModel(ICommandProcessor *processor, QObject *parent = nullptr);

    [[nodiscard]] QStringList availableCommands() const;
    [[nodiscard]] QString commandInput() const;
    void setCommandInput(const QString &input);

    Q_INVOKABLE void executeCommand();

signals:
    void availableCommandsChanged();
    void commandInputChanged();
    void commandExecuted(const QString &result);

private:
    QStringList m_availableCommands;
    QString m_commandInput;
    ICommandProcessor *m_processor{nullptr};
};
} // viewmodel
// element
// app

//
// Created by MichaelBrunner on 27/07/2025.
//

#include <presentation/viewmodel/CommandViewModel.hh>
#include <models/presentation/ICommandProcessor.hh>

#include <QDebug>

QString operator""_qs(const char *str, size_t)
{
    return QString::fromStdString(str);
}

namespace app::element::viewmodel
{
CommandViewModel::CommandViewModel(ICommandProcessor *processor, QObject *parent)
    : QObject(parent), m_processor(processor)
{
    std::ranges::transform(processor->suggestCommands(),
                           std::back_inserter(m_availableCommands),
                           [](const std::string_view s)
                           {
                               return QString::fromStdString(s.data());
                           });
}

QStringList CommandViewModel::availableCommands() const
{
    return m_availableCommands;
}

QString CommandViewModel::commandInput() const
{
    qDebug() << "CommandViewModel::commandInput() called, returning:" << m_commandInput;
    return m_commandInput;
}

void CommandViewModel::setCommandInput(const QString &input)
{
    if (m_commandInput != input) {
        m_commandInput = input;
        emit commandInputChanged();
    }
}

void CommandViewModel::executeCommand()
{
    qDebug() << "CommandViewModel::executeCommand() called with input:" << m_commandInput;
    if (m_processor) {
        const auto result = m_processor->processCommand(m_commandInput.toStdString());
        emit commandExecuted(QString::fromStdString(result));
    }
}
} // viewmodel
// element
// app

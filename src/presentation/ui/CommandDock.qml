import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15

Item {
    id: root
    width: 400
    height: 300

    property var filteredCommands: []

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 16
        spacing: 8

        TextField {
            id: inputField
            Layout.fillWidth: true
            placeholderText: "Enter command..."
            font.pixelSize: 14

            text: commandViewModel.commandInput
            onTextChanged: {
                commandViewModel.commandInput = text;

                if (text.length > 0) {
                    root.filteredCommands = commandViewModel.availableCommands.filter(function(cmd) {
                        return cmd.toLowerCase().startsWith(text.toLowerCase());
                    });
                } else {
                    root.filteredCommands = [];
                }

                completerPopup.visible = root.filteredCommands.length > 0;
                completerListView.currentIndex = -1;
            }

            Keys.onDownPressed: {
                if (completerPopup.visible) {
                    completerListView.incrementCurrentIndex();
                }
            }

            Keys.onUpPressed: {
                if (completerPopup.visible) {
                    completerListView.decrementCurrentIndex();
                }
            }

            Keys.onReturnPressed: {
                if (completerPopup.visible && completerListView.currentIndex >= 0) {
                    const selected = root.filteredCommands[completerListView.currentIndex];
                    inputField.text = selected;
                    commandViewModel.commandInput = selected;
                }

                completerPopup.close();
                commandViewModel.executeCommand();
            }
        }

        Label {
            id: resultLabel
            text: "Ausgabe erscheint hier..."
            Layout.fillWidth: true
            wrapMode: Text.Wrap
            font.pixelSize: 13
            color: "#333"
        }
    }

    Popup {
        id: completerPopup
        x: inputField.x
        y: inputField.y + inputField.height + 4
        width: inputField.width
        height: completerListView.implicitHeight + 8 // + padding falls nötig
        modal: false
        focus: false
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

        background: Rectangle {
            anchors.fill: parent
            color: "white"
            border.color: "#aaa"
            radius: 4
        }

        ListView {
            id: completerListView
            anchors.fill: parent
            clip: true
            spacing: 0

            model: root.filteredCommands
            currentIndex: -1

            implicitHeight: Math.min(root.filteredCommands.length * 32, 160)

            delegate: ItemDelegate {
                width: parent.width
                height: 32
                text: modelData
                highlighted: ListView.isCurrentItem

                onClicked: {
                    inputField.text = modelData;
                    commandViewModel.commandInput = modelData;
                    completerPopup.close();
                    inputField.forceActiveFocus();
                    commandViewModel.executeCommand();
                }
            }

            onCurrentIndexChanged: {
                if (currentIndex >= 0)
                    positionViewAtIndex(currentIndex, ListView.Center);
            }
        }
    }


    Connections {
        target: commandViewModel

        function onCommandExecuted(result) {
            resultLabel.text = result;
            // inputField.text = ""; commandViewModel.commandInput = "";
        }
    }
}

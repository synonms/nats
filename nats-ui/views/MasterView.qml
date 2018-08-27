import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Column {
        spacing: 10
        anchors.centerIn: parent

        Button {
            text: "Connect"
            onClicked: masterController.connect()
        }

        Button {
            text: "Disconnect"
            onClicked: masterController.disconnect()
        }
    }
}

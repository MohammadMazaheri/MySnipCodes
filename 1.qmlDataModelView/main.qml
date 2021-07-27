import QtQuick 2.12
import QtQuick.Controls 2.5

ApplicationWindow {
    visible: true
    width: 400
    height: 300

    ListView {
        anchors.fill: parent

        model: dataModel
        delegate: Rectangle {
            height: 20
            width: 400
            color: model.modelData.color
            Text { text: name + "\t|\t" + latitude + "\t|\t" + longitude}
        }
    }
}

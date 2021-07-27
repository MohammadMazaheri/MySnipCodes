import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

ApplicationWindow {
    visible: true
    width: 400
    height: 500

    ColumnLayout
    {
        anchors.fill: parent

        ListView {
            id: listView
            Layout.fillWidth: true
            Layout.fillHeight: true

            model: modelList
            delegate: Rectangle {
                height: 20
                width: 400
                color: model.modelData.color
                Text { text: name + "\t|\t" + latitude + "\t|\t" + longitude}
            }
        }

        RowLayout
        {
            Button
            {
                id: btnAppend
                text: qsTr("Append record")

                onClicked:
                {
                    dataModel.append(txtName.text,Number(txtLat.text),Number(txtLong.text),txtColor.text)
                }
            }

            Button
            {
                id: btnUpdate
                text: qsTr("Update record")

                onClicked:
                {
                    dataModel.update(Number(txtIndex.text),txtName.text,Number(txtLat.text),Number(txtLong.text),txtColor.text)
                }
            }

            Button
            {
                id: btnRemove
                text: qsTr("Remove record")

                onClicked:
                {
                    dataModel.remove(Number(txtIndex.text))
                }
            }
        }

        RowLayout
        {
            Text
            {
                text: qsTr("ID: ")
            }

            TextField
            {
                id: txtIndex
                selectByMouse: true
                text: "0"
            }
        }

        RowLayout
        {
            Text
            {
                text: qsTr("Name: ")
            }

            TextField
            {
                id: txtName
                selectByMouse: true
                text: "Item"
            }
        }

        RowLayout
        {
            Text
            {
                text: qsTr("Latitude: ")
            }

            TextField
            {
                id: txtLat
                selectByMouse: true
                text: "3.14"
            }
        }

        RowLayout
        {
            Text
            {
                text: qsTr("Longitude: ")
            }

            TextField
            {
                id: txtLong
                selectByMouse: true
                text: "3.15"
            }
        }

        RowLayout
        {
            Text
            {
                text: qsTr("Color: ")
            }

            TextField
            {
                id: txtColor
                selectByMouse: true
                text: "lime"
            }
        }
    }
}

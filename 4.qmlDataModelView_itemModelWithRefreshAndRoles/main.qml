import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

ApplicationWindow {
    visible: true
    width: 400
    height: 400

    ColumnLayout
    {
        anchors.fill: parent

        ListView {
            id: listView
            Layout.fillWidth: true
            Layout.fillHeight: true

            model: listModel.model
            delegate: Rectangle {
                height: 20
                width: 400
                color: "lime"
                Text {
                    text: name + "\t" + value
                }
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
                    listModel.append(txtName.text,Number(txtValue.text))
                }
            }

            Button
            {
                id: btnUpdate
                text: qsTr("Update record")

                onClicked:
                {
                    listModel.update(Number(cmb.currentIndex),txtName.text,Number(txtValue.text))
                }
            }

            Button
            {
                id: btnRemove
                text: qsTr("Remove record")

                onClicked:
                {
                    listModel.remove(Number(cmb.currentIndex))
                }
            }

            Button
            {
                id: btnInfo
                text: qsTr("Fields")

                onClicked:
                {
                    console.log("model.rowCount:", listModel.model.rowCount, "model.colCount:", listModel.model.colCount, "model.fieldNames:", listModel.model.fieldNames)
                    //listModel.clear()
                }
            }
        }

        RowLayout
        {
            ComboBox
            {
                id: cmb
                model: listModel.model
                textRole: "name"
                valueRole: "value"

                onCurrentIndexChanged:
                {
                    if(currentIndex > -1)
                    {
                        var index = currentIndex;
                        txtName.text = model.data(index, "name");
                        txtValue.text = model.data(index, "value");

                        console.log("index is:",currentIndex)
                        //console.log("value is:",currentValue)
                    }
                }
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
            }
        }

        RowLayout
        {
            Text
            {
                text: qsTr("Value: ")
            }

            TextField
            {
                id: txtValue
                selectByMouse: true
            }
        }
    }
}


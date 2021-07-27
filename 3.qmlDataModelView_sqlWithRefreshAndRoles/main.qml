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

            model: sqlModel
            delegate: Rectangle {
                height: 20
                width: 400
                color: "lime"
                Text {
                    text: "\t" + id + "\t" + name + "\t" + value + "\t" + isDeleted
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
                    dbInterface.append(txtName.text,Number(txtValue.text))
                    dbInterface.refresh("SELECT * FROM tblTest")
                }
            }

            Button
            {
                id: btnUpdate
                text: qsTr("Update record")

                onClicked:
                {
                    dbInterface.update(Number(txtId.text),txtName.text,Number(txtValue.text),Number(txtIsDel.text))
                    dbInterface.refresh("SELECT * FROM tblTest")
                }
            }

            Button
            {
                id: btnRemove
                text: qsTr("Remove record")

                onClicked:
                {
                    dbInterface.remove(Number(txtId.text))
                    dbInterface.refresh("SELECT * FROM tblTest")
                }
            }
        }

        RowLayout
        {
            ComboBox
            {
                id: cmb
                model: sqlModel
                textRole: "name"
                valueRole: "id"

                onCurrentIndexChanged:
                {
                    if(currentIndex > -1)
                    {
                        var index = currentIndex;
                        txtId.text = model.data(index, "id");
                        txtName.text = model.data(index, "name");
                        txtValue.text = model.data(index, "value");
                        txtIsDel.text = model.data(index, "isDeleted");

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
                text: qsTr("ID: ")
            }

            TextField
            {
                id: txtId
                selectByMouse: true
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

        RowLayout
        {
            Text
            {
                text: qsTr("isDel: ")
            }

            TextField
            {
                id: txtIsDel
                selectByMouse: true
            }
        }
    }
}


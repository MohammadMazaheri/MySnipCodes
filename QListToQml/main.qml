import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

ApplicationWindow {
    visible: true
    width: 240
    height: 120
    title: qsTr("Scroll")

    /**
     * @note
     * QVariantList and QVariantMap to JavaScript Array and Object:
     * The QML engine provides automatic type conversion between QVariantList and JavaScript arrays, and between QVariantMap and JavaScript objects.
     */

    function readObject(obj) {
        console.log("DataModel by calling function:");
        console.log(obj.name,obj.latitude,obj.longitude,obj.color);
    }

    function readList(list) {
        console.log("DataModelList by calling function:");
        for (var i=0; i<list.length; i++)
            console.log(list[i])
    }

    ColumnLayout {
        anchors.fill: parent

        Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: "QList<qreal>"

            onClicked: {
                console.log("QList by loop:");
                for (var i = 0; i < myList.length; ++i)
                {
                    console.log(myList[i]);
                }

                console.log("QList by index:");
                console.log(myList[0],", ",myList[1],", ",myList[2],", ",myList[3]);
            }
        }

        Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: "DataModel*"

            onClicked: {
                console.log("DataModel by fields:");
                console.log("name=",myData.name,",lat=",myData.latitude,",long=",myData.longitude,",color=",myData.color);

                readObject(myData.getObject())
            }
        }

        Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: "DataModelList*"

            onClicked: {
                console.log("DataModelList by fields:");
                console.log(myDataList.strList[0],myDataList.strList[1],myDataList.strList[2],myDataList.strList[3],myDataList.strList[4]);

                readList(myDataList.getList())

                console.log("DataModelList count by calling function:");
                var count = myDataList.getListCount()
                console.log("count=",count);
            }
        }
    }
}

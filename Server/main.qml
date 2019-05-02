import QtQuick 2.9
import QtQml.Models 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import TableModel 0.1
import server 1.0


ApplicationWindow {
    id: root
    visible: true
    width: 640
    height: 480
    minimumHeight: 250
    minimumWidth: 300
    color: "#E3E3D3"
    title: qsTr("Server")

    Column{
        id: mycolumn
        spacing: 10
        width: parent.width
        height: parent.height
        Row{
            width: root.width
            id: myrow
            anchors.margins: 5
            spacing: 50
            Text {
                width: myrow.width/3 - myrow.spacing
                id: labelport
                text: qsTr("Enter port")
                font.pointSize: 16
                font.italic: true
            }
            TextField {
                id: portfield
                width: myrow.width/3 - myrow.spacing
                font.pointSize: 16
                placeholderText: "e.g. 1234"
                style: TextFieldStyle {
                    textColor: "black"
                    background: Rectangle {
                        implicitWidth: 300
                        implicitHeight: 25
                        border.color: "#333"
                        border.width: 1
                    }
                }
                onTextChanged: {
                    if(portfield.text.length >= 4)
                        startServer.enabled = true
                }
            }
            Button{
                width: myrow.width/3 - myrow.spacing
                id: copybutton
                style: ButtonStyle{
                    label: Text{
                        //set text in center
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        text: "Copy"
                        font.pointSize: 14
                        font.family: "Arial Black"
                    }
                }
                onClicked: portfield.copy()
            }
        }
        Network{
            id: server
            /*message: "counter"*/
            onSentData: {
                tablemodel.appendDataFromQml(d, h, n, p)
            }
            onSentMessage: {
                textchatarea.append(t)
            }
            onDisconnect: {
                tablemodel.removeDataFromQml(n)
            }

        }
        ToolButton {
            anchors.horizontalCenter: parent.horizontalCenter
            id: startServer
            enabled: false
            width: parent.width/8
            height: parent.height/8
            Image {
                id: startimage
                source: "/images/start-512.png"
                anchors.fill: parent
                anchors.margins: 4
            }
            onClicked: {
                server.start_button(portfield.text)
                startServer.enabled = false
                portfield.enabled = false
            }
        }
        Rectangle{
            id: chatarea
            width: parent.width
            height: parent.height/3

            TextArea{
                id: textchatarea
                enabled: false
                anchors.fill: parent
                font.pointSize: 14
            }
        }
        Text {
            id: labelactiveusers
            text: qsTr("Active Users:")
            font.pointSize: 16
        }

        TableView{
            width: parent.width
            height: parent.height/3
            //enabled: false

            model: TableModel {
                id: tablemodel
            }

            style: TableViewStyle {
                        headerDelegate: Rectangle {
                            height: textItem.implicitHeight * 1.2
                            width: textItem.implicitWidth
                            color: "lightsteelblue"
                            Text {
                                id: textItem
                                anchors.fill: parent
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: styleData.textAlignment
                                anchors.leftMargin: 12
                                text: styleData.value
                                elide: Text.ElideRight
                                color: textColor
                                renderType: Text.NativeRendering
                            }
                            Rectangle {
                                anchors.right: parent.right
                                anchors.top: parent.top
                                anchors.bottom: parent.bottom
                                anchors.bottomMargin: 1
                                anchors.topMargin: 1
                                width: 1
                                color: "#ccc"
                            }
                        }
            }
            TableViewColumn{
                role: "DomainRole"
                title: "Domain"
            }
            TableViewColumn{
                role: "HostRole"
                title: "Host"
            }
            TableViewColumn{
                role: "UsernameRole"
                title: "Name"
            }
            TableViewColumn{
                role: "PoolingtimeRole"
                title: "Pooling time"
            }
        }
    }
}


import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 1.3
import user 1.0


Window {
    id: window
    visible: true
    width: 640
    height: 480
    color: "#FFFAFFFF"
    title: qsTr("Client")
    minimumHeight: 460
    minimumWidth: 500
    MainWindow{
        id: client

        onValidSocket: {
            connectbutton.enabled = false
            sendbutton.enabled = true
        }

        onFillCharArea: {
            textchatarea.append(tx)
        }
        onChangeConnectButton: {
            connectbutton.enabled = true
            sendbutton.enabled = false
        }

    }

    Grid{
        id:grid
        columns: 2
        rows: 4
        columnSpacing: 20
        rowSpacing: 10
        //5 pixels gone away from left side
        anchors.left: parent.left
        anchors.leftMargin: 5
        Text {
            //width: myrow.width/3 - myrow.spacing
            id: labelport
            text: qsTr("Server port")
            font.pointSize: 16

        }
        TextField {
            id: portfield
            //width: myrow.width/3 - myrow.spacing
            font.pointSize: 16
            placeholderText: "1111"
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
                    connectbutton.enabled = true
            }
        }

        Text {
            //width: myrow.width/3 - myrow.spacing
            id: labelhost
            text: qsTr("Server host")
            font.pointSize: 16
        }
        TextField {
            //width: myrow.width/3 - myrow.spacing
            id: hostfield
            font.pointSize: 16
            font.italic: true
            placeholderText: "127.0.0.1"
            style: TextFieldStyle {
                textColor: "black"
                background: Rectangle {
                    implicitWidth: 300
                    implicitHeight: 25
                    border.color: "#333"
                    border.width: 1
                }
            }
        }

        Text {
            //width: myrow.width/3 - myrow.spacing
            id: labelusername
            text: qsTr("User name")
            font.pointSize: 16
        }
        TextField {
            //width: myrow.width/3 - myrow.spacing
            id: usernamefield
            font.pointSize: 16
            style: TextFieldStyle {
                textColor: "black"
                background: Rectangle {
                    implicitWidth: 300
                    implicitHeight: 25
                    border.color: "#333"
                    border.width: 1
                }
            }
        }

        Text {
            //width: myrow.width/3 - myrow.spacing
            id: labelpoolingperiod
            text: qsTr("Server pooling period")
            font.pointSize: 16
        }
        TextField {
            //width: myrow.width/3 - myrow.spacing
            id: pooltimefield
            font.pointSize: 16
            placeholderText: "e.g 500"
            style: TextFieldStyle {
                textColor: "black"
                background: Rectangle {
                    implicitWidth: 300
                    implicitHeight: 25
                    border.color: "#333"
                    border.width: 1
                }
            }
        }
    }
    Button{
        anchors.top: grid.bottom
        anchors.left: parent.left
        anchors.leftMargin: 5
        id: connectbutton
        enabled: false
        style: ButtonStyle{
            background:  Rectangle{
                implicitWidth: 100
                implicitHeight: 25
                border.width: 1
                radius: 4
                gradient: Gradient {
                    GradientStop { position: 0 ; color: control.pressed ? "#ccc" : "#eee" }
                    GradientStop { position: 1 ; color: control.pressed ? "#aaa" : "#ccc" }
                }
            }
            label: Text{
                //set text in center
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                text: "Connect"
                font.pointSize: 14

            }
        }
        onClicked: {
            client.port = portfield.text
            client.host = hostfield.text
            client.username = usernamefield.text
            client.pooltime = pooltimefield.text
            client.on_ConnectButton_clicked()
        }
    }
    Rectangle{
        //set it after Button
        anchors.top: connectbutton.bottom
        anchors.centerIn: parent
        id: chatarea
        width: parent.width - 10
        height: parent.height/3

        TextArea{
            id: textchatarea
            anchors.fill: parent
            font.pointSize: 14
            enabled: false
        }
    }
    CheckBox{
        id: checkbox
        anchors.top: chatarea.bottom
        anchors.left: parent.left
        anchors.leftMargin: 5
        style: CheckBoxStyle{
            indicator: Rectangle {
                implicitWidth: 16
                implicitHeight: 16
                radius: 3
                border.color: control.activeFocus ? "darkblue" : "gray"
                border.width: 1
                Rectangle {
                    visible: control.checked
                    color: "#555"
                    border.color: "#333"
                    radius: 1
                    anchors.margins: 4
                    anchors.fill: parent
                }
            }
            label: Text {
                id: name
                text: qsTr("Send anonymously")
                font.pointSize: 14
            }
        }
    }

    Row{
        spacing: 10
        anchors.top: checkbox.bottom
        anchors.left: parent.left
        anchors.leftMargin: 5
        width: parent.width
        height: parent.height/5

        Rectangle{
            id: fillarea
            width: parent.width*2/3
            height: parent.height
            TextArea{
                id: sendtext
                anchors.fill: parent
                font.pointSize: 14
            }
        }

        Button{
            id: sendbutton
            enabled: false
            style: ButtonStyle{
                background:  Rectangle{
                    implicitWidth: 100
                    implicitHeight: 25
                    border.width: 1
                    radius: 4
                    gradient: Gradient {
                        GradientStop { position: 0 ; color: control.pressed ? "#ccc" : "#eee" }
                        GradientStop { position: 1 ; color: control.pressed ? "#aaa" : "#ccc" }
                    }
                }
                label: Text{
                    //set text in center
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter

                    text: "Send"
                    font.pointSize: 14

                }
            }
            onClicked: {
                client.on_SendButton_clicked(checkbox.checked, sendtext.text)
                sendtext.text = " "
            }
        }
    }
}

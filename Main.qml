import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Dialogs

import ClassArduinoBoard 1.0

Window {
    id: root
    width: 460
    minimumWidth: 360
    height: 680
    minimumHeight: 600
    visible: true
    title: qsTr("Traffic Light")
    color: "beige"

    // State of lights
    property bool yellowlight: false
    property bool greenlight: false
    property bool redlight: false
    property int phase: 1

    // Platform status
    property bool android: false
    property int fontsize: android ? 14 : 12

    // C++ Class connected with serial port -> arduino
    Arduino{
        id: arduino
    }
    //!---------------------


    Timer{
        id: traffic_timer
        interval: 2000
        repeat: true
        running: trafficON.checked ? true : false
        onTriggered: {


            if(phase === 1){
                redlight = true
                yellowlight = false
                greenlight = false

                arduino.setCommand("r1y0g0");

                phase++
                return
            }

            if(phase === 2){
                redlight = true
                yellowlight = true
                greenlight = false

                arduino.setCommand("r1y1g0");

                phase++
                return
            }

            if(phase === 3){
                redlight = false
                yellowlight = false
                greenlight = true

                arduino.setCommand("r0y0g1");

                phase = 1
                return
            }
        }

        onRunningChanged: {

             if(!traffic_timer.running){
                 redlight = false
                 yellowlight = false
                 greenlight = false
                 arduino.setCommand("r0y0g0");
                 phase = 1

             }
        }
    }

    Timer{
        id: maintaince_timer
        running: trafficMaintaince.checked ? true : false
        interval: 1000
        repeat: true
        onTriggered: {

            yellowlight === true ?  yellowlight = false : yellowlight = true

            if(yellowlight)
                arduino.setCommand("r0y1g0");
            else
                arduino.setCommand("r0y0g0");

        }
        onRunningChanged: {

             if(!maintaince_timer.running){
                yellowlight = false
                arduino.setCommand("r0y0g0");
             }
        }
    }

    // Switch
    Column{
        id: columnSwitch
        x:20; y:20
        Row{

            height: 35
            spacing: 10

            Switch{
                id: trafficON
                height: 22
                text: trafficON.checked ? "ON" : "OFF"

                onToggled: {

                    if(trafficON.checked)
                        trafficMaintaince.checked = false
                }
            }

            Text{
                height: 35
                text: trafficON.checked ? "The trafficlight is turned ON" : "The trafficlight is turned OFF"
                font.pointSize: fontsize
                color: trafficON.checked ? "blue" : "gray"

            }
        }
        Row{

            height: 35
            spacing: 10

            Switch{
                id: trafficMaintaince
                height: 22
                text: trafficMaintaince.checked ? "ON" : "OFF"
                onToggled: {

                    if(trafficMaintaince.checked){
                        trafficON.checked = false
                        trafficManual.checked = false
                    }


                }
            }

            Text{
                height: 35
                text: trafficMaintaince.checked ? "Maintaince ON" : "Maintaince OFF"
                font.pointSize: fontsize
                color: trafficMaintaince.checked ? "blue" : "gray"

            }
        }
        Row{

            height: 35
            spacing: 10

            Switch{
                id: trafficManual
                height: 22
                text: trafficManual.checked ? "ON" : "OFF"
                onToggled: {

                    if(trafficManual.checked){
                        trafficON.checked = false
                        trafficMaintaince.checked = false
                    }
                }
            }

            Text{
                height: 35
                text: trafficManual.checked ? "Manual ON" : "Manual OFF"
                font.pointSize: fontsize
                color: trafficManual.checked ? "blue" : "gray"

            }
        }
    }

    // Traffic Light
    Rectangle{
        id: trafficrect
        width: 100
        height: 250
        color: "lightgray"
        border.color: "gray"

        anchors.centerIn: parent

        Column{
            id: column
            width: parent.width
            height: parent.height - 20
            spacing: 5
            x: column.width/2 - redrect.width/2
            y:5
            // Red Light
            Rectangle{
                id: redrect
                width: parent.height/3
                height: parent.height/3
                radius: parent.width
                border.color: "gray"
                color: redlight ? "red" : "white"
                MouseArea{
                    anchors.fill: parent
                    onClicked: {

                        if(trafficManual.checked){
                            redlight ?  redlight = false : redlight = true

                            if(redlight)
                                arduino.setCommand("r1");
                            else
                                arduino.setCommand("r0");


                        }
                    }
                }

            }

            // Yellow Light
            Rectangle{
                id: yellowrect
                width: parent.height/3
                height: parent.height/3
                radius: parent.width
                border.color: "gray"
                color: yellowlight ? "yellow" : "white"
                MouseArea{
                    anchors.fill: parent
                    onClicked: {

                        if(trafficManual.checked){
                            yellowlight ?  yellowlight = false : yellowlight = true


                            if(yellowlight)
                                arduino.setCommand("y1");
                            else
                                arduino.setCommand("y0");

                        }
                    }
                }
            }

            // Green Light
            Rectangle{
                id: greenrect
                width: parent.height/3
                height: parent.height/3
                radius: parent.height/3
                border.color: "gray"
                color: greenlight ? "green" : "white"
                MouseArea{
                    anchors.fill: parent
                    onClicked: {

                        if(trafficManual.checked){
                            greenlight ?  greenlight = false : greenlight = true

                            if(greenlight)
                                arduino.setCommand("g1");
                            else
                                arduino.setCommand("g0");

                        }
                    }
                }
            }
        }
    }

    // Information Text about connected arduino board
    Grid{
        columns: 2
        columnSpacing: 10
        rowSpacing: 5
        anchors.top: trafficrect.bottom
        anchors.left: columnSwitch.left
        anchors.topMargin: 10

        Text {
            text: qsTr("Available Board: ")
            color: "gray"
            font.pointSize: fontsize
        }
        Text {
            text: arduino.isAvailable ? arduino.boardManufacturer : "None"
            color: "#2979FF"
            font.pointSize: fontsize
        }
        Text {
            text: qsTr("Description Board: ")
            color: "gray"
            font.pointSize: fontsize
        }
        Text {
            text: arduino.isAvailable ? arduino.boardDescription : "None"
            color: "#2979FF"
            font.pointSize: fontsize
        }
        Text {
            text: qsTr("Vendor-ID: ")
            color: "gray"
            font.pointSize: fontsize
        }
        Text {
            text: arduino.isAvailable ? arduino.vendorID : "None"
            color: "#2979FF"
            font.pointSize: fontsize
        }
        Text {
            text: qsTr("Product-ID: ")
            color: "gray"
            font.pointSize: fontsize
        }
        Text {
            text: arduino.isAvailable ? arduino.productID : "None"
            color: "#2979FF"
            font.pointSize: fontsize
        }
        Text {
            text: qsTr("Port: ")
            color: "gray"
            font.pointSize: fontsize
        }
        Text {
            text: arduino.isAvailable ? arduino.portName : "None"
            color: "#2979FF"
            font.pointSize: fontsize
        }
        Text {
            text: qsTr("Writeable: ")
            color: "gray"
            font.pointSize: fontsize
        }
        Text {
            text: arduino.isWriteable ? "Yes" : "No"
            color: arduino.isWriteable ?  "green" : "red"
            font.pointSize: fontsize
        }
    }


    Component.onCompleted: {

        // Check on wich platform is this app running?
        if(Qt.platform.os === "android")
            android = true


        // Function called in C++ Class Arduino
        arduino.checkAvailableBoards()


    }

}

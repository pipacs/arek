import QtQuick 1.1
import com.nokia.meego 1.0

Page {
    id: page
    // tools: commonTools
    Column {
        id: col
        spacing: 11
        anchors.margins: 22
        anchors.centerIn: parent

        Image {
            source: "arek80.png"
        }
        Label {
            text: "Accelerometer Rekorder"
            font.pixelSize: 32
        }
        Label {
            width: page.width - 44
            text: "Sensor readings are logged to MyDocs/Documents/<i>date-name</i>.csv\n"
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            color: "grey"
        }

        Label {
            text: "Log file name:"
        }
        TextField {
            id: fileName
            width: col.width - 22
            enabled: !counter.running
        }
        Label {
            text: "Current reading:"
        }
        Label {
            id: readingX
            text: "0"
        }
        Label {
            id: readingY
            text: "0"
        }
        Label {
            id: readingZ
            text: "0"
        }
        Button {
            text: counter.running? "Stop": "Start"
            iconSource: counter.running? "image://theme/icon-m-toolbar-mediacontrol-stop": "image://theme/icon-m-toolbar-mediacontrol-play"
            enabled: fileName.text !== ""
            onClicked: {
                logger.fileName = fileName.text
                counter.running = !counter.running
                if (!counter.running) {
                    logger.flush()
                    readingX.text = "0"
                    readingY.text = "0"
                    readingZ.text = "0"
                }
            }
        }
    }

    function readingChanged(r) {
        readingX.text = r["x"]
        readingY.text = r["y"]
        readingZ.text = r["z"]
        logger.log(r)
    }

    Component.onCompleted: {
        counter.readingChanged.connect(readingChanged)
    }
}

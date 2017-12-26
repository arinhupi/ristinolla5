import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    id: appWindow
    visible: true
    width: rntable.gRows * 30 + 150
    height: rntable.gCols * 30 + 200
    maximumWidth: width
    maximumHeight: height
    minimumWidth: width
    minimumHeight: height
    title: qsTr("Ristinolla")

    RNTable {
        id: rntable
    }


}

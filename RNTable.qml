import QtQuick 2.0
import QtQuick.Controls 2.1

Rectangle {
    width: parent.width
    height: parent.height
    color: "#555555"
    property int playerTurn: 1
    property int gRows: 15 // when changing table size change also table init in main.cpp
    property int gCols: 15

    function setValue(row, col, value){
        var repIndex = row * gRows + col;
        rep.itemAt(repIndex).ntValue = value;
        rep.itemAt(repIndex).visible = true;
    }

    function setColorOfSequence(indexes){
        for (var i=1; i < indexes.length; i++)
        rep.itemAt(indexes[i]).color = "#eebb11";
    }

    function clearTable(){
        for (var i=0; i<grid.columns*grid.rows; i++){
            rep.itemAt(i).ntValue = "";
            rep.itemAt(i).color = "#eeeeee";
        }
    }

    Grid {
        id: grid
        anchors.horizontalCenter: parent.horizontalCenter
        y: 50
        rows: gRows; columns: gCols; spacing: 2

        Repeater {
            id: rep
             model: gRows * gCols
             Rectangle {
                 id: rec
                 property alias ntValue: numtext.text
                  width: 30; height: 30
                  color: "#eeeeee"
                  Text {
                      id: numtext
                      font.pointSize: 20
                      anchors.centerIn: parent
                  }
                  MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            if (playerTurn === 1 && rngame.checkMove(Math.floor(index/gRows), index%gCols, 1)){
                                numtext.text = "X";
                                var longestSeq = rngame.fullSeqFound(1);
                                if (longestSeq[0] === 5){
                                    //console.log("You won!");
                                    setColorOfSequence(longestSeq);
                                } else {
                                    playerTurn = 2;
                                    compMoveTimer.start();
                                }
                            }
                        }
                  }
              }
          }
    }

    Timer {
        id: compMoveTimer
        interval: 500
        onTriggered:{
            var rc = rngame.getComputerMove();
            rep.itemAt(rc).ntValue = "O";
            var longestSeq = rngame.fullSeqFound(2);
            if (longestSeq[0] === 5){
                //console.log("computer won!");
                setColorOfSequence(longestSeq);
            }
            else
                playerTurn = 1;
        }
    }

    Button {
        id: resetButton
        anchors.left: grid.left
        y: appWindow.height - 75
        text: "new game"
        onClicked: {clearTable(); rngame.resetTable(); playerTurn = 1;}
    }

    Button {
        anchors.right: grid.right
        y: appWindow.height - 75
        text: "quit"
        onClicked: appWindow.close();
    }

}

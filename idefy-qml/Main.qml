import QtCore
import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import QtQuick.Dialogs
import idefy

pragma ComponentBehavior: Bound

ApplicationWindow {
    id: root

    property bool showLineNumbers: true
    property string currentFilePath: "File"

    visible: true
    title: "IDEFY"

    color: Colors.background
    flags: Qt.Window | Qt.FramelessWindowHint

    width: Constants.width
    height: Constants.height

    menuBar: MyMenuBar {
        dragWindow: root
        infoText: "IDEFY"
        MyMenu {
            title: qsTr("File")

            Action {
                text: "Open Layer"
                shortcut: StandardKey.Open
                onTriggered: workspaceDialog.open()
            }
            Action {
                text: qsTr("Increase Font")
                shortcut: StandardKey.ZoomIn
                onTriggered: editor.text.font.pixelSize += 1
            }
            Action {
                text: qsTr("Decrease Font")
                shortcut: StandardKey.ZoomOut
                onTriggered: editor.text.font.pixelSize -= 1
            }
            Action {
                text: root.showLineNumbers ? qsTr("Toggle Line Numbers OFF")
                                           : qsTr("Toggle Line Numbers ON")
                shortcut: "Ctrl+L"
                onTriggered: root.showLineNumbers = !root.showLineNumbers
            }
            Action {
                text: root.expandPath ? qsTr("Toggle Short Path")
                                      : qsTr("Toggle Expand Path")
                enabled: root.currentFilePath
                onTriggered: root.expandPath = !root.expandPath
            }
            Action {
                text: qsTr("Reset Filesystem")
                enabled: sidebar.currentTabIndex === 1
                onTriggered: fileSystemView.rootIndex = undefined
            }
            Action {
                text: qsTr("Exit")
                onTriggered: Qt.exit(0)
                shortcut: StandardKey.Quit
            }
        }
    }

    FolderDialog {
        id: workspaceDialog
        currentFolder: StandardPaths.standardLocations(StandardPaths.HomeLocation)[0]
        onAccepted: YoctoEngine.tryToSetYoctoRoot(currentFolder)
    }

    RowLayout {
            anchors.fill: parent
            spacing: 0

            // Stores the buttons that navigate the application.
            Sidebar {
                id: sidebar
                dragWindow: root
                Layout.preferredWidth: 50
                Layout.fillHeight: true
            }

            // Allows resizing parts of the UI.
            SplitView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                // Customized handle to drag between the Navigation and the Editor.
                handle: Rectangle {
                    implicitWidth: 10
                    color: SplitHandle.pressed ? Colors.color2 : Colors.background
                    border.color: SplitHandle.hovered ? Colors.color2 : Colors.background
                    opacity: SplitHandle.hovered || navigationView.width < 15 ? 1.0 : 0.0

                    Behavior on opacity {
                        OpacityAnimator {
                            duration: 1400
                        }
                    }
                }

                Rectangle {
                    id: navigationView
                    color: Colors.surface1
                    SplitView.preferredWidth: 250
                    SplitView.fillHeight: true
                    // The stack-layout provides different views, based on the
                    // selected buttons inside the sidebar.
                    StackLayout {
                        anchors.fill: parent
                        currentIndex: sidebar.currentTabIndex

                        // Shows the files on the file system.
                        LayerExplorerView {
                            id: layerExplorerView
                            color: Colors.surface1
                            onFileClicked: path => root.currentFilePath = path
                        }
                    }
                }

                // The main view that contains the editor.
                Editor {
                    id: editor
                    showLineNumbers: root.showLineNumbers
                    currentFilePath: root.currentFilePath
                    SplitView.fillWidth: true
                    SplitView.fillHeight: true
                }
            }
    }
}


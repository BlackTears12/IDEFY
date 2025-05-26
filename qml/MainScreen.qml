

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import idefy

Rectangle {
    id: rectangle
    width: Constants.width
    height: Constants.height

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

                        // Shows the help text.
                        Text {
                            text: qsTr("This example shows how to use and visualize the file system.\n\n"
                                     + "Customized Qt Quick Components have been used to achieve this look.\n\n"
                                     + "You can edit the files but they won't be changed on the file system.\n\n"
                                     + "Click on the folder icon to the left to get started.")
                            wrapMode: TextArea.Wrap
                            color: Colors.text
                        }

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

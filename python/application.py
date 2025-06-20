import sys
from PySide6.QtGui import QGuiApplication
from PySide6.QtQml import QQmlApplicationEngine

class Application(QGuiApplication):
    def __init__(self,args=sys.argv):
        super().__init__(args)
        self.engine = QQmlApplicationEngine()
        self.engine.addImportPath(sys.path[0])
        

    def execute(self):
        self.engine.loadFromModule("idefy-qml", "Main")
        if not self.engine.rootObjects():
            sys.exit(-1)
        exit_code = self.exec()
        del self.engine
        sys.exit(exit_code)
    
    
    
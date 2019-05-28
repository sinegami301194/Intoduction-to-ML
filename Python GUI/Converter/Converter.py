from PyQt5 import QtWidgets, uic

def Convert():
    dlg.lineEdit_2.setText(str(float(dlg.lineEdit.text())))

app = QtWidgets.QApplication([])
dlg = uic.loadUi('test1.ui')

dlg.pushButton.clicked.connect(Convert)

dlg.show()
app.exec()

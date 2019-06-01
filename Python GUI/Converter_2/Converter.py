from PyQt5 import QtWidgets, uic

def Convert():
    dlg.lineEdit_2.setText(str(float(dlg.lineEdit.text())))

app = QtWidgets.QApplication([])
dlg = uic.loadUi('test1.ui')

dlg.lineEdit.setFocus()
dlg.lineEdit.setPlaceholderText('Inter')
dlg.pushButton.clicked.connect(Convert)
dlg.lineEdit.returnPressed.connect(Convert)
dlg.lineEdit_2.setReadOnly(True)

dlg.show()
app.exec()
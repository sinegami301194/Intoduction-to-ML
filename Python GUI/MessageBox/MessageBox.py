from PyQt5 import QtWidgets, uic # Import libraries
from PyQt5.QtWidgets import *

def Convert():
    dlg.lineEdit_2.setText(str(float(dlg.lineEdit.text())))

def addItem():
    if not dlg.lineEdit_3.text()=='':
        dlg.listWidget.addItem(dlg.lineEdit_3.text())
        dlg.lineEdit_3.setText('')
    else:
        showMessage('Warning', 'You have to type one element')

def showMessage(title,message):
    QMessageBox.information(None,title,message)

app = QtWidgets.QApplication([])
dlg = uic.loadUi('test1.ui')

dlg.lineEdit.setFocus()
dlg.lineEdit.setPlaceholderText('Inter')
dlg.pushButton.clicked.connect(Convert)
dlg.lineEdit.returnPressed.connect(Convert)
dlg.lineEdit_2.setReadOnly(True)

dlg.lineEdit_3.setPlaceholderText('Inter to add Item')
dlg.pushButton_2.clicked.connect(addItem)


dlg.show()
app.exec()

from PyQt5 import QtWidgets, uic


app = QtWidgets.QApplication([])
dlg = uic.loadUi('test1.ui')

dlg.show()
app.exec()

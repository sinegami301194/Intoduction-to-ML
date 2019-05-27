from PyQt5 import QtWidgets, uic # Include Libraries


app = QtWidgets.QApplication([])
dlg = uic.loadUi('test1.ui')

dlg.show()
app.exec()

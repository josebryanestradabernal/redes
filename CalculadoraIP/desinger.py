# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'guiCalculator.ui'
#
# Created by: PyQt5 UI code generator 5.15.0
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(947, 445)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.label_2 = QtWidgets.QLabel(self.centralwidget)
        self.label_2.setGeometry(QtCore.QRect(10, 30, 101, 17))
        self.label_2.setObjectName("label_2")
        self.txtIp = QtWidgets.QTextEdit(self.centralwidget)
        self.txtIp.setGeometry(QtCore.QRect(100, 20, 181, 31))
        self.txtIp.setObjectName("txtIp")
        self.groupBox = QtWidgets.QGroupBox(self.centralwidget)
        self.groupBox.setGeometry(QtCore.QRect(10, 60, 141, 101))
        self.groupBox.setObjectName("groupBox")
        self.radioButton_3 = QtWidgets.QRadioButton(self.groupBox)
        self.radioButton_3.setGeometry(QtCore.QRect(10, 20, 112, 23))
        self.radioButton_3.setObjectName("radioButton_3")
        self.buttonGroup = QtWidgets.QButtonGroup(MainWindow)
        self.buttonGroup.setObjectName("buttonGroup")
        self.buttonGroup.addButton(self.radioButton_3)
        self.radioButton = QtWidgets.QRadioButton(self.groupBox)
        self.radioButton.setGeometry(QtCore.QRect(10, 60, 112, 23))
        self.radioButton.setChecked(True)
        self.radioButton.setObjectName("radioButton")
        self.buttonGroup.addButton(self.radioButton)
        self.Prefijo = QtWidgets.QRadioButton(self.groupBox)
        self.Prefijo.setGeometry(QtCore.QRect(10, 40, 112, 23))
        self.Prefijo.setObjectName("Prefijo")
        self.buttonGroup.addButton(self.Prefijo)
        self.radioButton.raise_()
        self.radioButton_3.raise_()
        self.Prefijo.raise_()
        self.txtOp = QtWidgets.QTextEdit(self.centralwidget)
        self.txtOp.setGeometry(QtCore.QRect(160, 60, 104, 31))
        self.txtOp.setPlaceholderText("")
        self.txtOp.setObjectName("txtOp")
        self.txtMarcara = QtWidgets.QTextEdit(self.centralwidget)
        self.txtMarcara.setGeometry(QtCore.QRect(450, 10, 261, 91))
        self.txtMarcara.setObjectName("txtMarcara")
        self.txtCalculos = QtWidgets.QTextEdit(self.centralwidget)
        self.txtCalculos.setGeometry(QtCore.QRect(450, 110, 261, 81))
        self.txtCalculos.setObjectName("txtCalculos")
        self.label = QtWidgets.QLabel(self.centralwidget)
        self.label.setGeometry(QtCore.QRect(80, 210, 141, 17))
        self.label.setObjectName("label")
        self.label_3 = QtWidgets.QLabel(self.centralwidget)
        self.label_3.setGeometry(QtCore.QRect(470, 210, 241, 17))
        self.label_3.setObjectName("label_3")
        self.tableSubrede = QtWidgets.QTableWidget(self.centralwidget)
        self.tableSubrede.setGeometry(QtCore.QRect(30, 230, 256, 192))
        self.tableSubrede.setObjectName("tableSubrede")
        self.tableSubrede.setColumnCount(0)
        self.tableSubrede.setRowCount(0)
        self.tableHost = QtWidgets.QTableWidget(self.centralwidget)
        self.tableHost.setGeometry(QtCore.QRect(450, 230, 256, 192))
        self.tableHost.setObjectName("tableHost")
        self.tableHost.setColumnCount(0)
        self.tableHost.setRowCount(0)
        self.btnCalcular = QtWidgets.QPushButton(self.centralwidget)
        self.btnCalcular.setGeometry(QtCore.QRect(110, 160, 161, 25))
        self.btnCalcular.setObjectName("btnCalcular")
        self.subred = QtWidgets.QTextEdit(self.centralwidget)
        self.subred.setGeometry(QtCore.QRect(650, 200, 61, 31))
        self.subred.setObjectName("subred")
        self.groupBox_2 = QtWidgets.QGroupBox(self.centralwidget)
        self.groupBox_2.setGeometry(QtCore.QRect(730, 10, 161, 101))
        self.groupBox_2.setObjectName("groupBox_2")
        self.TipoA = QtWidgets.QRadioButton(self.groupBox_2)
        self.TipoA.setGeometry(QtCore.QRect(10, 30, 112, 23))
        self.TipoA.setObjectName("TipoA")
        self.TipoB = QtWidgets.QRadioButton(self.groupBox_2)
        self.TipoB.setGeometry(QtCore.QRect(10, 50, 112, 23))
        self.TipoB.setObjectName("TipoB")
        self.TipoC = QtWidgets.QRadioButton(self.groupBox_2)
        self.TipoC.setGeometry(QtCore.QRect(10, 70, 112, 23))
        self.TipoC.setObjectName("TipoC")
        self.redesPrivadas = QtWidgets.QTextEdit(self.centralwidget)
        self.redesPrivadas.setGeometry(QtCore.QRect(730, 120, 191, 241))
        self.redesPrivadas.setObjectName("redesPrivadas")
        MainWindow.setCentralWidget(self.centralwidget)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)
        self.menuBar = QtWidgets.QMenuBar(MainWindow)
        self.menuBar.setGeometry(QtCore.QRect(0, 0, 947, 22))
        self.menuBar.setObjectName("menuBar")
        MainWindow.setMenuBar(self.menuBar)
        self.toolBar = QtWidgets.QToolBar(MainWindow)
        self.toolBar.setObjectName("toolBar")
        MainWindow.addToolBar(QtCore.Qt.TopToolBarArea, self.toolBar)
        self.toolBar_2 = QtWidgets.QToolBar(MainWindow)
        self.toolBar_2.setObjectName("toolBar_2")
        MainWindow.addToolBar(QtCore.Qt.TopToolBarArea, self.toolBar_2)
        self.toolBar_3 = QtWidgets.QToolBar(MainWindow)
        self.toolBar_3.setObjectName("toolBar_3")
        MainWindow.addToolBar(QtCore.Qt.TopToolBarArea, self.toolBar_3)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "CalculadoraIP"))
        self.label_2.setText(_translate("MainWindow", "Dirección IP:"))
        self.groupBox.setTitle(_translate("MainWindow", "Selecciona la opcion: "))
        self.radioButton_3.setText(_translate("MainWindow", "Subredes"))
        self.radioButton.setText(_translate("MainWindow", "Host"))
        self.Prefijo.setText(_translate("MainWindow", "Prefijo"))
        self.label.setText(_translate("MainWindow", "Lista de Subredes"))
        self.label_3.setText(_translate("MainWindow", "Lista de host en la subred"))
        self.btnCalcular.setText(_translate("MainWindow", "Calcular"))
        self.groupBox_2.setTitle(_translate("MainWindow", "Redes Privadas de tipo: "))
        self.TipoA.setText(_translate("MainWindow", "Tipo A"))
        self.TipoB.setText(_translate("MainWindow", "Tipo B "))
        self.TipoC.setText(_translate("MainWindow", "Tipo C "))
        self.toolBar.setWindowTitle(_translate("MainWindow", "toolBar"))
        self.toolBar_2.setWindowTitle(_translate("MainWindow", "toolBar_2"))
        self.toolBar_3.setWindowTitle(_translate("MainWindow", "toolBar_3"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())

from desinger import *
from  PyQt5.QtWidgets import QTableWidgetItem
#Implementacion de la parte grafica, diseñada en qt5
class MainWindow(QtWidgets.QMainWindow, Ui_MainWindow):
    def __init__ (self, *args,**kwargs):
        QtWidgets.QMainWindow.__init__(self,*args,**kwargs)
        self.setupUi(self)
        self.btnCalcular.clicked.connect(self.BtnCalculatorFun) 
    def BtnCalculatorFun (self): 
        flag=0
        self.tableSubrede.setColumnCount(1)
        self.tableHost.setColumnCount(1) 
        if (self.radioButton.isChecked()):
             flag=1
        elif (self.radioButton_3.isChecked()):
             flag=2
        elif (self.Prefijo.isChecked()):
             flag=3
        s=Solution(self.txtOp.toPlainText(),self.txtIp.toPlainText(),flag)
        s.calcular(self)

class Solution (object):
    def __init__ (self,numHoS,DirIP,flag):
        self.numHoS=numHoS
        self.DirIP=DirIP
        self.flag=flag
#trabaja bajo demanda de hosting o subredes
    def calcular(self,window):
        IpBase=0
        corrimientos=3
        split=self.DirIP.split('.')
        print (split)
        for a in split:
            IpBase|=(int(a)<<corrimientos*8) 
            corrimientos-=1;
        #despues de poner todos los bits en la misma variable se empiza a trabajar
        numClase=0
        numClase=int (split[0])>>5;
        if(bin(numClase>>2)=='0b0'):
            print("Clase A")
            window.txtMarcara.setText("Clase A")
            numClase=8
        elif (bin(numClase>>1)=='0b10'):
            print ("clase B")
            window.txtMarcara.setText("Clase B")
            numClase=16
        elif (bin(numClase)=='0b110'):
            print ("clase C")
            window.txtMarcara.setText("Clase C")
            numClase=24
        numhost=0
        numsuredes=0
        #cuando la flag esta en uno significa que esta activado en modo host
        if (self.flag==1): 
            numhost=self.LowerBound(int (self.numHoS))
            numsuredes=32-numClase-numhost
        elif (self.flag==2) :  
            numsuredes=self.LowerBound(int(self.numHoS))
            numhost=32-numClase-numsuredes
        elif (self.flag==3) :
            #para el caso del prefijo es algo especial ya que el prefijo es igual a numClase+ numSubredes
            numsuredes=(int (self.numHoS))-numClase
            numhost=32-numClase- numsuredes
        #crear una matriz para introducir los datos que se retornaran al inicio
        mascara=((1<<numClase+numsuredes)-1)<<numhost
        window.txtCalculos.setText("Cant. Host: "+str((2**numhost)-2)+"\nCant. SubRedes: "+str((2**numsuredes)-2)
        +"\nMSubRed: "+str(mascara>>24)+"."+str((mascara>>16)&0xff)+"."+ str((mascara>>8)&0xff)+"."+str (mascara&0xff)) 
        #mascara de Red antes De formar las subredes
        mascara=((1<<numClase)-1)<<numsuredes+numhost
        window.txtMarcara.append("MRed:"+str(mascara>>24)+"."+str((mascara>>16)&0xff)+"."+str((mascara>>8)&0xff)+"."+
        str(mascara&0xff))
        print (IpBase)
        subredes=IpBase>>numhost
        window.tableSubrede.clear()
        window.tableSubrede.setRowCount(0)
        for a in range (0,(2**numsuredes)-2):     
            subredes+=1
            subred=subredes<<numhost
            window.tableSubrede.insertRow(window.tableSubrede.rowCount())
            window.tableSubrede.setItem(window.tableSubrede.rowCount()-1,0,QTableWidgetItem(str(subred>>24)+"."+
            str((subred>>16)&0xff)+"."+str((subred>>8)&0xff)+"."+str(subred&0xff)+"/"+str(numClase+numsuredes)))
        hosted=IpBase>>numhost
        hosted+=int(window.subred.toPlainText())
        hosted=hosted<<numhost
        window.tableHost.clear()
        window.tableHost.setRowCount(0)
        for a in range (0, (2**numhost)-2):
            hosted+=1
            window.tableHost.insertRow(window.tableHost.rowCount()) 
            window.tableHost.setItem(window.tableHost.rowCount()-1,0,QTableWidgetItem(str(hosted>>24)+"."+
            str((hosted>>16)&0xff)+"."+str((hosted>>8)&0xff)+"."+str(hosted&0xff)))
        
        #se calculan las redes privadas en funcion del tipo que se prefiera 
        #IpBasePrivadas=0; 
        if (window.TipoA.isChecked()): 
            window.redesPrivadas.setText("Clase tipo A\nDir IP: 10.0.0.0/8\n MRed:255.0.0.0")  
        elif (window.TipoB.isChecked()):
            window.redesPrivadas.setText("Clase tipo B\nDir IP: 172.16.0.0/12\n MRed:255.240.0.0")  
        elif (window.TipoC.isChecked()):  
            window.redesPrivadas.setText("Clase tipo C\nDir IP: 192.168.0.0/16\n MRed:255.255.0.0")  
    def LowerBound(self,num):
        l=0
        r=100
        loweBound=0; 
        while (r>=l): 
            m=int (l+(r-l)/2)
            if ((2**m-2)>=num):
                loweBound=m
                r=m-1;
            else: 
                l=m+1
        return loweBound
if __name__=="__main__":
    app=QtWidgets.QApplication([])
    window =MainWindow()
    window.show()
    app.exec_()

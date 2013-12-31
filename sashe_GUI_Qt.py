# -*- coding: utf-8 -*-
import sys
import socket 
from PyQt4.QtCore import *
from PyQt4.QtGui import *


class ConfigWindow(QDialog):
    """Configure window to set IP of server"""
    def __init__(self, parent = None):
        """ initializes IP window"""
        super(ConfigWindow, self).__init__(parent)
        self.my_ip_address = self.get_local_ip_address()
        iplabel = QLabel("IP address")
        self.ipedit = QLineEdit("")
        configButton = QDialogButtonBox(QDialogButtonBox.Ok|QDialogButtonBox.Cancel)
        youriplabel = QLabel("Your IP address:")
        yourip = QLabel(self.my_ip_address)
        space = QLabel(" ")

        grid = QGridLayout()
        grid.addWidget(youriplabel, 0, 0)
        grid.addWidget(yourip,0,1)
        grid.addWidget(iplabel, 1, 0)
        grid.addWidget(self.ipedit, 1, 1)
        grid.addWidget(space,2,0)
        grid.addWidget(configButton, 3, 0)

        self.connect(configButton, SIGNAL("accepted()"), self, SLOT("accept()"))
        self.connect(configButton, SIGNAL("rejected()"), self, SLOT("reject()"))

        self.setWindowTitle("Enter Server IP")
        self.setLayout(grid)



    def get_local_ip_address(self):
        target = 'mrwiki.olin.edu'
        ipaddr = ''
        try:
            s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            s.connect((target, 8000))
            ipaddr = s.getsockname()[0]
            s.close()
        except:
            pass

        return ipaddr


    def get_ip_address(self):
        return self.my_ip_address, self.target_ip

    def accept(self):
        self.target_ip = self.ipedit.text()
        QDialog.accept(self)

class MainForm(QMainWindow):
    """main window for file tree test"""
    def __init__(self, parent=None, server=None):
        """initializes main window and tree w/ splitter"""
        super(MainForm, self).__init__(parent)

        self.get_ip()
        
        model_host = QFileSystemModel()
        model_host.setRootPath(QDir.homePath())
        if not server:
            model_server = QFileSystemModel() #Qmodel_server.setRootPath(QDir.homePath())FileSystemModel()
            model_server.setRootPath(QDir.homePath())
        else:
            model_server = server

        self.view_host = QTreeView()
        self.setAnimated(True)
        self.view_host.setModel(model_host)
        self.view_server = QTreeView()
        self.view_server.setModel(model_server)

        self.sendButton = QPushButton("Download")
        self.quitButton = QPushButton("Quit")
        self.connect(self.sendButton, SIGNAL("clicked()"), self.click)
        self.connect(self.quitButton, SIGNAL("clicked()"), self.quit_clicked)

        self.MyLabel = QLabel("Your Computer: %s" % self.my_ip_address)
        self.TheirLabel = QLabel("Server: %s" % self.target_ip)

        self.leftside = QWidget()
        leftlayout = QVBoxLayout()
        self.leftside.setLayout(leftlayout)
        leftlayout.addWidget(self.MyLabel)
        leftlayout.addWidget(self.view_host)


        self.rightside = QWidget()
        rightlayout = QVBoxLayout()
        self.rightside.setLayout(rightlayout)
        rightlayout.addWidget(self.TheirLabel)
        rightlayout.addWidget(self.view_server)


        self.treeSplitter = QSplitter(Qt.Horizontal)
        self.ButtonSplitter = QSplitter(Qt.Horizontal)
        self.mainSplitter = QSplitter(Qt.Vertical)
        self.treeSplitter.addWidget(self.leftside)
        self.treeSplitter.addWidget(self.rightside)
        self.ButtonSplitter.addWidget(self.sendButton)
        self.ButtonSplitter.addWidget(self.quitButton)
        self.mainSplitter.addWidget(self.treeSplitter)
        self.mainSplitter.addWidget(self.ButtonSplitter)

        self.setCentralWidget(self.mainSplitter)

        self.resize(800, 480)

    def click(self):
        print self.target_ip

    def quit_clicked(self):
        self.close()

    def get_ip(self):
        config = ConfigWindow(self)
        if config.exec_():
            self.target_ip = config.get_ip_address()[1]
            self.my_ip_address = config.get_ip_address()[0]

    def connect_server(self):
        """connects to server and gets file tree"""
       
        return


def main():
    """runs program"""
    app = QApplication(sys.argv)
    form = MainForm()
    form.show()
    app.exec_()

main()


def send_struct_request():
    """sends requestfor server file structure"""



def server_file_struct():
    """recieves request for file structure pickles it and sends that"""
    model_server = QFileSystemModel()
    model_server.setRootPath(QDir.homePath())
    #do something to extract the info -- Arjun is looking for it now 
    serv_str = #thing
    pick_serv = pickle.dumps(serv_str)
    return pick_serv




def unpickle(pick_serv):
    """unpickles and reconstructs the FileSystemModel"""
    loaded = pickle.loads(pick_serv)
    #thing that Arjun is looking up to reassemble the loaded string
    return struct_server #a QFileSystemModel type 
 

"""
sudo-code
Server:
    recieves request for file structure
    gets QFileSystemModel
    turns FileSystemModel into data
    pickles data
    send picklecd

client:
    sends requestfor server file structure

    recieves pickle
    unpickles
    reconstructs 
"""
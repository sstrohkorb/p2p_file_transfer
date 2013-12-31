# -*- coding: utf-8 -*-
import sys
import socket
import subprocess
import time
import shutil
from os import remove
from PyQt4.QtCore import *
from PyQt4.QtGui import *


class MainForm(QDialog):
    """main window for file tree test"""
    def __init__(self, parent=None, server=None):
        """initializes main window and tree w/ splitter"""
        super(MainForm, self).__init__(parent)
        self.my_ip_address = self.get_local_ip_address()
        iplabel = QLabel("IP address")
        self.ipedit = QLineEdit("")
        youriplabel = QLabel("Your IP address:")
        yourip = QLabel(self.my_ip_address)
        space = QLabel(" ")
        file_label = QLabel("Desired File:")
        self.file_path = QLineEdit("")
        self.sendButton = QPushButton("Download")
        self.quitButton = QPushButton("Quit")
        self.connect(self.sendButton, SIGNAL("clicked()"), self.click)
        self.connect(self.quitButton, SIGNAL("clicked()"), self.quit_clicked)


        grid = QGridLayout()
        grid.addWidget(youriplabel, 0, 0)
        grid.addWidget(yourip,0,1)
        grid.addWidget(iplabel, 1, 0)
        grid.addWidget(self.ipedit, 1, 1)
        grid.addWidget(file_label,2,0)
        grid.addWidget(self.file_path,2,1)
        grid.addWidget(space,3,0)
        grid.addWidget(self.sendButton,4,1)
        grid.addWidget(self.quitButton,4,2)

        self.setWindowTitle("Enter Server IP")
        self.setLayout(grid)

        # self.mainSplitter = QSplitter(Qt.Vertical)
        # self.mainSplitter.addWidget(grid)
        self.resize(600, 300)
        # self.setCentralWidget(self.mainSplitter)


    def click(self):
        self.dest = str("/home/alettyo/sashe_downloads/")

        server_ip = self.ipedit.text()
        wanted_file = self.file_path.text()
        print "Server", server_ip
        print "file wanted:", wanted_file

        # fd = open("/home/alettyo/Dropbox/softsys/str_size.txt", "w")
        # fd.write(str(len("download "+wanted_file)+1))
        # fd.close()

        cli = subprocess.Popen(["./serv_cli/client", server_ip, wanted_file], stdin=subprocess.PIPE)
        "print done cli"
        time.sleep(8)
        cli.terminate()
        try:
            remove(str(self.dest+wanted_file))
        except:
            pass
        shutil.move(str("./"+wanted_file), self.dest)
        return server_ip, wanted_file


    def quit_clicked(self):
        self.close()

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


def main():
    """runs program"""
    app = QApplication(sys.argv)
    form = MainForm()
    form.show()
    app.exec_()
    print "running"

main()




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
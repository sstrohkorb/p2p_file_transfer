import sys
import socket 
from PyQt4.QtCore import *
from PyQt4.QtGui import *

print "flag1"

model_host = QFileSystemModel()

print "flag2"

model_host.setRootPath(QDir.homePath())

print "flag3"

print model_host

print "flag4"

somt = model_host.mimeData()

print somt
import socket
 
def get_local_ip_address(target):
  ipaddr = ''
  try:
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.connect((target, 8000))
    ipaddr = s.getsockname()[0]
    s.close()
  except:
    pass
 
  return ipaddr 

print get_local_ip_address('mrwiki.olin.edu')
print type(get_local_ip_address('mrwiki.olin.edu'))

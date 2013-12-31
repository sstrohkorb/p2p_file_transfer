"""
Does not work unless your firewall is disconnected:
https://help.ubuntu.com/community/UFW
"""
from __future__ import print_function
#import server
import client

# our IP addresses - to be updated each time
Klutzy_ip = 	"10.41.24.167"
Burpy_ip = 		"10.41.24.128"
SquigglyD_ip = 	"10.41.88.7"
Arjun_ip = 		"10.41.88.2"
Home_ip = 		"127.0.0.1"

"""
struct Connection *new_Connection() {
    return (Connection *) calloc(1,sizeof(struct Connection));
}
void delete_Connection(struct Connection *obj) {
    free(obj);
}
"""

c = client.Connection();
client.make_connection(c, Home_ip);
file_name = "download example.txt";
client.transfer_file(c, file_name);
client.close_connection(c);

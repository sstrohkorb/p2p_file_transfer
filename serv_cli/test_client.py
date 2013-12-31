import client

IP = "127.0.0.1";
file_name = "download example.txt";

c = client.Connection();
client.make_connection(c, IP);
client.transfer_file(c, file_name);

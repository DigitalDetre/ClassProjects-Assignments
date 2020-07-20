import socket
import sys
import os

try:
	# Creates the socket
	s = socket.socket()
except socket.error as err:
	print "Socket creation failed with error %s" %(err)

# Sets the port number
port = 45000

try:
	ip = socket.gethostbyname('eustis.eecs.ucf.edu')
except socket.gaierror:
	# this means could not resolve the host
	print "There was an error getting the IP"
	sys.exit()

# Binds to the port
s.connect((ip, port))
flag = raw_input("Do you want send a file to the server? Input[Yes/No]\n")
filename = raw_input("Please input a filename to receive from or write to the server.\n")

s.send(flag)

if flag == "Yes":
	# Says what mode the server is on
	print s.recv(1024)
	s.send(filename)

	# Tells if the server has the file or not
	flag2 = s.recv(1024)
	if flag2 == "Ok":
		try:
			f = open(filename, 'rb')
		except IOError:
			print "Could not read file: ", filename
			sys.exit()

		line = 1

		while line:
			line = f.read(1024)
			s.send(line)
		f.close()
		print "File has been sent to the server"
	else:
		print "File exists on the server"
else:
	# Says what mode the server is on
	print s.recv(1024)

	s.send(filename)

	# Prints if the file exists or not
	print s.recv(1024)

	with open('received_file.txt', 'wb') as file:
		while True:
			# Prints the data from the server
			data = s.recv(1024)
			if not data:
				break
			print(data)
			file.write(data)

	# Closes the file
	file.close()

# Closes the connection
s.close()

print "Exiting Client.py"
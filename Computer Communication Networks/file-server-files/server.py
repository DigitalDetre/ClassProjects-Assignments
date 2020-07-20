import socket
import sys
import os

DEBUG = 1

byte = input("Please input the byte range.\n")

try:
	# Creates the socket
	s = socket.socket()
except socket.error as err:
	print "Socket creation failed with error %s" %(err)

try:
	ip = socket.gethostbyname('eustis.eecs.ucf.edu')
except socket.gaierror:
	# this means could not resolve the host
	print "There was an error getting the IP"
	sys.exit()

# Sets the port number
port = 45000

# Binds to the port
s.bind(('', port))

s.listen(5)

while True:
	client, addr = s.accept()

	print "Got connection from", addr
	flag = client.recv(1024)

	if flag == "Yes":
		client.send("Server is in writing mode")
		filename = client.recv(1024)
		try:
			file = open(filename, 'rb')
			client.send('Not ok')
			file.close()
		except IOError:
			client.send('Ok')
			with open('server_received_file.txt', 'wb') as file:
				while True:
					# Writes the data from the client
					data = client.recv(1024)
					if not data:
						break
					file.write(data)
			file.close()
	else:
		client.send("Server is in receiving mode")
		filename = client.recv(1024)
		try:
			f = open(filename, 'rb')
			client.send("File does exist")
		except IOError:
			print "Could not read file:", filename
			client.send("File does not exist")
			sys.exit()

		# Gets the total size of the file
		filesize = os.path.getsize(filename)

		if filesize < 10:
			percent = filesize
		else:
			percent = filesize * 0.1

		if DEBUG:
			print "Sending", filename, "to", addr

		line = 1

		counter = 0

		if byte >= filesize:
			if filesize < 10:
				line = f.read(int(percent))
				client.send(line)
				for x in range(0, 10):
					if DEBUG:
						counter += 1
						if counter > 0 and counter <= 10:
							print ("Sent %d%% of %s" % (counter * 10, filename))
			else:
				while line:
					line = f.read(int(percent))
					client.send(line)
					if DEBUG:
						counter += 1
						if counter > 0 and counter <= 10:
							print ("Sent %d%% of %s" % (counter * 10, filename))
		else:
			if byte < 10:
				percent = byte
				line = f.read(int(percent))
				client.send(line)
				for x in range(0, 10):
					if DEBUG:
						counter += 1
						if counter > 0 and counter <= 10:
							print ("Sent %d%% of %s" % (counter * 10, filename))
			else:
				percent = byte * 0.1
				for x in range(0, 10):
					line = f.read(int(percent))
					client.send(line)
					if DEBUG:
						counter += 1
						if counter > 0 and counter <= 10:
							print ("Sent %d%% of %s" % (counter * 10, filename))
				
		f.close()

		if DEBUG:
			print "Finished sending", filename, "to", addr

	print "Closing connection to client"
	client.close()
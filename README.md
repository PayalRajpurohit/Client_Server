In this program we have implemented a single service broker, multiple service
providers, and a single service requister. 

The Service Broker:

This program will be a concurrent server, one process of this server will 
will accept connections from the service requester to tell the service 
requester about the available services and where are they located. 

Each service will be represented by an integer that identifies the service, 
a port number, and an IP address. For simplicity's sake we will keep the IP 
address as the loopback IP addres 127.0.0.1 which means that all processes 
will run on the local machine, but the port number is going to change. So, 
simply you need to provide two integers to the service requester.


The other process will take care of generating the services and their port 
numbers (since the IP address is already known). There's no communication here
with a service provider needed, you are just going to simulate this by having
this service broker process randomly and every 15 seconds generate a random
number between 1 and 100 that represents the service and assign it a unique
port number. In addition to generating one number every 15 seconds, every
30 seconds you will remove the earliest number that you generated from the
list of available services. You need to keep in mind that you may randomly 
generate duplicates, so you don't want to keep duplicates in the list of 
services availabe. 

The Service Requester:
This one is an interactive client program, that is a client of the broker,
and all it does, based on user's input, checks to see if a particular service
is available at the broker and where is it available. If the broker responds
negatively that the broker doesn't have that service, then the requester
goes back and checks for another service until it finds one (in this case
the requester received a message from the broker containing a service number
and a port number). 

Once the service requester receives a service number and a port number, then 
you make the request from the service provider server.

The requester contacts the broker first, and upon
positive response from the broker, it contacts the service provider. 

The service provider:
Once the requester got a positive response from the service broker, then you 
need to manually run the service provider program that will run on the same 
machine and open the port provided and waits for a request from the service
requester. This request is a very simple request, in the form of a question:
can you provide this service, and the answer should be yes from the service
provider if everything is OK, otherwise no, I can't. 


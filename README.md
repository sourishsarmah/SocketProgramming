# Socket Programming

##


### The repository contains two directories -  
* Server - Contains all the server side script
* Client - Contains all the client side script


##  Examples -

1. Program to run TCP client and server socket programs where client first says "Hi" and in response server says "Hello".

    Files -  
    - ./server/tcp_server  
    - ./client/tcp_client  

2. Program using TCP socket to implement the following:
    1. Server maintains records of fruits in the format: fruit-name quantity Last-sold (server timestamp).
    2. Multiple client purchase the fruits one at a time.
    3. The fruit quantity is updated each time any fruit is sold.
    4. Show warning messages to the client if the quantity requested is not available.
    5. Display the customer ids <IP, port> who has done transactions already. This list should be updated in the server everytime a transaction occurs.
    6. The total number of unique customers who did some transaction will be displayed to the customer everytime.

    Files -  
    - ./server/shop_server  
    - ./client/shop_client  

3. Program to run UDP client and server socket programs where client first says "Hi" and in response server says "Hello".

    Files -  
    - ./server/udp_server  
    - ./client/udp_client  

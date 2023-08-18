To fail the localhost (127.0.0.1) with 100% packetloss, I made the firewal reject any input connection to the localhost. This can be done by running the command `sudo iptables -A INPUT 
-p icmp --icmp-type echo-request -s 127.0.0.1 -j DROP`. This will reject any input connection to the localhost. To test this I ran the command `ping 127.0.0.1` which returned the below image:

![plot](./pingfail.png)

To restore the localhost I ran the command `sudo iptables -D INPUT -p icmp --icmp-type echo-request -s 127.0.0.1 -j DROP` which will remove the rule that rejects any input connection to the localhost. To test this I ran the command `ping 127.0.0.1` which returned the below image:

![plot](./pingpass.png)
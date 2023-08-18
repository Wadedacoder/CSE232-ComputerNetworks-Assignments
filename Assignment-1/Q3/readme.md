for part a:

The total hops are 10. One intermediatery router is _gateway(192.168.232.2). The average latency was is 0.506ms. The other is del11s22-in-f14.1e100.net(142.250.206.174). The average latency was 5.802ms. Rest of the routers are not shown in the output of the command `traceroute www.google.com -I`.

The output of the command `traceroute www.google.com -I` is shown below:

![plot](./Q3/routera.png)

for part b:

After pinging the URL "www.google.com" 50 times, I got an average of 9.009 ms. The exact output is shown below:

![plot](./Q3/pingb.png)

for part c:
Adding up all intermediate router latencies, we get 0.506ms + 5.802ms = 6.308ms. This is less than the average latency of pinging the URL "www.google.com" 50 times which is 9.009 ms. This are similar but dont exactly match due to a variety of network factors such as congestion. We also have a very small traceroute sample size of 1.

for part d:
Maximum of all intermediate router latencies is 5.802ms. This is less than the average latency of pinging the URL "www.google.com" 50 times which is 9.009 ms. This is because the latency of any one intermediate router will be less than all the intermediate routers.

for part e:
The multiple entries in the traceroute output are due to the fact that the packets are being routed through different paths. This is because the routers are using different routing algorithms to route the packets. The routers are using different routing algorithms because they are different routers and they are using different routing algorithms to route the packets.

for part f:
The average latency is 329.266 ms. The output of the command `ping stanford.edu -c 50` is shown below:

![plot](./pings.png)

for part g:
The number of hops to stanford.edu is 27. This is much lower than google.com's 10 hops.  The output of the command `traceroute stanford.edu -I` is shown below:

![plot](./routers.png)

for part h:
The latency difference between stanford.edu and google.com is 329.266 ms - 9.009 ms = 320.257 ms. This is due to stanford.edu being farther away from my location than google.com. This is because the packets have to travel a longer distance to reach stanford.edu than google.com. This is also leads to the higher number of hops to stanford.edu than google.com.
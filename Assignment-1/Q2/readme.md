For part (a):

An authoritative answer is a response we get directly from the primary DNS server holding the master copy of the zone file.

To recieve an authorative answer we first must find the primary DNS server for the domain we are looking for. We can do this by using the `nslookup` command. For example, if we want to find the primary DNS server for `google.com` we can run the command `nslookup -type=soa google.com` which will return the primary DNS server for `google.com` which is `ns1.google.com`. 

Now that we have the primary DNS server for `google.com` we can run the command `nslookup google.com ns1.google.com` which will return an authorative answer for `google.com` which is in the image below:

![plot](./nslookup.png)

for part (b):

Time to live of google.com DNS is 5 seconds. It will then be 

![plot](./ttl.png)

Sources:

https://www.linode.com/docs/guides/how-to-use-nslookup-command/

https://www.baeldung.com/cs/dns-authoritative-server-ip#:~:text=An%20authoritative%20answer%20is%20a,copy%20of%20the%20zone%20file.&text=It%20gives%20us%20the%20addresses,208.238.

https://www.howtouselinux.com/post/dns-ttl#:~:text=The%20best%20way%20to%20check,is%20available%20on%20most%20systems.
import time
from scapy.all import IP, UDP, Raw, send

dest_ip = "127.0.0.1"

#list of packets to send with src and dest
packets = [(3333, 3334, b"meow"), (3334, 3335, b"meow meow"), (3335, 3336, b"rawr"), (3336, 3337, b"A" * 100), (3337, 3338, b"meow meow meow meoww~"), (3338, 3339, b"meow meow meow meow meow...")]

for i, (sport, dport, payload) in enumerate(packets, start=1):
   #build packet as IP layer / UDP layer / Raw payload
   pkt = IP(dst=dest_ip) / UDP(sport=sport, dport=dport) / Raw(load=payload)
   send(pkt) #send packet
   time.sleep(0.1) #small delay so wireshark can capture each packet clearly
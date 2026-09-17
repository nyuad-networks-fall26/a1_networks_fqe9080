# UDP Reader

Please consult brightspace for assignment description.
In effect, you will need to:
- Edit `udp_reader.c` file with correct code to read any PCAP file that has UDP packets.
- Edit `generator.py` file with correct code to generate UDP packets as per the assignment description.
- Replace `sample.pcap` file with the file you generated using `generator.py` and wireshark (as shown during the lab).

## Using the Makefile

`udp_reader.c` is expected to compile without issues while using the following flags: `-Wall -Wextra -Werror --std=c2x`. 
A Makefile using these flags has been provided to you. You can use `make` as a short-hand to compile your program.

## Reference PCAP files
`/references` folder has a couple pcap files that you can use during testing.
However, note that you are required to produce a `sample.pcap` of your own as part of the submission.

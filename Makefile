udp_reader: udp_reader.c
	gcc -Wall -Wextra -Werror --std=c2x $^ -o $@

clean:
	rm -rf udp_reader

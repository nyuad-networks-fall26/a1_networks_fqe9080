#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <arpa/inet.h>

//struct to hold udp header fields
struct udp_header{
    uint16_t src_port;
    uint16_t dst_port;
    uint16_t length;
    uint16_t checksum;
};

int main(int argc, char *argv[]){
    //ceck command line args
    if (argc != 2) {
        fprintf(stderr, "Missing pcap file argument\n");
        return EXIT_FAILURE;
    }

    //open pcap file
    FILE *fp = fopen(argv[1], "rb");
    if (fp == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    //skip 24 byte pcap global header
    if (fseek(fp, 24, SEEK_SET) != 0){
        perror("fseek");
        fclose(fp);
        return EXIT_FAILURE;
    }

    //loop over every packet in file
    uint8_t record_header[16];

    while (fread(record_header, 1, 16, fp) == 16){
        //extract incl_len (its little endian)
        uint32_t incl_len;
        memcpy(&incl_len, record_header + 8, sizeof(incl_len));
        //allocate buffer for packet data
        uint8_t *packet = malloc(incl_len);
        if (packet == NULL){
            perror("malloc");
            fclose(fp);
            return EXIT_FAILURE;
        }

        //read packet data
        if (fread(packet, 1, incl_len, fp) != incl_len){
            fprintf(stderr, "Error: failed to read packet data\n");
            free(packet);
            fclose(fp);
            return EXIT_FAILURE;
        }
        //locate upd header
        uint8_t *udp_start = packet + 14 + 20; //skip ethernet and ip headers

        //copy upd header into struct
        struct udp_header udp;
        memcpy(&udp, udp_start, 8);

        //convert from network byte order (big-endian) to host order
        udp.src_port = ntohs(udp.src_port);
        udp.dst_port = ntohs(udp.dst_port);
        udp.length= ntohs(udp.length);
        udp.checksum = ntohs(udp.checksum);

        //print four udp header fields
        printf("Src Port: %u\n", udp.src_port);
        printf("Dst Port: %u\n", udp.dst_port);
        printf("Length: %u\n", udp.length);
        printf("Checksum: 0x%04x\n", udp.checksum);

        //print payload
        uint16_t payload_len = udp.length - 8;
        uint8_t *payload = udp_start + 8;

        for (uint16_t i = 0; i < payload_len; i++){
            if (isprint(payload[i])) {
                putchar(payload[i]);
            } else {
                putchar('.');
            }
        }
        putchar('\n');

        //print separator
        printf("==================================\n");
        free(packet);
    }

    //close file and exit
    fclose(fp);
    return EXIT_SUCCESS;
}
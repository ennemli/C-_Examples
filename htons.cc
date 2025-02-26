#include <arpa/inet.h>
#include <stdio.h>

int main() {
  uint16_t port_network = htons(8080);      // Host to Network
  uint16_t port_host = ntohs(port_network); // Network to Host

  printf("Network Order: %u\n", port_network);
  printf("Host Order: %u\n", port_host);

  return 0;
}

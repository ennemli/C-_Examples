#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <vector>

// Structure to represent UDP packet
struct UDPPacket {
  struct PseudoHeader {
    uint32_t src_ip;
    uint32_t dest_ip;
    uint8_t zeros;
    uint8_t protocol;
    uint16_t udp_length;
  } pseudo_header;

  struct UDPHeader {
    uint16_t src_port;
    uint16_t dest_port;
    uint16_t length;
    uint16_t checksum;
  } udp_header;

  std::vector<uint8_t> data;
};

// Calculate UDP checksum
uint16_t calculate_checksum(const UDPPacket &packet) {
  // First, calculate total size needed for checksum calculation
  size_t total_size = sizeof(UDPPacket::PseudoHeader) +
                      sizeof(UDPPacket::UDPHeader) + packet.data.size();

  // Ensure we have even number of bytes (pad with zero if needed)
  if (total_size % 2)
    total_size++;

  // Create buffer for checksum calculation
  std::vector<uint8_t> buffer(total_size, 0);
  size_t offset = 0;

  // Copy pseudo header
  memcpy(buffer.data(), &packet.pseudo_header, sizeof(UDPPacket::PseudoHeader));
  offset += sizeof(UDPPacket::PseudoHeader);

  // Copy UDP header (with checksum field set to 0)
  UDPPacket::UDPHeader header = packet.udp_header;
  header.checksum = 0;
  memcpy(buffer.data() + offset, &header, sizeof(UDPPacket::UDPHeader));
  offset += sizeof(UDPPacket::UDPHeader);

  // Copy data
  memcpy(buffer.data() + offset, packet.data.data(), packet.data.size());

  // Calculate checksum
  uint32_t sum = 0;
  uint16_t *ptr = reinterpret_cast<uint16_t *>(buffer.data());

  // Sum up 16-bit words
  for (size_t i = 0; i < total_size / 2; i++) {
    sum += ntohs(ptr[i]);
    // Add carry if it exists
    if (sum >> 16) {
      sum = (sum & 0xFFFF) + (sum >> 16);
    }
  }

  // Take one's complement
  return ~sum & 0xFFFF;
}

// Verify checksum
bool verify_checksum(const UDPPacket &packet) {
  uint16_t received_checksum = packet.udp_header.checksum;
  uint16_t calculated_checksum = calculate_checksum(packet);
  return received_checksum == calculated_checksum;
}

int main() {
  // Create sample UDP packet
  UDPPacket packet;

  // Fill pseudo header
  packet.pseudo_header.src_ip = inet_addr("192.168.1.1");
  packet.pseudo_header.dest_ip = inet_addr("192.168.1.2");
  packet.pseudo_header.zeros = 0;
  packet.pseudo_header.protocol = 17; // UDP protocol number

  // Fill UDP header
  packet.udp_header.src_port = htons(12345);
  packet.udp_header.dest_port = htons(54321);

  // Sample data
  const char *message = "Hello, UDP!";
  packet.data = std::vector<uint8_t>(message, message + strlen(message));

  // Set packet lengths
  packet.udp_header.length =
      htons(sizeof(UDPPacket::UDPHeader) + packet.data.size());
  packet.pseudo_header.udp_length = packet.udp_header.length;

  // Calculate and set checksum
  packet.udp_header.checksum = calculate_checksum(packet);
  std::cout << "Original checksum: 0x" << std::hex << packet.udp_header.checksum
            << std::endl;

  // Verify original packet
  std::cout << "Original packet verification: "
            << (verify_checksum(packet) ? "Valid" : "Invalid") << std::endl;

  // Simulate corruption by changing one byte in data
  if (!packet.data.empty()) {
    packet.data[0] ^= 1; // Flip one bit in first byte
  }

  // Verify corrupted packet
  std::cout << "Corrupted packet verification: "
            << (verify_checksum(packet) ? "Valid" : "Invalid") << std::endl;

  return 0;
}

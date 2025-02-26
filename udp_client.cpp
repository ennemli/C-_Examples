#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define MAXLINE 1024

int main() {
  int sockfd;
  char buffer[MAXLINE];
  struct sockaddr_in servaddr;

  // Creating socket file descriptor
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  memset(&servaddr, 0, sizeof(servaddr));

  // Filling server information
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
  servaddr.sin_addr.s_addr = INADDR_ANY;

  int n;
  socklen_t len;

  std::cout << "Enter message: ";
  std::string message;
  std::getline(std::cin, message);

  sendto(sockfd, message.c_str(), message.length(), MSG_CONFIRM,
         (const struct sockaddr *)&servaddr, sizeof(servaddr));
  std::cout << "Message sent." << std::endl;

  n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL,
               (struct sockaddr *)&servaddr, &len);
  buffer[n] = '\0';
  std::cout << "Server: " << buffer << std::endl;

  close(sockfd);
  return 0;
}

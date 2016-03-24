#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <malloc.h>
#include <string.h>

#define SERVER_PORT 3333
#define SERVER_IP "127.0.0.1"


int main()
{
  struct sockaddr_in addr, server_addr;
  int c_fd, pack_len, max_sends, srv_addr_len, recv_buf_len;
  char *ping_pack = NULL;
  char resp[1024] = {0,};

  printf("Welcome to client UDP socket \n");

  if ((c_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
  {
     printf("error in socket creation");
     return -1;
  }
  memset(&addr, 0x00, sizeof(struct sockaddr_in));

  addr.sin_family = AF_INET;
  addr.sin_port = htons(SERVER_PORT);
  addr.sin_addr.s_addr = inet_ntoa(SERVER_IP);
  if (inet_aton(SERVER_IP, &addr.sin_addr)==0) {
    printf("inet_aton() failed\n");
    return 1;
  }
 
  ping_pack = (char*) malloc(8);

  if(!ping_pack)
  {
    printf("no memory\n");
    return -1;
  }
  pack_len = 0;
  ping_pack[pack_len++] = 0; //request
  ping_pack[pack_len++] = 1; //ping packet

  max_sends = 0;
  while(max_sends < 5)
  {
     if(sendto(c_fd, ping_pack, pack_len, 0, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1)
     {
       printf("error sending [%d] time \n", max_sends);
     }
     printf("send successfull\n");
     if (recvfrom(c_fd, resp, 1024, 0, (struct sockaddr *)&server_addr, &srv_addr_len) == -1)
     {
       printf("error receiving [%d] time \n", max_sends);
     }
     printf("send & recv successfull\n");

     max_sends++;
  }

 free((void*) ping_pack);


  return 0;

}


#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <malloc.h>
#include <string.h>

#define SERVER_PORT 3333
#define BUFFLEN 1500


char *parse_generate_buffer(char *b, int b_len, int *snd_buf_len)
{
  char *p = NULL;
  int p_len = 0;
  int b_index = 0;
  if (b_len < 2)
  {
    printf("need more buffer \n");
    return NULL;
  }


  //get packet type ==> 0 req; 1 resp;
  if(b[b_index] == 0)
  {
    b_index++;

    printf("Packet type == req");
    p = (char*)malloc(BUFFLEN);
  
    if (p == NULL)
    {
      printf("Error in memory allocation");
      return NULL;
    }

    p[p_len] = 1;//packet type: response
    p_len++;

    if (b[b_index] == 1) //ping req
    {
      char pong[] = "PONG";
      p[p_len] = 1; //ping resp
      p_len++;
      p[p_len] = strlen(pong); //ping resp
      p_len++;

      memcpy(p + p_len, pong, strlen(pong));
      p_len+=strlen(pong);

    }

  }
  else if (b[b_index] == 1)
  {
    printf("Packet type == resp");
    return NULL;
  }
  else
  {
    printf("not a valid packet type");
  }
  *snd_buf_len = p_len;
  return p;
}

int main ()
{
  
  struct sockaddr_in addr, cli;
  int s_fd, cli_len, recv_buf_len;
  char buf[BUFFLEN];

  if ((s_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
  {
     printf("error in socket creation");
     return -1;
  }

  memset(&addr, 0x00, sizeof(struct sockaddr_in));

  addr.sin_family = AF_INET;
  addr.sin_port = htons(SERVER_PORT);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(s_fd,(struct sockaddr *) &addr, sizeof(struct sockaddr_in)) == -1)
  {
     printf("error in bind");
     return -1;
  }
  
  printf("socket bind to [%d] successfull\n", SERVER_PORT);
  while(1)
  {
    char *cli_data = NULL;
    int send_buff_len = 0;
    recv_buf_len = 0;
    if((recv_buf_len = recvfrom(s_fd, buf, BUFFLEN, 0, (struct sockaddr *)&cli, &cli_len)) == -1)
    {
      printf("error in recv from");
      return -1;
    }
    printf("data received of len [%d] \n", recv_buf_len);

    cli_data = parse_generate_buffer(buf, recv_buf_len, &send_buff_len);
    if(cli_data)
    {
      if(sendto(s_fd, cli_data, send_buff_len, 0, (struct sockaddr *)&cli, cli_len) == -1)
      {
        printf ("Error in SENDTO");
        return -1;
      }
      free ((void*) cli_data);
    }

  }

  return 0;
}




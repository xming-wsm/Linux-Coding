#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

#define BUF_SIZE 1024
#define EPOLL_SIZE 50

void error_msg(char* msg) {
  fputs(msg, stderr);
  fputc('\n', stderr);
  exit(1);
}



int main(int argc, char *argv[])
{
  int serv_sock, clnt_sock;
  struct sockaddr_in serv_adr, clnt_adr;
  socklen_t clnt_adr_size;
  int str_len;
  char msg[BUF_SIZE];

  struct epoll_event *ep_events;
  struct epoll_event event;
  int epfd, event_cnt;

  if (argc != 2) {
    printf("Usage: %s <port>\n", argv[0]);
    exit(1);
  }

  serv_sock = socket(PF_INET, SOCK_STREAM, 0);
  memset(&serv_adr, 0, sizeof(serv_adr));
  serv_adr.sin_family = AF_INET;
  serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_adr.sin_port = htons(atoi(argv[1]));

  int sock_opt = 1;
  setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &sock_opt, sizeof(sock_opt));

  if (bind(serv_sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1) {
    error_msg("bind() error");
  }

  if (listen(serv_sock, 5) == -1) {
    error_msg("listen() error");
  } else {
    fputs("Server start sucessfully\n", stdout);
  }

  epfd = epoll_create(EPOLL_SIZE);
  event.events = EPOLLIN;
  event.data.fd = serv_sock;
  ep_events = malloc(sizeof(struct epoll_event) * EPOLL_SIZE);
  epoll_ctl(epfd, EPOLL_CTL_ADD, serv_sock, &event);


  while (1) {
  
    event_cnt = epoll_wait(epfd, ep_events, EPOLL_SIZE, -1);
    if (event_cnt == -1) {
      fputs("epoll_wait() error\n", stderr);
      break;
    }

    for (int i = 0; i < event_cnt; i ++) {
      if (ep_events[i].data.fd == serv_sock) {
        
        clnt_adr_size = sizeof(clnt_adr);
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_adr, &clnt_adr_size);
        event.events = EPOLLIN;
        event.data.fd = clnt_sock;
        epoll_ctl(epfd, EPOLL_CTL_ADD, clnt_sock, &event);
        printf("Connected client: %d\n", clnt_sock);
      } else {

        str_len = read(ep_events[i].data.fd, msg, BUF_SIZE);
        if (str_len == 0) {
          // close request...
          epoll_ctl(epfd, EPOLL_CTL_DEL, ep_events[i].data.fd, NULL);
          printf("Close client: %d\n", ep_events[i].data.fd);
          close(ep_events[i].data.fd);
        } else {
          // read data...
          write(ep_events[i].data.fd, msg, str_len);
        }

      }
    }
  }

  close(serv_sock);
  close(epfd);
  return EXIT_SUCCESS;
}

































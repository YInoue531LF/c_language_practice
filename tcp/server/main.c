#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(){
  int sock;
  int sock1;
  socklen_t len;
  struct sockaddr_in addr;
  struct sockaddr_in client;
  
  char txt[] = {"HELLO from Server"};

  if(sock > 0){
    close(sock);
  }

  /* socketの作成 */
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if(sock < 0){
    printf("socket failed\n");
    return 1;
  }

  /* 通信ポート・アドレスの設定 */
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8000);
  addr.sin_addr.s_addr= INADDR_ANY;

  /* ソケットにアドレスを結びつける */
  if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0){
    printf("bind failed\n");
    return 1;
  }

  /* コネクト要求をいくつまで待つかを設定 */
  if(listen(sock, 5) < 0){
    printf("listen failed\n");
    close(sock);
    return 1;
  }

  if(sock1 > 0){
    close(sock1);
  }
  
  len = sizeof(client);

  /* コネクト要求を待つ */
  if((sock1 = accept(sock, (struct sockaddr *)&client, &len)) < 0){
    printf("accept failed\n");
    close(sock);
    return 1;
  }

  printf("--- server info ---\n");
  printf("ip_address %s, \nport %d\n",
          inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));

  printf("--- client info ---\n");
  printf("ip_address %s, \nport %d\n ",
          inet_ntoa(client.sin_addr), ntohs(client.sin_port));

  send(sock1, txt, sizeof(txt), 0);

  close(sock1);
  close(sock);

  printf("\nmain finish...\n");
  return 0;
}

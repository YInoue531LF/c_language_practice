#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
  int sock;
  struct sockaddr_in server;
  int r;
  char buf[32];

  /* ソケットの作成 */
  if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    printf("socket failed\n");
    return 1;
  }

  server.sin_family = AF_INET;
  server.sin_port = htons(8000);
  server.sin_addr.s_addr = inet_addr("127.0.0.1");

  /* サーバに接続 */
  if((connect(sock, (struct sockaddr *)&server, sizeof(server))) < 0){
    printf("connect failed\n");
    close(sock);
  }
  
  /* サーバからデータを受信 */
  memset(buf, 0, sizeof(buf));
  r = read(sock, buf, sizeof(buf));

  printf("受信したメッセージ：%s\n", buf);
  printf("文字数：%d\n", r);


  /* socketの終了 */
  close(sock);

  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <netdb.h>
#include <assert.h>

#define ECHO_LEN	1025
#define MAXBUF 		  1024
#define MAXEPOLLSIZE 	100
#define NI_MAXHOST  	1025
#define NI_MAXSERV	  32

static unsigned int myport = 1234;

// setnonblocking - 设置句柄为非阻塞方式
int setnonblocking(int sockfd)
{   
    // fcntl 一种读写锁的拓展形式
    // 文件记录锁是fcntl函数的主要功能。记录上锁粒度是整个文件大小时，是文件上锁
    // 记录锁：实现只锁文件的某个部分，并且可以灵活的选择是阻塞方式还是立刻返回方式
    if (fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0)|O_NONBLOCK) == -1)
        return -1;
    
    return 0;
}

static void add_event(int epollfd,int fd,int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&ev);
}

static void delete_event(int epollfd,int fd,int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd,EPOLL_CTL_DEL,fd,&ev);
}

static void do_write(int epollfd,int fd,char *buf)
{
    int nwrite;
    nwrite = write(fd,buf,strlen(buf));
    if(nwrite == 1)
    {
        perror("write error :");
        close(fd);
        delete_event(epollfd,fd,EPOLLOUT);
    }
}

int udp_socket_connect(int epollfd,struct sockaddr_in *servddr)
{
    struct sockaddr_in my_addr, their_addr;
    int fd = socket(PF_INET,SOCK_DGRAM,0);

    // 设置socket 属性，端口可以重用
    int opt = SO_REUSEPORT;
    setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    setnonblocking(fd);
    bzero(&my_addr,sizeof(my_addr));
    my_addr.sin_family = PF_INET;
    my_addr.sin_port = htons(myport);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    if(bind(fd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr)) == -1)
    {
        perror("bind");
        exit(1);
    }
    else{
        printf("IP and port bind success\n");
    }   
    if(fd == -1) return -1;
    connect(fd,(struct sockaddr *)servddr,sizeof(struct sockaddr_in));
    add_event(epollfd,fd,EPOLLIN);

    return fd;

}

void msg_process(int epollfd,int fd)
{
    int nread = 0;
    char buf[MAXBUF];
    char type;

    nread = read(fd,buf,MAXBUF);
    buf[nread] = '\0';
    type = buf[0];

    if(type == 2)
    {
        printf("recv msg %s \n",buf+1);
        do_write(epollfd,fd,buf);
    }
    else{
        delete_event(epollfd,fd,EPOLLOUT);
		close(fd);
    }

}

void accept_client(int epollfd,int fd)
{
    struct sockaddr_storage client_addr;
    socklen_t addr_size = sizeof(client_addr);
    char buf[1024];
    int ret = recvfrom(fd,buf,1024,0,(struct sockaddr*)&client_addr,&addr_size);
    buf[ret] = '\0';
    char type = buf[0];
    char hbuf[NI_MAXHOST],sbuf[NI_MAXSERV];
    ret = getnameinfo((struct sockaddr *)&client_addr, addr_size, hbuf, sizeof(hbuf), \
		sbuf, sizeof(sbuf), NI_NUMERICHOST | NI_NUMERICSERV);
    
    printf("recvfrom client [%s,%s] : %d\n",hbuf,sbuf,buf[0]);

    if(type!=0)
    {
        return ;
    }
    int new_sock = udp_socket_connect(epollfd, (struct sockaddr_in*)&client_addr);
    buf[0] = 1;
    do_write(epollfd,new_sock,buf);

}

int main(int argc,char **argv)
{
    int listener,kdpfd,nfds, n , curfds;
    socklen_t len;
    struct sockaddr_in my_addr, their_addr;

    struct epoll_event ev;
    struct epoll_event events[MAXEPOLLSIZE];

    // 开启socket监听
    if((listener == socket(PF_INET,SOCK_DGRAM,0)) == -1 ) // socket 还是个系统调用 SOCK_DGRAM分是数据抱,是udp协议网络编程
    {   
        // 没有监听到
        perror("socket create failed !");
        exit(1);
    }
    else{
        printf("socket create  success \n");
    }

    /*设置socket属性，端口可以重用*/
    int opt = SO_REUSEADDR;
    setsockopt(listener,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    setnonblocking(listener);
    // 和memset 类似, 第一个参数指针，第二个需要清空的长度
    bzero(&my_addr,sizeof(my_addr));
    my_addr.sin_family = PF_INET;
    my_addr.sin_port = htons(myport);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    if(bind(listener,(struct sockaddr *)&my_addr,sizeof(struct sockaddr) ) == -1 )
    {
        perror("bind");
        exit(1);
    }
    else{
        // success 
        printf("IP and port bind success, port:%d \n", myport);
    }

    // bind 成功后
    /* 创建epoll 句柄，把监听socket 加入到 epoll集合里 */
    kdpfd = epoll_create(MAXEPOLLSIZE);
    len = sizeof(struct sockaddr_in);
    ev.data.fd = listener;
    ev.events = EPOLLIN | EPOLLET;
    if(epoll_ctl(kdpfd,EPOLL_CTL_ADD,listener,&ev) < 0 )
    {
        fprintf(stderr,"epoll set insertion error: df = %d \n",listener);
        return -1;
    }
    else{
        printf("listen socket added in  epoll success \n");
    }

    while(1)
    {
        /* 等待有事情发生 */
        nfds = epoll_wait(kdpfd,events,10000,-1);
        if(nfds == -1)
        {
            perror("epoll_wait");
            break;
        }
        /* 处理所有事情*/
        for(n = 0 ;n<nfds;++n)
        {   
            if(events[n].data.fd == listener)
            {
                // 刚开启连接
                accept_client(kdpfd,listener);
            }
            else{
                msg_process(kdpfd,events[n].data.fd);
            }


        }
                
    }
    close(listener);
    close(kdpfd);


    return 0;
}

//
//  main.c
//  machpractice
//
//  Created by Kevin Stubbings on 1/30/20.
//  Copyright © 2020 Kevin Stubbings. All rights reserved.
//
#include "mach_port.h"
#include <stdio.h>
#include <mach/mach.h>
#include <stdio.h>
#include <err.h>


struct integer_message
{
    mach_msg_header_t head;
    mach_msg_type_t type;
    int inline_integer;
};

void send_integer(mach_port_t destination, int i){
    kern_return_t err;
    struct integer_message message;
    
    message.head.msgh_bits=MACH_MSGH_BITS_REMOTE(MACH_MSG_TYPE_MAKE_SEND);
    message.head.msgh_size=sizeof(struct integer_message);
    message.head.msgh_local_port = MACH_PORT_NULL;
    message.head.msgh_remote_port = destination;
    
    message.type.msgt_name = MACH_MSGH_BITS_REMOTE(MACH_MSG_TYPE_MAKE_SEND);
    message.type.msgh_size = 32;
    message.type.msgt_number =1;
    message.type.msgt_inline = TRUE;
    
    err=mach_msg(&(message.head), MACH_SEND_MSG,message.head.msgh_size, 0, MACH_PORT_NULL, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
    
}
void recieve_integer(mach_port_t source, int *ip){
    kern_return_t err;
    struct integer_message message;
    err = mach_msg(&(message.head), MACH_RCV_MSG, 0, message.type.msgh_size,source, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL );
    
    *ip = message.inline_integer;
}
int main(void){
    int s_integer, r_integer;
    kern_return_t error;
    mach_port_t recv_port;
    mach_port_allocate(mach_task_self(), MACH_PORT_RIGHT_RECEIVE, &recv_port);
    if(err !=KERN_SUCESS){
        perror("error : could not allocate any port");
        exit(err);
    }
    send_integer(recv_port, s_integer);
    recieve_integer(recv_port, &r_integer);
    mach_port_deallocate(mach_task_self(),destination);
    return 0;
}

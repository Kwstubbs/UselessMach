//
//  mach_port.h
//  machpractice
//
//  Created by Kevin Stubbings on 1/31/20.
//  Copyright © 2020 Kevin Stubbings. All rights reserved.
//

#ifndef mach_port_h
#define mach_port_h
void send_integer(mach_port_t destination, int i);
void recieve integer(mach_port_t source, int *ip);
#endif /* mach_port_h */

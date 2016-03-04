/*
 * Copyright 2015 Emanuele Forestieri <forestieriemanuele@gmail.com>
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define byte char

static const char characters[] = "0123456789ABCDEF";


static inline byte countc(register char *s,  char c) /*count how many times there is c in the string s*/
{
    byte n=0;
    while(*s) if(*s++==c) n++;
    return n;
}
static bool checkpass(char *pass)
{
    /*Check the password, FUNCTIONS ORDER FOR SPEED*/

    /*There can be no more than two consecutive identical characters*/
//    for(byte i=0; i<8; i++)
//    {
//        if(pass[i]==pass[i+1])
//        {
//            i++;
//            if(pass[i]==pass[i+1])
//                return 0;
//        }
//    }

    /*There can be no more than 5 characters A-F and 9 numbers*/
    byte charactersAF=0,numbers=0;
    for(byte i=0; i<10; i++)
    	(pass[i]>='A' && pass[i]<='F') ? charactersAF++ : numbers++;
    if((charactersAF>5)||(numbers>9))
        return 0;

    /*There can be no more than three identical characters*/
    for(byte i=0; i<16; i++)
        if(countc(pass, characters[i])>3)
            return 0;

    /*if the password is valid than return true/1*/
    return 1;
}
static inline void bruteforce(char *pass,byte ind)
{
    for(register byte i=0;i<16;i++)
    {
        //speed-hack check if there is more two character consecutive
        if (ind>=2)
            if (pass[0] == pass[1] && pass[1] == pass[2])
                continue;
        pass[ind]=characters[i];
        if (ind==9)
        {
            if(checkpass(pass))
                printf("%s\n",pass);
        }
        else bruteforce(pass,ind+1);
    }
}
int main(void)
{
    char pass[10+1]="xxxxxxxxxx";
    fprintf(stderr,"\n[*] Password generation...\n\n");
    bruteforce(pass,0);
    return 0;
}

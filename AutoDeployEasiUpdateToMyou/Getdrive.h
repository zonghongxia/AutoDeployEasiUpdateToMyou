#ifndef _GETDRIVE_H
#define _GETDRIVE_H

#include<stdio.h>  
#include<iostream>  
#include <string>
#include<string.h>  
#include<windows.h> 
#include <atlstr.h>

class Drive
{
public:
	Drive();
	void GetDrive(std::string &drive);
};

#endif

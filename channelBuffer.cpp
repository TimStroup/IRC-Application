#include "channelBuffer.h"
#include <string>
#include <iostream>
using namespace std;

channelBuffer::channelBuffer(string name){
    channelBuffer::name = name;
}

void channelBuffer::addMessage(string message){
    channelBuffer::messages.push_back(message);
}

void channelBuffer::dumpMessages(){
    for(string msg : channelBuffer::messages){
        cout << msg << "\n";
    }
    channelBuffer::messages.clear();
}
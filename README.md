## Overview
This simple note-taking program is intended to reproduce all the typical functionality of a desktop notepad or simple text editor. The application can open any normal text file type including .txt and .rtf. 

## Building
This project should be buildable on all major platforms by using the following commands:

``` sh
git clone https://github.com/harveyongh/cpp-note.git; cd cpp-note/; 
mkdir build && cd build/
cmake .. && cmake --build .
```
The executable can then be run using
``` sh
./cppnote
```
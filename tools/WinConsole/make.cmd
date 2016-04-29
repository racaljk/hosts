windres tool.rc -o tmp.o
g++ -o tool.exe tool.cpp tmp.o -s -lwininet -O2
del /q tmp.o
pause
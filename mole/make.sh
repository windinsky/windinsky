

g++ -I/usr/local/include/ server.cc -o bin/windinsky.cgi -L/usr/local/lib/ -L/usr/local/mysql/lib -lfcgi++ -lfcgi -lmysqlclient -lpthread -ldl
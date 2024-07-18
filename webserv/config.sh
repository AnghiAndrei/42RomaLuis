path=$(pwd)
sed 's|/nfs/homes/aanghi/Desktop/42RomaLuis/webserv|$path|g' conf/conffull.conf
sed 's|/nfs/homes/aanghi/Desktop/42RomaLuis/webserv|$path|g' conf/tester.conf
sed 's|/nfs/homes/aanghi/Desktop/42RomaLuis/webserv|$path|g' webserv.cpp

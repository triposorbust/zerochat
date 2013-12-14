#!/bin/sh

sudo apt-get update

sudo apt-get -y install g++
sudo apt-get -y install gdb
sudo apt-get -y install emacs
sudo apt-get -y install make
sudo apt-get -y install git

wget download.zeromq.org/zeromq-4.0.3.tar.gz
tar -xvf zeromq-4.0.3.tar.gz

sudo echo "/usr/local/lib" >> /etc/ld.so.conf

cd zeromq-4.0.3
sudo ./configure
sudo make
sudo make install
cd ..

sudo ldconfig

exit 0

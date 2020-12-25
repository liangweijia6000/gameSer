
# gameSer

Try to create a online game framework

TODO: <br>

network first, protobuf reflect after

&#8195;network<br>
&#8195;protobuf<br>
&#8195;confg<br>
&#8195;log<br>
&#8195;timer<br>
&#8195;db server<br>
&#8195;client<br>



install protobuf:
 ```
 sudo apt-get install autoconf automake libtool curl make g++ unzip
 git clone https://github.com/protocolbuffers/protobuf.git
 cd protobuf
 git submodule update --init --recursive
 ./autogen.sh
 ./configure
 make
 make check
 sudo make install
 sudo ldconfig
 ```

 
$ export GO111MODULE=on
$ export GOPROXY=https://goproxy.cn

# Usage
## Building
* Linux/Mac
```
git submodule init
git submodule update
sudo apt-get install aptitude -y
sudo aptitude install -y build-essential git libboost-all-dev cmake rapidjson-dev sqlite3
mkdir build
cd build
cmake ..
make
```

## Running
copy ```base.db``` into build folder and rename ```default.db```
then run ```./Server```

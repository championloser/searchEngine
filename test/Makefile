testRssParse.out:testRssParse.cpp
	g++ testRssParse.cpp ../src/RssParse.cpp ../src/tinyxml2.cpp ../src/int2str.cpp ../src/GetFilenameFromDir.cpp ../src/ReadConfigFile.cpp ../src/Mylog.cpp -o rssParse.out -pthread -llog4cpp -std=c++11
#	g++ testReadByOffset.cpp ../src/ReadConfigFile.cpp ../src/Mylog.cpp ../src/int2str.cpp -o readByOff.out -llog4cpp -pthread -std=c++11
#	g++ testRmRepeat.cpp ../src/Mylog.cpp ../src/int2str.cpp ../src/ReadConfigFile.cpp ../src/RmRepeat.cpp -o rmRepeat.out -llog4cpp -pthread -std=c++11
.PHONY:clean
clean:
	rm rssParse.out
#	rm readByOff.out
#	rm rmRepeat.out

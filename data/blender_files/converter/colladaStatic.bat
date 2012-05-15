java -jar refinery.jar -i %1 -o %1 -x polylists2triangles
java -jar refinery.jar -i %1 -o %1 -x deindexer
java -jar refinery.jar -i %1 -o %1 -x Axisconverter -axis Y_UP
ColladaParser.exe %1
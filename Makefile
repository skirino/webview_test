
SRC_FILES = src/NBPane.vala src/NBBrowser.vala src/main.vala

main: ${SRC_FILES}
	mkdir bin
	valac -o bin/NetBehindBrowser --pkg gtk+-2.0 --pkg webkit-1.0 --thread ${SRC_FILES}

cgen: ${SRC_FILES}
	valac --pkg gtk+-2.0 --pkg webkit-1.0 --thread ${SRC_FILES}

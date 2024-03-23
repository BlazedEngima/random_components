clean:
	rm -rf build
	cmake -S . -B build
	cmake --build build

up:
	export HOST_ARCH=`uname -m` ;\
	docker-compose up

down:
	docker-compose down
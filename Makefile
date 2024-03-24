clean:
	rm -rf build
	cmake -S . -B build
	cmake --build build

up:
	docker-compose up

down:
	docker-compose down
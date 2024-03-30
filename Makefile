SERVICE ?=

new:
	rm -rf build
	cmake -S . -B build
	cmake --build build

up:
	docker-compose up $(SERVICE)

down:
	docker-compose down $(SERVICE)

update:
	docker-compose up --build $(SERVICE)
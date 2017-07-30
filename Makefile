.PHONY all:
all: elka_data_collection

.PHONY elka_data_collection:
elka_data_collection: elka_ground_bindings elka_ground_python

.PHONY elka_data_collection-debug:
elka_data_collection-debug: elka_ground_bindings-debug elka_ground_python

.PHONY elka_ground_bindings:
elka_ground_bindings:
	@mkdir -p build_elka_data_collection/python && cd build_elka_data_collection && cmake -DPYBIND10_PYTHON_VERSION=2.7 -DCMAKE_BUILD_TYPE=RELEASE -Wno-dev ../
	@cd build_elka_data_collection && make

.PHONY elka_data_collection-debug:
elka_ground_bindings-debug:
	@mkdir -p build_elka_data_collection/python && cd build_elka_data_collection && cmake -DPYBIND11_PYTHON_VERSION=2.7 -DCMAKE_BUILD_TYPE=DEBUG -Wno-dev ../
	@cd build_elka_data_collection && make VERBOSE=1

.PHONY elka_ground_python:
elka_ground_python:
	@python tools/h2py.py src/elka_comm/common/elka.h && mv ELKA.py src/python/elka.py
	@cp -r src/python/* build_elka_data_collection/python/

elka_ground_python-run: elka_ground_python
	cd build_elka_data_collection/python && python gui_start.py

.PHONY submodule:
submodule: 
	@git submodule update --init --recursive

.PHONY clean:
	@rm -rf build_elka_data_collection

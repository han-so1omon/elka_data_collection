.PHONY all:
all: elka_data_collection

.PHONY elka_data_collection:
elka_data_collection:
	@mkdir -p build_elka_data_collection && cd build_elka_data_collection && cmake -DPYBIND11_PYTHON_VERSION=2.7 -Wno-dev ../
	@cd build_elka_data_collection && make

.PHONY submodule:
submodule: 
	@git submodule update --init --recursive

.PHONY clean:
	@rm -rf build_elka_data_collection

#include <pybind11/pybind11.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "blake2.h"
#include "blake2-impl.h"
char version[]="1.0";

char const* getVersion() {
	return version;
}

class Bke
{
    public:
        Bke(){}
        ~Bke() {}

        void initialize(std::string &nb) {
		uint8_t sum[BLAKE2S_OUTBYTES];
		blake2s_state S;
        blake2s_init(&S,BLAKE2S_OUTBYTES);
		if(nb.length()!=0){
		  blake2s_update(&S,( const uint8_t * )&nb[0],nb.length());
		}
		blake2s_final(&S,sum,BLAKE2S_OUTBYTES);
		HashKey=std::string(sum,32);
		
		}
		
        
		const std::string &getHash() const { return HashKey; }

    private:
        std::string HashKey;
};
 
namespace py = pybind11;


PYBIND11_MODULE(blake2s_component,greetings)
{
  greetings.doc() = "greeting_object 1.0";
  greetings.def("getVersion", &getVersion, "a function returning the version");
  
   // bindings to Bke class
    py::class_<Bke>(greetings, "Bke", py::dynamic_attr())
        .def(py::init())
        .def("initialize", &Bke::initialize)
        .def("getHash", &Bke::getHash);
}
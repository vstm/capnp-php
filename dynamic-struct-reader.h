#ifndef CAPNP_PHP_DYNAMIC_STRUCT_READER_H
#define CAPNP_PHP_DYNAMIC_STRUCT_READER_H

#include <phpcpp.h>
#include <capnp/dynamic.h>

namespace capnp_php {
    class DynamicStructReader : public Php::Base {
        private:
            Php::Object messageReader;
            capnp::DynamicStruct::Reader reader;

        public:
            DynamicStructReader(capnp::DynamicStruct::Reader reader,
                Php::Object messageReader);


            Php::Value __get(const Php::Value& name);

            Php::Value which();
    };
}

#endif /* CAPNP_PHP_DYNAMIC_STRUCT_READER_H */

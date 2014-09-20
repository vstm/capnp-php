#ifndef CAPNP_PHP_STRUCT_SCHEMA_H
#define CAPNP_PHP_STRUCT_SCHEMA_H

#include <phpcpp.h>
#include <capnp/schema-parser.h>

namespace capnp_php {
    class StructSchema : public Php::Base {
        private:
            Php::Object parent;
            capnp::StructSchema schema;

        public:
            StructSchema(capnp::StructSchema schema, Php::Object parent);

            capnp::StructSchema& getSchema();

            Php::Value getFieldNames();
    };
}

#endif /* CAPNP_PHP_STRUCT_SCHEMA_H */

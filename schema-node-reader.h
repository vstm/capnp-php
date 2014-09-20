#ifndef CAPNP_PHP_SCHEMA_NODE_READER_H
#define CAPNP_PHP_SCHEMA_NODE_READER_H

#include <phpcpp.h>
#include <capnp/schema.capnp.h>

namespace capnp_php {
    class SchemaNodeReader : public Php::Base {
        private:
            Php::Value parsedSchema;
            capnp::schema::Node::Reader reader;
        public:
           SchemaNodeReader(capnp::schema::Node::Reader reader,
                            Php::Value parsedSchema);


            Php::Object getNestedNodes();
            Php::Value isStruct();
            Php::Value isEnum();

    };
}

#endif /* CAPNP_PHP_SCHEMA_NODE_READER_H */

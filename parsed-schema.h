#ifndef CAPNP_PHP_PARSED_SCHEMA_H
#define CAPNP_PHP_PARSED_SCHEMA_H


#include <phpcpp.h>
#include <capnp/schema-parser.h>

namespace capnp_php {
    class ParsedSchema : public Php::Base {
        private:
            Php::Value schemaParser;
            ::capnp::ParsedSchema schema;
        public:
            ParsedSchema(const ::capnp::ParsedSchema & schema,
                         Php::Value schemaParser);

            Php::Value getProto();
            Php::Value getNested(Php::Parameters& params);
            Php::Value asStruct();
    };
}

#endif /* CAPNP_PHP_PARSED_SCHEMA_H */

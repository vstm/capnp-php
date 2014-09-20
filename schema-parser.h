#ifndef CAPNP_PHP_SCHEMA_PARSER_H
#define CAPNP_PHP_SCHEMA_PARSER_H

#include <phpcpp.h>
#include <capnp/schema-parser.h>

namespace capnp_php {
	class SchemaParser : public Php::Base {
            private:
                // we have to do this to prevent
                // "error: looser throw specifier ..." compiler error
                capnp::SchemaParser* parser;
            public:
                SchemaParser();
                ~SchemaParser();
                Php::Value parseDiskFile(Php::Parameters &params);
	};
}

#endif /* CAPNP_PHP_SCHEMA_PARSER_H */

#ifndef CAPNP_PHP_FLAT_ARRAY_MESSAGE_READER_H
#define CAPNP_PHP_FLAT_ARRAY_MESSAGE_READER_H

#include <string>
#include <phpcpp.h>
#include <capnp/serialize.h>

namespace capnp_php {
    class FlatArrayMessageReader : public Php::Base {
        private:
            std::string message;
            ::capnp::FlatArrayMessageReader* reader;

        public:
            FlatArrayMessageReader();
            ~FlatArrayMessageReader();

            void __construct(Php::Parameters& params);

            Php::Value getRoot(Php::Parameters& params);
    };
}

#endif /* CAPNP_PHP_FLAT_ARRAY_MESSAGE_READER_H */

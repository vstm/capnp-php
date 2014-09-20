#ifndef CAPNP_PHP_MALLOC_MESSAGE_BUILDER_H
#define CAPNP_PHP_MALLOC_MESSAGE_BUILDER_H

#include <phpcpp.h>
#include <capnp/message.h>

namespace capnp_php {
    class MallocMessageBuilder : public Php::Base {
        private:
            capnp::MallocMessageBuilder* builder;

        public:
            MallocMessageBuilder();
            ~MallocMessageBuilder();

            Php::Value initRoot(Php::Parameters& params);
            Php::Value toFlatArray();
    };
}

#endif /* CAPNP_PHP_MALLOC_MESSAGE_BUILDER_H */

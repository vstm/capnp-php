#ifndef CAPNP_PHP_DYNAMIC_LIST_BUILDER_H
#define CAPNP_PHP_DYNAMIC_LIST_BUILDER_H

#include <phpcpp.h>
#include <capnp/dynamic.h>

namespace capnp_php {

    class DynamicListBuilder : public Php::Base, public Php::Countable,
        public Php::ArrayAccess, public Php::Traversable {
        private:
            Php::Object messageBuilder;
            capnp::DynamicList::Builder builder;

        public:
            DynamicListBuilder(capnp::DynamicList::Builder builder,
                Php::Object messageBuilder);

            Php::Value getByIndex(int64_t index);

            virtual long count() override;
            virtual bool offsetExists(const Php::Value &key) override;
            virtual Php::Value offsetGet(const Php::Value &key) override;

            virtual void offsetSet(const Php::Value &key, const Php::Value &value) override;
            virtual void offsetUnset(const Php::Value &key) override;

            virtual Php::Iterator *getIterator() override;
    };
}

#endif /* CAPNP_PHP_DYNAMIC_LIST_BUILDER_H */

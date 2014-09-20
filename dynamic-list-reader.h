#ifndef CAPNP_PHP_DYNAMIC_LIST_READER_H
#define CAPNP_PHP_DYNAMIC_LIST_READER_H

#include <phpcpp.h>
#include <capnp/dynamic.h>

namespace capnp_php {

    class DynamicListReader : public Php::Base, public Php::Countable,
        public Php::ArrayAccess, public Php::Traversable {
        private:
            Php::Object messageReader;
            capnp::DynamicList::Reader reader;

        public:
            DynamicListReader(capnp::DynamicList::Reader reader,
                Php::Object messageReader);

            ~DynamicListReader();

            Php::Value getByIndex(int64_t index);

            virtual long count() override;
            virtual bool offsetExists(const Php::Value &key) override;
            virtual Php::Value offsetGet(const Php::Value &key) override;

            virtual void offsetSet(const Php::Value &key, const Php::Value &value) override;
            virtual void offsetUnset(const Php::Value &key) override;

            virtual Php::Iterator *getIterator() override;

    };

}

#endif /* CAPNP_PHP_DYNAMIC_LIST_READER_H */

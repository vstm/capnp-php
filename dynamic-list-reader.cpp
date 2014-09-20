#include <iostream>

#include "dynamic-list-reader.h"
#include "dynamic-value-converter.h"

namespace capnp_php {
    DynamicListReader::DynamicListReader(capnp::DynamicList::Reader reader,
                Php::Object messageReader)
        : Php::Base(),
          Php::Countable(),
          messageReader(messageReader),
          reader(reader)
    {
        //Php::out << "DynamicListReader::DynamicListReader ctor " << (void*)this << std::endl;
    }

    DynamicListReader::~DynamicListReader() {
        //Php::out << "DynamicListReader::~DynamicListReader dtor " << (void*)this << std::endl;

    }

    Php::Value DynamicListReader::getByIndex(int64_t index) {
        return DynamicValueConverter::convertFromCapnp(reader[index], this);
    }

    long DynamicListReader::count() {
        return static_cast<long>(reader.size());
    }

    bool DynamicListReader::offsetExists(const Php::Value &key) {
        int64_t index = key;

        return index < static_cast<int64_t>(reader.size());
    }

    Php::Value DynamicListReader::offsetGet(const Php::Value &key) {
        return getByIndex(key);
    }

    void DynamicListReader::offsetSet(const Php::Value &key, const Php::Value &value) {
        //throw Php::NotImplemented();
    }

    void DynamicListReader::offsetUnset(const Php::Value &key) {
        //throw Php::NotImplemented();
    }

    class DynamicListReaderIterator : public Php::Iterator {
        private:
            long index;
            DynamicListReader * reader;

        public:
            DynamicListReaderIterator(DynamicListReader * reader) 
                : Php::Iterator(reader),
                  index(0),
                  reader(reader)
            {
            }

            virtual ~DynamicListReaderIterator() { }

            virtual bool valid() override
            {
                return index < reader->count();
            }

            virtual Php::Value current() override
            {
                return reader->getByIndex(index);
            }

            virtual Php::Value key() override
            {
                return static_cast<int64_t>(index);
            }

            virtual void next() override
            {
                ++index;
            }

            virtual void rewind() override
            {
                index = 0;
            }

    };

    Php::Iterator * DynamicListReader::getIterator() {
        return new DynamicListReaderIterator(this);
    }
}

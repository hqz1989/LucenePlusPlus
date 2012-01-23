/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2009-2011 Alan Wright. All rights reserved.
// Distributable under the terms of either the Apache License (Version 2.0)
// or the GNU Lesser General Public License.
/////////////////////////////////////////////////////////////////////////////

#ifndef MAP_H
#define MAP_H

#include <map>
#include <boost/unordered_map.hpp>
#include "LuceneSync.h"

namespace Lucene
{
    template <class T>
    class Map : public map_ptr<T>, public LuceneSync
    {
    public:
        typedef typename T::key_type key_type;
        typedef typename T::mapped_type mapped_type;
        typedef typename T::iterator iterator;
        typedef typename T::const_iterator const_iterator;

        Map(pair_container<T>* p = 0) : map_ptr<T>(p)
        {
        }

        Map(const Map& rhs) : map_ptr<T>(rhs)
        {
        }

        void put(const key_type& key, const mapped_type& value)
        {
            (*this)[key] = value;
        }

        template <class ITER>
        void put(ITER first, ITER last)
        {
            for (; first != last; ++first)
                put(first->first, first->second);
        }

        iterator remove(iterator pos)
        {
            return this->erase(pos);
        }

        iterator remove(iterator first, iterator last)
        {
            return this->erase(first, last);
        }

        bool remove(const key_type& key)
        {
            return this->erase(key) > 0;
        }

        mapped_type get(const key_type& key) const
        {
            const_iterator findValue = this->find(key);
            return findValue == this->end() ? mapped_type() : findValue->second;
        }

        bool contains(const key_type& key) const
        {
            return this->find(key) != this->end();
        }

        int32_t hashCode()
        {
            return (int32_t)(int64_t)this->get();
        }

        int32_t size() const
        {
            return (int32_t)map_ptr<T>::size();
        }
    };

    template < class KEY, class VALUE, class HASH = boost::hash<KEY>, class EQUAL = std::equal_to<KEY> >
    class HashMap : public Map < boost::unordered_map<KEY, VALUE, HASH, EQUAL> >
    {
    public:
        typedef boost::unordered_map<KEY, VALUE, HASH, EQUAL> map_type;
        typedef typename map_type::key_type key_type;
        typedef typename map_type::mapped_type mapped_type;
        typedef typename map_type::hasher hasher;
        typedef typename map_type::key_equal key_equal;

        HashMap(pair_container<map_type>* p = 0) : Map<map_type>(p)
        {
        }

        HashMap(const HashMap& rhs) : Map<map_type>(rhs)
        {
        }

        static HashMap<KEY, VALUE, HASH, EQUAL> newInstance()
        {
            pair_container<map_type>* container = new pair_container<map_type>();
            gc::get_gc().register_object(static_cast<gc_object*>(container));
            return HashMap<KEY, VALUE, HASH, EQUAL>(container);
        }

        static HashMap<KEY, VALUE, HASH, EQUAL> newStaticInstance()
        {
            pair_container<map_type>* container = new pair_container<map_type>();
            gc::get_static_gc().register_object(static_cast<gc_object*>(container));
            return HashMap<KEY, VALUE, HASH, EQUAL>(container);
        }

        template <class ITER>
        static HashMap<KEY, VALUE, HASH, EQUAL> newInstance(ITER first, ITER last)
        {
            pair_container<map_type>* container = new pair_container<map_type>();
            gc::get_gc().register_object(static_cast<gc_object*>(container));
            container->insert(first, last);
            return HashMap<KEY, VALUE, HASH, EQUAL>(container);
        }

        template <class ITER>
        static HashMap<KEY, VALUE, HASH, EQUAL> newStaticInstance(ITER first, ITER last)
        {
            pair_container<map_type>* container = new pair_container<map_type>();
            gc::get_static_gc().register_object(static_cast<gc_object*>(container));
            container->insert(first, last);
            return HashMap<KEY, VALUE, HASH, EQUAL>(container);
        }
    };

    template < class KEY, class VALUE, class COMPARE = std::less<KEY> >
    class SortedMap : public Map < std::map<KEY, VALUE, COMPARE> >
    {
    public:
        typedef std::map<KEY, VALUE, COMPARE> map_type;
        typedef typename map_type::key_type key_type;
        typedef typename map_type::mapped_type mapped_type;
        typedef typename map_type::key_compare key_compare;

        SortedMap(pair_container<map_type>* p = 0) : Map<map_type>(p)
        {
        }

        SortedMap(const SortedMap& rhs) : Map<map_type>(rhs)
        {
        }

        static SortedMap<KEY, VALUE, COMPARE> newInstance()
        {
            pair_container<map_type>* container = new pair_container<map_type>();
            gc::get_gc().register_object(static_cast<gc_object*>(container));
            return SortedMap<KEY, VALUE, COMPARE>(container);
        }

        static SortedMap<KEY, VALUE, COMPARE> newStaticInstance()
        {
            pair_container<map_type>* container = new pair_container<map_type>();
            gc::get_static_gc().register_object(static_cast<gc_object*>(container));
            return SortedMap<KEY, VALUE, COMPARE>(container);
        }

        template <class ITER>
        static SortedMap<KEY, VALUE, COMPARE> newInstance(ITER first, ITER last)
        {
            pair_container<map_type>* container = new pair_container<map_type>();
            gc::get_gc().register_object(static_cast<gc_object*>(container));
            container->insert(first, last);
            return SortedMap<KEY, VALUE, COMPARE>(container);
        }

        template <class ITER>
        static SortedMap<KEY, VALUE, COMPARE> newStaticInstance(ITER first, ITER last)
        {
            pair_container<map_type>* container = new pair_container<map_type>();
            gc::get_static_gc().register_object(static_cast<gc_object*>(container));
            container->insert(first, last);
            return SortedMap<KEY, VALUE, COMPARE>(container);
        }
    };
}

#endif

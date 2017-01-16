#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <vector>

template <class object_infos>
class Object
{
    private:
        static std::vector<object_infos> infos;

    public:
        Object(unsigned short id = 0, unsigned short variant = 0) :
            id(id), variant(variant)
        {
        }

        object_infos& getInfos()
        {
            if (infos.size() <= id)
                infos.resize(id + 1);

            return (infos[id]);
        }

        const object_infos& getInfos() const
        {
            if (infos.size() <= id)
                infos.resize(id + 1);

            return (infos[id]);
        }

        static void setInfosFor(object_infos &info, unsigned short id)
        {
            if (infos.size() <= id)
                infos.resize(id + 1);

            infos[id] = info;
        }

        static void clearAllInfos()
        {
            infos.clear();
        }

        unsigned short id;
        unsigned short variant;
};

template <class object_infos>
std::vector<object_infos> Object<object_infos>::infos;

#endif

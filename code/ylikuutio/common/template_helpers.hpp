#ifndef __TEMPLATE_HELPERS_HPP_INCLUDED
#define __TEMPLATE_HELPERS_HPP_INCLUDED

// http://stackoverflow.com/questions/992471/how-to-query-ift-int-with-template-class/992476#992476
template<class T>
struct type_is_float
{
    static const bool value = false;
};

template<>
struct type_is_float<float>
{
    static const bool value = true;
};

template<class T>
struct type_is_int32_t
{
    static const bool value = false;
};

template<>
struct type_is_int32_t<int32_t>
{
    static const bool value = true;
};

template<class T>
struct type_is_uint32_t
{
    static const bool value = false;
};

template<>
struct type_is_uint32_t<uint32_t>
{
    static const bool value = true;
};

#endif

#pragma once

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <type_traits>

template<typename, typename = void>
struct is_serializable : std::false_type {};

template<typename T>
struct is_serializable<T, std::void_t<
    decltype(std::declval<T>().serialize(std::declval<boost::archive::text_oarchive&>(), 0)),
    decltype(std::declval<T>().serialize(std::declval<boost::archive::text_iarchive&>(), 0))
>> : std::true_type {};

template<typename T>
constexpr bool is_serializable_v = is_serializable<T>::value;

template<typename T>
std::string serialize(const T& value) {
    std::ostringstream oss;
    oss.imbue(std::locale::classic());
    boost::archive::text_oarchive oa(oss);
    oa << value;
    return oss.str();
}

template<typename T>
T deserialize(const std::string& data) {
    std::istringstream iss(data);
    iss.imbue(std::locale::classic());
    boost::archive::text_iarchive ia(iss);
    T value;
    ia >> value;
    return value;
}
// Include standard headers
namespace ylikuutio
{
    namespace memory
    {
        template<class T1, class T2>
            T2 read_nonaligned_32_bit(T1* src_data, std::size_t offset)
            {
                uint8_t* src_data_uint8_t = (uint8_t*) src_data;
                T2 value_32_bit = static_cast<T2>(src_data_uint8_t[offset + 3]);
                value_32_bit = value_32_bit << 8 | static_cast<T2>(src_data_uint8_t[offset + 2]);
                value_32_bit = value_32_bit << 8 | static_cast<T2>(src_data_uint8_t[offset + 1]);
                value_32_bit = value_32_bit << 8 | static_cast<T2>(src_data_uint8_t[offset]);
                return value_32_bit;
            }
    }
}

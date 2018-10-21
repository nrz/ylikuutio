// Include standard headers
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace yli
{
    namespace command_line
    {
        class CommandLineMaster
        {
            public:
                CommandLineMaster(const int argc, const char* const argv[]);
                bool is_key(const std::string& key);
                std::string get_value(const std::string& key);
                void print_keys();
                void print_keys_and_values();

            private:
                int argc;
                std::vector<std::string> arg_vector;
                std::unordered_map<std::string, std::string> arg_map;
        };
    }
}

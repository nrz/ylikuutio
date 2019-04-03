#ifndef __SHADER_COMPARE_HPP_INCLUDED
#define __SHADER_COMPARE_HPP_INCLUDED

namespace yli
{
    namespace ontology
    {
        class Shader;

        class ShaderCompare
        {
            public:
                bool operator() (yli::ontology::Shader* first, yli::ontology::Shader* second);
        };
    }
}

#endif

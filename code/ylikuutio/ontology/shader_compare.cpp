#include "shader_compare.hpp"
#include "entity.hpp"
#include "shader.hpp"

namespace yli
{
    namespace ontology
    {
        bool ShaderCompare::operator() (yli::ontology::Shader* first, yli::ontology::Shader* second)
        {
            if (first->is_gpgpu_shader)
            {
                if (!second->is_gpgpu_shader)
                {
                    return false;
                }

                if (first->get_childID() < second->get_childID())
                {
                    return true;
                }

                return false;
            }

            if (second->is_gpgpu_shader)
            {
                return false;
            }

            if (first->get_childID() < second->get_childID())
            {
                return true;
            }

            return false;
        }
    }
}

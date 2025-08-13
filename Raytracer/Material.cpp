#include "Material.hpp"

Material::Material(Color4 col) : m_pattern{ no_pat(col) } {}
Material::Material(Pattern pat) : m_pattern{ pat } {}
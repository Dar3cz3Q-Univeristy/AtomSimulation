#include "Sphere.h"

// TODO: Connect vertices without repeating
// #define AS_SPHERE_FEWER_INDICES

Sphere::Sphere(float radius, unsigned int rings, unsigned int sectors)
{
    float const R = 1.0f / (float)(rings - 1);
    float const S = 1.0f / (float)(sectors - 1);
    unsigned int r{}, s{};

    m_Vertices.resize(rings * sectors);

    std::vector<Vertex>::iterator v = m_Vertices.begin();

    for (r = 0; r < rings; r++) for (s = 0; s < sectors; s++) {
        float const y = sin(-static_cast<float>(M_PI_2) + static_cast<float>(M_PI) * r * R);
        float const x = cos(2.0f * static_cast<float>(M_PI) * s * S) * sin(static_cast<float>(M_PI) * r * R);
        float const z = sin(2.0f * static_cast<float>(M_PI) * s * S) * sin(static_cast<float>(M_PI) * r * R);

        (*v).Position.x = x * radius;
        (*v).Position.y = y * radius;
        (*v).Position.z = z * radius;

        (*v).Normal.x = x;
        (*v).Normal.y = y;
        (*v).Normal.z = z;

        (*v).UV.x = s * S;
        (*v).UV.y = r * R;

        v++;
    }

#ifdef AS_SPHERE_FEWER_INDICES
    m_Indices.resize(rings * sectors * 4);
#else
    m_Indices.resize(rings * sectors * 6);
#endif

    std::vector<unsigned int>::iterator i = m_Indices.begin();

#ifdef AS_SPHERE_FEWER_INDICES
    for (r = 0; r < rings - 1; r++) {
        for (s = 0; s < sectors - 1; s++) {
            *i++ = r * sectors + s;
            *i++ = r * sectors + (s + 1);
            *i++ = (r + 1) * sectors + (s + 1);
            *i++ = (r + 1) * sectors + s;
        }
    }
#else
    for (r = 0; r < rings - 1; r++) {
        for (s = 0; s < sectors - 1; s++) {
            int curRow = r * sectors;
            int nextRow = (r + 1) * sectors;

            *i++ = curRow + s;
            *i++ = nextRow + s;
            *i++ = nextRow + (s + 1);

            *i++ = curRow + s;
            *i++ = nextRow + (s + 1);
            *i++ = curRow + (s + 1);
        }
    }
#endif
}

Sphere::~Sphere() {}

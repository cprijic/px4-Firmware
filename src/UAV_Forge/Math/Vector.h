// Copyright 2015 Christopher Prijic

#ifndef SRC_UAV_FORGE_MATH_VECTOR_H_
#define SRC_UAV_FORGE_MATH_VECTOR_H_

struct vec3 {
    float x = 0, y = 0, z = 0;

    vec3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    vec3() : x(0), y(0), z(0) {}

    vec3 operator-(float a) {
        return vec3(x - a, y - a, z - a);
    }

    vec3 operator-(vec3 v) {
        return vec3(x - v.x, y - v.y, z - v.z);
    }

    vec3 operator+(float a) {
        return vec3(x + a, y + a, z + a);
    }

    vec3 operator+(vec3 v) {
        return vec3(x + v.x, y + v.y, z + v.z);
    }

    vec3 operator-=(float a) {
        x-=a; y-=a; z-=a; return *this;
    }

    vec3 operator-=(vec3 v) {
        x-=v.x; y-=v.y; z-=v.z; return *this;
    }

    vec3 operator+=(float a) {
        x+=a; y+=a; z+=a; return *this;
    }

    vec3 operator+=(vec3 v) {
        x+=v.x; y+=v.y; z+=v.z; return *this;
    }
};

#endif /* SRC_UAV_FORGE_MATH_VECTOR_H_ */

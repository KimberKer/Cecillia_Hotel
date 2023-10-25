#ifndef PHYSICSLIB_HPP
#define PHYSICSLIB_HPP
#include "../Math/Vector2D.h"



namespace Duck {

    class AABB {
    public:
        MathLib::Vector2D minVec;
        MathLib::Vector2D maxVec;

    public:
            AABB();
            AABB(const MathLib::Vector2D& min, const MathLib::Vector2D& max);
            AABB ConvertToAABB(float x, float y, float width, float height);

    };

    class PhysicsLib {

        template <typename T>
        T Max(const T& a, const T& b);

    public:
        bool CollisionIntersection_RectRect(const AABB& aabb1, const MathLib::Vector2D& vel1,
            const AABB& aabb2, const MathLib::Vector2D& vel2, float dt);
        bool IsOutOfBounds(const AABB& boundingBox, const AABB& other) const;
    private:

 
    };


}
#endif // PHYSICSLIB_HPP

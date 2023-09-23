#ifndef PHYSICSLIB_HPP
#define PHYSICSLIB_HPP
#include "../Math/Vector2D.h"
#include "../Time.h"


namespace Duck {
    class AABB {
    public:
        MathLib::Vector2D min;
        MathLib::Vector2D max;
    };

    class PhysicsLib {

    template <typename T>
    T Max(const T& a, const T& b);

    public:

        PhysicsLib() {

        };
        ~PhysicsLib() {};

        bool CollisionIntersection_RectRect(const AABB& aabb1, const MathLib::Vector2D& vel1,
            const AABB& aabb2, const MathLib::Vector2D& vel2);

        void PlayerMovement(bool keyPressed, int longPressedKey, MathLib::Vector2D player_current_position, MathLib::Vector2D player_current_Velocity);
        //        void testCollison(int longKeyPressed,GLFWwindow* _window, MathLib::Vector2D* player_pos);

    private:
        Time time;
 
    };


}
#endif // PHYSICSLIB_HPP

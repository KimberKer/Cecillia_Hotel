#include "duckpch.h"

#include "PhysicsSystem.h"
#include "Duck/De-serialize/GameObject.h"
#include "Duck/Player/PlayerComponent.h"

#include "Duck/KeyCodes.h"
#include "Duck/Platform/Windows/WindowsInput.h"



namespace Duck
{

    void PhysicsSystem::Init() 
    {
        for (auto& entity : m_Entities)
        {
            
        }
    }

    // Update the physics object based on the given time delta.
    void PhysicsSystem::Update(double dt, int cellSize)
    {
        for (auto const& entity : m_Entities)
        {
            auto& obj = ecs.getComponent<GameObject>(entity);

            //update logic for player
            if (obj.getObj() == OBJ_PLAYER)
            {
                auto& player = ecs.getComponent<PlayerComponent>(entity);

                //update state of player
                if (WindowsInput::IsKeyPressed(Key::Left))
                {
                    obj.SetState(STATE_GOING_LEFT);
                }

                else if (WindowsInput::IsKeyPressed(Key::Right))
                {
                    obj.SetState(STATE_GOING_RIGHT);
                }

                else if (WindowsInput::IsKeyPressed(Key::Up))
                {
                    obj.SetState(STATE_GOING_UP);
                }

                else if (WindowsInput::IsKeyPressed(Key::Down))
                {
                    obj.SetState(STATE_GOING_DOWN);
                }
                
                else
                {
                    obj.SetState(STATE_NONE);
                }

                //update velocity based on state
                switch (obj.getState())
                {
                case STATE_GOING_LEFT:
                    obj.SetVelocityX(-1.0f);
                    break;
                case STATE_GOING_RIGHT:
                    obj.SetVelocityX(1.0f);
                    break;
                case STATE_GOING_UP:
                    obj.SetVelocityY(1.0f);
                    break;
                case STATE_GOING_DOWN:
                    obj.SetVelocityY(-1.0f);
                    break;
                default:
                    obj.SetVelocityX(0.0f);
                    obj.SetVelocityY(0.0f);
                    break;
                }

                //player movement
                if (!player.IsMoving()) {
                    player.SetPercentMove(0.0f);

                    if (obj.getVelocityX() != 0.0f || obj.getVelocityY() != 0.0f)
                    {
                        player.SetInitialPosition(MathLib::Vector2D(obj.getX(), obj.getY()));
                        player.SetMoving(true);
                    }
                }

                else if (obj.getVelocityX() != 0.f && obj.getVelocityY() == 0.0f && player.IsMoving())
                {
                    float percentMove = player.GetPercentMove();
                    percentMove += player.GetPlayerVelocity() * dt;

                    if (percentMove >= 1.0f)
                    {
                        obj.SetPositionX(player.GetInitialPos().x + (cellSize * obj.getVelocityX()));
                        player.SetPercentMove(0.0f);
                        player.SetMoving(false);
                    }

                    else
                    {
                        obj.SetPositionX(player.GetInitialPos().x + (cellSize * obj.getVelocityX() * percentMove));
                        player.SetPercentMove(0.0f);
                        player.SetMoving(false);
                    }
                }

                else if (obj.getVelocityY() != 0.0f && obj.getVelocityX() == 0.0f && player.IsMoving())
                {
                    float percentMove = player.GetPercentMove();
                    percentMove += player.GetPlayerVelocity() * dt;

                    if (percentMove >= 1.0f)
                    {
                        obj.SetPositionY(player.GetInitialPos().y + (cellSize * obj.getVelocityY()));
                        player.SetPercentMove(0.0f);
                        player.SetMoving(false);
                    }

                    else
                    {
                        obj.SetPositionY(player.GetInitialPos().y + (cellSize * obj.getVelocityY() * percentMove));
                        player.SetPercentMove(0.0f);
                        player.SetMoving(false);
                    }
                }
            }

            std::cout << "TESTING PHYSICS--------------------\n";
            std::cout << "X: " << obj.getX() << ", velocity X: " << obj.getVelocityX() << std::endl;
            std::cout << "Y: " << obj.getY() << ", velocity Y: " << obj.getVelocityY() << std::endl;
            std::cout << "-----------------------------------\n";

        }
        
        
        // Using the kinematic equation: v = u + a * t
        // Update velocity based on acceleration
        //xVelocity += xAcceleration * static_cast<float>(deltaTime);
        //yVelocity += yAcceleration * static_cast<float>(deltaTime);

        // Using the kinematic equation: s = u * t + 0.5 * a * t * t
        // Update position based on velocity
        //x += xVelocity * static_cast<float>(deltaTime);
        //y += yVelocity * static_cast<float>(deltaTime);
    }

}
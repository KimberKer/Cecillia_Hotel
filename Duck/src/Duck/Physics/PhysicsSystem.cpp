//---------------------------------------------------------
// File:		PhysicsSystam.cpp
// 
// authors:		Kristy Lee Yu Xuan
// email:		kristyyuxuan.lee\@digipen.edu
//
// Brief:       This source file defines the functions in the Physics System class.
//
// Copyright ? 2023 DigiPen, All rights reserved.
//-------------------------------------------------------

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
                float acceleration = player.GetPlayerVelocity() * dt;

                // If the player is currently moving horizontally
                if (obj.getVelocityX() != 0.f && obj.getVelocityY() == 0.0f) {
                    // Update the player's position based on acceleration and velocity
                    obj.SetPositionX(obj.getX() + (cellSize * obj.getVelocityX() * acceleration));
                }
                // If the player is currently moving vertically
                else if (obj.getVelocityY() != 0.f && obj.getVelocityX() == 0.0f) {
                    // Update the player's position based on acceleration and velocity
                    obj.SetPositionY(obj.getY() + (cellSize * obj.getVelocityY() * acceleration));
                }
            }

            //uncomment when testing
            // std::cout << "TESTING PHYSICS--------------------\n";
            // std::cout << "X: " << obj.getX() << ", velocity X: " << obj.getVelocityX() << std::endl;
            // std::cout << "Y: " << obj.getY() << ", velocity Y: " << obj.getVelocityY() << std::endl;
            // std::cout << "-----------------------------------\n";

        }

    }

}
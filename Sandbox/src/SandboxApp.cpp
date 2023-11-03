#include <Duck.h>

extern bool	showImGuiWindow;
extern 	double	fps;

class ExampleLayer : public Duck::Layer
{
public:

	ExampleLayer() : Layer("Example") {
		isGamePlaying = true;

		//showImGuiWindow = true;

		///* ---------- ECS ---------- */
		Duck::ecs.Init();

		///* ---------- Register Components ---------- */
		Duck::ecs.RegisterComponent<Duck::AudioComponent>();
		Duck::ecs.RegisterComponent<Duck::GameObject>();
		Duck::ecs.RegisterComponent<Duck::PlayerComponent>();
		Duck::ecs.RegisterComponent<Duck::GraphicsComponent>();
		//Duck::ecs.RegisterComponent<Duck::JiangShi>();
		/* ---------- ---------- ---------- */

		///* ---------- Register Systems -> init system ---------- */
		audioSystem = Duck::ecs.RegisterSystem<Duck::AudioSystem>();
		{
			Duck::Signature signature;

			//set signature
			signature.set(Duck::ecs.GetComponentType<Duck::AudioComponent>());

			//set signature to system
			Duck::ecs.SetSystemSignature<Duck::AudioSystem>(signature);
		}
		audioSystem->init();

		physicsSystem = Duck::ecs.RegisterSystem<Duck::PhysicsSystem>();
		{
			Duck::Signature signature;

			//set signature
			signature.set(Duck::ecs.GetComponentType<Duck::GameObject>());
			signature.set(Duck::ecs.GetComponentType<Duck::PlayerComponent>());

			//set signautre to system
			Duck::ecs.SetSystemSignature<Duck::PhysicsSystem>(signature);
		}
		physicsSystem->Init();

		graphicsSystem = Duck::ecs.RegisterSystem<Duck::GraphicsSystem>();
		{
			Duck::Signature signature;

			//set signature
			signature.set(Duck::ecs.GetComponentType<Duck::GraphicsComponent>());

			//set signature to system
			Duck::ecs.SetSystemSignature<Duck::GraphicsSystem>(signature);
		}
		graphicsSystem->Init();

		/*JiangShi = Duck::ecs.RegisterSystem<Duck::JiangShi>();
		{
			Duck::Signature signature;
			signature.set(Duck::ecs.GetComponentType<Duck::JiangShi>());
			Duck::ecs.SetSystemSignature<Duck::JiangShi>(signature);
		}*/
		/* ---------- ---------- ---------- */


		///* ---------- Load Assets ---------- */
		m_AssetManager = std::unique_ptr<Duck::AssetManager>(new Duck::AssetManager);

		m_AssetManager->LoadAssets();

		///* ---------- Create Entities ---------- */

		//fonts
		Duck::Entity mineFont = Duck::ecs.CreateEntity();
		{
			Duck::ecs.AddComponent<Duck::GraphicsComponent>(
				mineFont,
				{ GRAPHICS_FONT, "Mine", "../assets/fonts/Minecraft.ttf" }
			);
		}

		//player
		Duck::Entity player = Duck::ecs.CreateEntity();

		Duck::ecs.AddComponent<Duck::GameObject>(
			player,
			{ 0, 0, 0, 0, 0, 0, STATE_NONE, OBJ_PLAYER }
		);

		Duck::ecs.AddComponent<Duck::PlayerComponent>(
			player,
			{}
		);

		//ghost
		/*Duck::Entity ghost = Duck::ecs.CreateEntity();
		Duck::ecs.AddComponent<Duck::JiangShi>(
			ghost,
			{ 6.f, 3.f, 0.2f, 0.0f, 1.0f, aabb.ConvertToAABB(7.f, 7.f, 1.f, 1.f) }
		);*/


		//audio entities
		Duck::Entity bgm = Duck::ecs.CreateEntity();
		Duck::Entity sfx1 = Duck::ecs.CreateEntity();
		Duck::Entity sfx2 = Duck::ecs.CreateEntity();
		Duck::Entity sfx3 = Duck::ecs.CreateEntity();

		Duck::ecs.AddComponent<Duck::AudioComponent>(
			bgm,
			{ "bgm", "../assets/audio/bgm.wav", true, 0.3f }
		);

		Duck::ecs.AddComponent<Duck::AudioComponent>(
			sfx1,
			{ "oof", "../assets/audio/oof.wav" }
		);

		Duck::ecs.AddComponent<Duck::AudioComponent>(
			sfx2,
			{ "ooz", "../assets/audio/ooz.wav" }
		);

		Duck::ecs.AddComponent<Duck::AudioComponent>(
			sfx3,
			{ "pew", "../assets/audio/pew.wav" }
		);


		/* ---------- ---------- ---------- */
		/* ---------- Map Functions ---------- */
		std::shared_ptr<Duck::MapDataHandler> map1 = std::make_shared<Duck::MapDataHandler>("../txtfiles/Map/map1.txt");
		m_maplist.push_back(map1);

		// Create and add the second map to the list
		std::shared_ptr<Duck::MapDataHandler> map2 = std::make_shared<Duck::MapDataHandler>("../txtfiles/Map/map2.txt");
		m_maplist.push_back(map2);

		/* ---------- ---------- ---------- */

		/* ---------- Load Texture ---------- */

		m_Graphics = std::unique_ptr<Duck::Graphics>(new Duck::Graphics(Duck::Application::Get().GetWindow()));


		m_InventorySlot = m_AssetManager->GetTexture("InventorySlot.jpeg");
		m_Animation = m_AssetManager->GetTexture("Character1Sprite.png");
		Image[OBJ_EMPTY] = m_AssetManager->GetTexture("FloorTile5.jpg");
		Image[OBJ_PLAYER] = m_AssetManager->GetTexture("Character1.png");
		Image[OBJ_WALL] = m_AssetManager->GetTexture("WallTile1.png");
		Image[OBJ_GHOST] = m_AssetManager->GetTexture("Ghost.png");
		Image[OBJ_NPC] = m_AssetManager->GetTexture("empty.png"); //not yet created
		Image[OBJ_OBJ] = m_AssetManager->GetTexture("empty.png"); //not yet created
		
		/* ---------- ---------- ---------- */

		/* ---------- Load Font ---------- */
		//m_Graphics->LoadFont("../assets/fonts/Roboto-Bold.ttf", "Roboto");
		//m_Graphics->LoadFont("../assets/fonts/Minecraft.ttf", "Mine");
		/* ---------- ------------ ---------- */

		/* ---------- Set Gridsize of Game ---------- */
		m_Graphics->SetGridSize(static_cast<int>(m_maplist[Duck::GetMapIndex()]->GetHeight()));
		/* ---------- ---------- ---------- */




		/* ---------- Game Objects ---------- */
		//create a list of game objects
		//m_gameobjList = new Duck::GameObject[MAX_NUMBER_OF_OBJ];

		// Creating the objects based on the map 
		//InitializeMap();
		m_maplist[Duck::GetMapIndex()]->InitializeMap(objectlist, m_gameobjList, p_player, Image);

		//prints map
		m_maplist[Duck::GetMapIndex()]->printMapData();

		/* ---------- ---------- ---------- */
		PlayerIniPosition = { p_player->getX(), p_player->getY() };
		m_ImGuiLayer = new Duck::ImGuiLayer(m_maplist, objectlist);
		Duck::Application::Get().PushOverlay(m_ImGuiLayer);

	}

	void OnUpdate() override
	{

		runtime.update();
		static auto startTime = std::chrono::high_resolution_clock::now();

		// Inside your game loop
		auto currentTime = std::chrono::high_resolution_clock::now();
		double frameTime = std::chrono::duration<double>(currentTime - startTime).count();
		startTime = currentTime;

		// Calculate FPS
		fps = 1.0 / frameTime;
		float dt = static_cast<float>(runtime.getDeltaTime());



		///* ---------- Updating Systems ---------- */
		audioSystem->update();
		physicsSystem->Update(dt, CELL_SIZE);
		//JiangShi->Update(dt, p_player);
		/* ---------- ---------- ---------- */

		if (isGamePlaying) {
			showGrid = GridChecker;
			// Calculate the target grid position based on the character's speed
			for (int i{}; i < objectlist.size(); i++) {
				switch (objectlist[i]->getState()) {
				case STATE_GOING_LEFT:
					objectlist[i]->SetVelocityX(-1.0f); // Adjust the velocity as needed
					break;
				case STATE_GOING_RIGHT:
					objectlist[i]->SetVelocityX(1.0f); // Adjust the velocity as needed
					break;
				case STATE_GOING_DOWN:
					objectlist[i]->SetVelocityY(1.0f); // Adjust the velocity as needed
					break;
				case STATE_GOING_UP:
					objectlist[i]->SetVelocityY(-1.0f); // Adjust the velocity as needed
					break;
				case STATE_NONE:
					objectlist[i]->SetVelocityX(0);
					objectlist[i]->SetVelocityY(0);
					break;
				}
			}


			// Character's Movement
			if (!isMoving) {
				percentMove = 0.0f;
				if (p_player->getVelocityX() != 0.f || p_player->getVelocityY() != 0.f) {
					initialPosition = MathLib::Vector2D(p_player->getX(), p_player->getY());
					isMoving = true;
				}
			}
			else if (p_player->getVelocityX() != 0.f && p_player->getVelocityY() == 0.0f && isMoving) {
				percentMove += PLAYER_VELOCITY * dt;
				if (percentMove >= 1.0f) {
					p_player->SetPositionX(initialPosition.x + (CELL_SIZE * p_player->getVelocityX()));
					percentMove = 0.0f;
					isMoving = false;
				}
				else {
					p_player->SetPositionX(initialPosition.x + (CELL_SIZE * p_player->getVelocityX() * percentMove));
					isMoving = false;
				}
			}
			else if (p_player->getVelocityY() != 0.f && p_player->getVelocityX() == 0.0f && isMoving) {
				percentMove += PLAYER_VELOCITY * dt;
				if (percentMove >= 1.0f) {
					p_player->SetPositionY(initialPosition.y + (CELL_SIZE * p_player->getVelocityY()));
					percentMove = 0.0f;
					isMoving = false;
				}
				else {
					p_player->SetPositionY(initialPosition.y + (CELL_SIZE * p_player->getVelocityY() * percentMove));
					isMoving = false;
				}
			}

		}

		else {
			m_maplist[Duck::GetMapIndex()]->InitializeMap(objectlist, m_gameobjList, p_player, Image);
			showGrid = true;
		}

		//DUCK_TRACE("{0}", percentMove);
		if (m_ImGuiLayer->GetUpdated())
		{
			m_maplist[Duck::GetMapIndex()]->InitializeMap(objectlist, m_gameobjList, p_player, Image);
			m_ImGuiLayer->UpdateObjects(m_maplist, objectlist);
			m_ImGuiLayer->SetUpdated();


		}

		Duck::RenderCommand::SetClearColor({ 0.2, 0.2, 0.2, 1 });
		Duck::RenderCommand::Clear();



		//Debug::GetInstance()->BeginSystemProfile("Graphics");


		Duck::AABB windowAABB = aabb.ConvertToAABB(0, 0, static_cast<float>(m_maplist[Duck::GetMapIndex()]->GetHeight()), static_cast<float>(m_maplist[Duck::GetMapIndex()]->GetWidth()));
		Duck::AABB playerAABB = aabb.ConvertToAABB(static_cast<float>(p_player->getX()), static_cast<float>(p_player->getY()), static_cast<float>(CELL_SIZE), static_cast<float>(CELL_SIZE));

		if (m_phy.IsOutOfBounds(windowAABB, playerAABB)) {
			p_player->SetPositionX(static_cast<float>(m_maplist[Duck::GetMapIndex()]->SnapToCellX(static_cast<float>(CELL_SIZE), p_player->getX()))); // Adjust as needed
			p_player->SetPositionY(static_cast<float>(m_maplist[Duck::GetMapIndex()]->SnapToCellY(static_cast<float>(CELL_SIZE), p_player->getY())));
			p_player->SetVelocityX(0);
			p_player->SetVelocityY(0);
		}

		Duck::RenderCommand::SetClearColor({ 0.2, 0.2, 0.2, 1 });
		Duck::RenderCommand::Clear();

		//draw objects

		m_Graphics->StartScene();

		m_Graphics->DrawBackground(Image[OBJ_EMPTY]);


		//apply collision and textures
		for (int i{}; i < objectlist.size(); i++) {

			Duck::AABB objectAABB = aabb.ConvertToAABB(objectlist[i]->getX(), objectlist[i]->getY(), static_cast<float>(CELL_SIZE), static_cast<float>(CELL_SIZE));
			if (objectlist[i]->getObj() != OBJ_EMPTY && objectlist[i]->getObj() != OBJ_PLAYER && objectlist[i]->getObj() != OBJ_GHOST) {
				if (objectlist[i]->getObj() != OBJ_EMPTY && m_phy.CollisionIntersection_RectRect(playerAABB, { p_player->getVelocityX(), p_player->getVelocityY() }, objectAABB, { objectlist[i]->getVelocityX(), objectlist[i]->getVelocityY() }, dt)) {
					DUCK_CORE_INFO("Player: Collision Detected!");
					p_player->SetPositionX(static_cast<float>(m_maplist[Duck::GetMapIndex()]->SnapToCellX(1, p_player->getX())));
					p_player->SetPositionY(static_cast<float>(m_maplist[Duck::GetMapIndex()]->SnapToCellY(1, p_player->getY())));
					p_player->SetVelocityX(0);
					p_player->SetVelocityY(0);
				}

				m_Graphics->DrawSquareObject(objectlist[i]->getX(), objectlist[i]->getY(), CELL_SIZE, (float)ObjectOrientation, objectlist[i]->GetImage(), showBB);

			}

			
			//SET player background image as a floor tile

		}

		m_Graphics->DrawSquareObject(p_player->getX(), p_player->getY(), PlayerScale * static_cast<float>(CELL_SIZE), (float)PlayerOrientation, p_player->GetImage(), showBB);
		m_Graphics->DrawAnimation(0.f, 0.f, 1.f, 0.f,m_Animation, 1, 4, dt, showBB);
		m_Graphics->UpdateCameraPos(p_player->getX(), p_player->getY());
		m_Graphics->UpdateCameraZoom(CameraZoom);


		if (showGrid) {
			m_Graphics->ShowGrid();
		}

		m_Graphics->DrawUISquareObject(40.f, 357.5, 1.f, 0.f, 75.f, 75.f, m_InventorySlot);
		m_Graphics->DrawUISquareObject(-40.f, 357.5f, 1.f, 0.f, 75.f, 75.f, m_InventorySlot);
		m_Graphics->DrawUISquareObject(120.f, 357.5f, 1.f, 0.f, 75.f, 75.f, m_InventorySlot);
		m_Graphics->DrawUISquareObject(-120.f, 357.5f, 1.f, 0.f, 75.f, 75.f, m_InventorySlot);
		m_Graphics->DrawUISquareObject(200.f, 357.5f, 1.f, 0.f, 75.f, 75.f, m_InventorySlot);
		m_Graphics->DrawUISquareObject(-200.f, 357.5f, 1.f, 0.f, 75.f, 75.f, m_InventorySlot);
		//m_Graphics->RenderText("Inventory", 340.f, 90.f, 0.3f, glm::vec3(1.f, 1.f, 1.f), "Mine");

		graphicsSystem->Update();

		m_Graphics->EndScene();
		//m_Graphics->DrawSquareObject(static_cast<float>((m_maplist[Duck::GetMapIndex()]->SnapToCellX(1, p_player->getX()))), static_cast<float>((m_maplist[Duck::GetMapIndex()]->SnapToCellY(1.f, p_player->getY()))), CELL_SIZE, (float)PlayerOrientation, m_CharacterTexture, showBB);

		//Debug::GetInstance()->EndSystemProfile("Graphics");

		// Testing of variable watch
		//std::string deltatime = std::to_string(runtime.getDeltaTime());
		//Debug::GetInstance()->WatchVariable("DT", deltatime);

	}



	void OnEvent(Duck::Event& event) override {
		if (event.GetEventType() == Duck::EventType::KeyPressed) {
			Duck::KeyPressedEvent& keyEvent = dynamic_cast<Duck::KeyPressedEvent&>(event);
			if (keyEvent.GetKeyCode() == Duck::Key::I) {
				showImGuiWindow = !showImGuiWindow; // Toggle the window's visibility
			}
			else if (keyEvent.GetKeyCode() == Duck::Key::G) {
				GridChecker = !GridChecker;
			}
			else if (keyEvent.GetKeyCode() == Duck::Key::B) {
				showBB = !showBB;
			}
			else if (keyEvent.GetKeyCode() == Duck::Key::R) {
				PlayerOrientation = (PlayerOrientation + 90) % 360;
			}
			else if (keyEvent.GetKeyCode() == Duck::Key::T) {
				PlayerScale = (PlayerScale == 1.f) ? 2.f : (PlayerScale == 2.f) ? 0.5f : 1.f;
			}
			else if (keyEvent.GetKeyCode() == Duck::Key::Y) {
				CameraZoom = (CameraZoom == 1.f) ? 1.2f : (CameraZoom == 1.2f) ? 1.5f : 1.f;
			}

		}

		if (event.GetEventType() == Duck::EventType::KeyPressed) {
			Duck::KeyPressedEvent& keyEvent = dynamic_cast<Duck::KeyPressedEvent&>(event);
			switch (keyEvent.GetKeyCode()) {
			case Duck::Key::A:
				p_player->SetState(STATE_GOING_LEFT);
				break;
			case Duck::Key::D:
				p_player->SetState(STATE_GOING_RIGHT);
				break;
			case Duck::Key::W:
				p_player->SetState(STATE_GOING_UP);
				break;
			case Duck::Key::S:
				p_player->SetState(STATE_GOING_DOWN);
				break;
			default:
				p_player->SetState(STATE_NONE);
				break;
			}
		}
		else if (event.GetEventType() == Duck::EventType::KeyReleased) {
			Duck::KeyReleasedEvent& keyEvent = dynamic_cast<Duck::KeyReleasedEvent&>(event);
			// Reset the velocity when key is released
			switch (keyEvent.GetKeyCode()) {
			case Duck::Key::A:
			case Duck::Key::D:
				p_player->SetPositionX(static_cast<float>(m_map->SnapToCellX(1, p_player->getX())));
				p_player->SetState(STATE_NONE);
				break;
			case Duck::Key::W:
			case Duck::Key::S:
				p_player->SetPositionY(static_cast<float>(m_map->SnapToCellY(1, p_player->getY())));
				p_player->SetState(STATE_NONE);
				break;
			default:
				p_player->SetState(STATE_NONE);
				break;
			}
		}
	}

private:
	Duck::Coordinator ecs;

	std::shared_ptr<Duck::MapDataHandler> m_map;
	std::unique_ptr<Duck::Graphics> m_Graphics;
	std::unique_ptr<Duck::AssetManager> m_AssetManager{};
	Duck::ImGuiLayer* m_ImGuiLayer;

	std::vector<std::shared_ptr<Duck::GameObject>> objectlist;
	std::vector<std::shared_ptr<Duck::MapDataHandler>> m_maplist;
	std::shared_ptr<Duck::GameObject> m_gameobjList;
	std::shared_ptr<Duck::GameObject> p_player;


	std::shared_ptr<Duck::AudioSystem> audioSystem;
	std::shared_ptr<Duck::PhysicsSystem> physicsSystem;
	std::shared_ptr<Duck::GraphicsSystem> graphicsSystem;

	Duck::AABB aabb;
	Duck::PhysicsLib m_phy;

	uint32_t m_CharacterTexture;
	uint32_t m_GhostTexture;
	uint32_t m_BackgroundTexture, m_BackgroundTexture2;
	uint32_t m_InventorySlot;
	uint32_t m_Animation;

	Duck::Time runtime;
	int mapindex = 0;

	int numOfObjects;
	unsigned const int MAX_NUMBER_OF_OBJ = 30;
	unsigned const int CELL_SIZE = 1;

	const float         PLAYER_VELOCITY = 10.f;

	bool                loadFiles = false;
	bool				showGrid = false;
	bool				GridChecker = false;
	bool				showBB = false;
	MathLib::Vector2D	PlayerIniPosition{};

	int					PlayerOrientation = 0;
	float				PlayerScale = 1.f;
	float				ObjectOrientation = 0.f;
	float				CameraZoom = 1.f;
	bool				isMoving = false;
	float				percentMove{};
	MathLib::Vector2D	initialPosition{};
	uint32_t			Image[20];
	float				acceleration = 0;
	//std::shared_ptr<Duck::JiangShi> JiangShi;
};


class Sandbox : public Duck::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {
		//m_map->FreeMapData();
	}
};

Duck::Application* Duck::CreateApplication() {
	return new Sandbox();
}



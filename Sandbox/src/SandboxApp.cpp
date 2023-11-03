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
		Duck::ecs.RegisterComponent<Duck::JiangShi>();
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

		JiangShiSystem = Duck::ecs.RegisterSystem<Duck::JiangShiSystem>();
		{
			Duck::Signature signature;
			signature.set(Duck::ecs.GetComponentType<Duck::JiangShi>());
			Duck::ecs.SetSystemSignature<Duck::JiangShi>(signature);

			signature.set(Duck::ecs.GetComponentType<Duck::GameObject>());
			Duck::ecs.SetSystemSignature<Duck::GameObject>(signature);
		}
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


		static std::vector<std::filesystem::directory_entry> assetEntries;
		static std::filesystem::path currentAssetDirectory("../assets/images/");
		//std::vector<uint32_t> assets;
		for (const auto& entry : std::filesystem::directory_iterator(currentAssetDirectory)) {
			assetEntries.push_back(entry);
		}
		for (int i = 0; i < assetEntries.size(); i++) {
			std::filesystem::path entryPath = assetEntries[i].path();
			std::string assetName = entryPath.filename().string();

			std::string image = "../assets/images/" + assetName;

			Duck::Shader::LoadTexture(image.c_str());
		}
		m_InventorySlot = Duck::Shader::LoadTexture("../assets/images/InventorySlot.jpeg");
		Image[OBJ_EMPTY] = Duck::Shader::LoadTexture("../assets/images/FloorTile5.jpg");
		Image[OBJ_PLAYER] = Duck::Shader::LoadTexture("../assets/images/Character1.png");
		Image[OBJ_WALL] = Duck::Shader::LoadTexture("../assets/images/WallTile1.png");
		Image[OBJ_GHOST] = Duck::Shader::LoadTexture("../assets/images/Ghost.png");
		Image[OBJ_NPC] = Duck::Shader::LoadTexture("../assets/images/empty.png"); //not yet created
		Image[OBJ_OBJ] = Duck::Shader::LoadTexture("../assets/images/empty.png"); //not yet created
		Duck::Shader::LoadTexture("../assets/images/FloorTile2.png"); //not yet created

		//uint32_t hello = Duck::Shader::LoadTexture("../assets/images/FloorTile5.jpg");


		//m_CharacterTexture  = Duck::Shader::LoadTexture("../assets/images/Character1.png");

		/* ---------- ---------- ---------- */

		/* ---------- Load Texture ---------- */

		m_Graphics->LoadFont("../assets/fonts/Minecraft.ttf", "Mine");
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

		///* ---------- Create Entities ---------- */

		//player 

		////ghost
		//for (int i{}; i < objectlist.size(); i++) {
		//	if (objectlist[i]->getObj() == OBJ_GHOST) {
		//		p_ghost = objectlist[i];
		//		Duck::Entity ghost = Duck::ecs.CreateEntity();
		//		Duck::ecs.AddComponent<Duck::GameObject>(
		//			ghost,
		//			{ objectlist[i]->getX(), objectlist[i]->getY(), 0.0f, 0.0f, 0, STATE_NONE, OBJ_GHOST }
		//		);
		//		Duck::ecs.AddComponent<Duck::JiangShi>(
		//			ghost,
		//			{ 6.f, 2.f, 0.2f, 0.0f, 1.0f, aabb.ConvertToAABB(objectlist[i]->getX(), objectlist[i]->getY(), 1.f, 1.f), State::Idle }
		//		);

		//	}
		//}

		//audio entities
		Duck::Entity bgm = Duck::ecs.CreateEntity();
		Duck::Entity sfx1 = Duck::ecs.CreateEntity();
		Duck::Entity sfx2 = Duck::ecs.CreateEntity();
		Duck::Entity sfx3 = Duck::ecs.CreateEntity();

		Duck::ecs.AddComponent<Duck::AudioComponent>(
			bgm,
			{ "bgm", "../assets/audio/bgm.wav", true, 0.1f }
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
		//audioSystem->update();
		physicsSystem->Update(dt, CELL_SIZE);

		JiangShiSystem->Update(dt);
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
			playerMovement(dt);
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
				if (m_phy.CollisionIntersection_RectRect(playerAABB, { p_player->getVelocityX(), p_player->getVelocityY() }, objectAABB, { objectlist[i]->getVelocityX(), objectlist[i]->getVelocityY() }, dt)) {
					DUCK_CORE_INFO("Player: Collision Detected!");
					p_player->SetPositionX(static_cast<float>(m_maplist[Duck::GetMapIndex()]->SnapToCellX(1, p_player->getX())));
					p_player->SetPositionY(static_cast<float>(m_maplist[Duck::GetMapIndex()]->SnapToCellY(1, p_player->getY())));
					p_player->SetVelocityX(0);
					p_player->SetVelocityY(0);
				}
				m_Graphics->DrawSquareObject(objectlist[i]->getX(), objectlist[i]->getY(), CELL_SIZE, (float)PlayerOrientation, objectlist[i]->GetImage(), showBB);


			}
			//SET player background image as a floor tile

		}
		m_Graphics->DrawSquareObject(p_player->getX(), p_player->getY(), static_cast<float>(CELL_SIZE), (float)PlayerOrientation, p_player->GetImage(), showBB);

		m_Graphics->UpdateCameraPos(p_player->getX(), p_player->getY());
		//m_Graphics->UpdateCameraPos(5.f,5.f);


		if (showGrid) {
			m_Graphics->ShowGrid();
		}

		m_Graphics->DrawUISquareObject(40.f, 357.5, 1.f, 0.f, 75.f, 75.f, m_InventorySlot);
		m_Graphics->DrawUISquareObject(-40.f, 357.5f, 1.f, 0.f, 75.f, 75.f, m_InventorySlot);
		m_Graphics->DrawUISquareObject(120.f, 357.5f, 1.f, 0.f, 75.f, 75.f, m_InventorySlot);
		m_Graphics->DrawUISquareObject(-120.f, 357.5f, 1.f, 0.f, 75.f, 75.f, m_InventorySlot);
		m_Graphics->DrawUISquareObject(200.f, 357.5f, 1.f, 0.f, 75.f, 75.f, m_InventorySlot);
		m_Graphics->DrawUISquareObject(-200.f, 357.5f, 1.f, 0.f, 75.f, 75.f, m_InventorySlot);
		m_Graphics->RenderText("Inventory", 340.f, 90.f, 0.3f, glm::vec3(1.f, 1.f, 1.f), "Mine");



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

	void playerMovement(double dt) {
		acceleration = PLAYER_VELOCITY * dt;

		// If the player is currently moving horizontally
		if (p_player->getVelocityX() != 0.f && p_player->getVelocityY() == 0.0f) {
			// Update the player's position based on acceleration and velocity
			p_player->SetPositionX(p_player->getX() + (CELL_SIZE * p_player->getVelocityX() * acceleration));
		}
		// If the player is currently moving vertically
		else if (p_player->getVelocityY() != 0.f && p_player->getVelocityX() == 0.0f) {
			// Update the player's position based on acceleration and velocity
			p_player->SetPositionY(p_player->getY() + (CELL_SIZE * p_player->getVelocityY() * acceleration));
		}
	}

private:
	Duck::Coordinator ecs;

	std::shared_ptr<Duck::MapDataHandler> m_map;
	std::unique_ptr<Duck::Graphics> m_Graphics;
	Duck::ImGuiLayer* m_ImGuiLayer;

	std::vector<std::shared_ptr<Duck::GameObject>> objectlist;
	std::vector<std::shared_ptr<Duck::MapDataHandler>> m_maplist;
	std::shared_ptr<Duck::GameObject> m_gameobjList;
	std::shared_ptr<Duck::GameObject> p_player;


	std::shared_ptr<Duck::AudioSystem> audioSystem;
	std::shared_ptr<Duck::PhysicsSystem> physicsSystem;

	Duck::AABB aabb;
	Duck::PhysicsLib m_phy;

	uint32_t m_CharacterTexture;
	uint32_t m_GhostTexture;
	uint32_t m_BackgroundTexture, m_BackgroundTexture2;
	uint32_t m_InventorySlot;

	std::shared_ptr<Duck::JiangShiSystem> JiangShiSystem;

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
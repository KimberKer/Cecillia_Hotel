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
		//Duck::ecs.RegisterComponent<Duck::JiangShi>();
		/* ---------- ---------- ---------- */

		///* ---------- Register Systems -> init system ---------- */
		audioSystem = Duck::ecs.RegisterSystem<Duck::AudioSystem>();
		{
			Duck::Signature signature;
			signature.set(Duck::ecs.GetComponentType<Duck::AudioComponent>());
			Duck::ecs.SetSystemSignature<Duck::AudioSystem>(signature);
		}
		audioSystem->init();

		/*JiangShi = Duck::ecs.RegisterSystem<Duck::JiangShi>();
		{
			Duck::Signature signature;
			signature.set(Duck::ecs.GetComponentType<Duck::JiangShi>());
			Duck::ecs.SetSystemSignature<Duck::JiangShi>(signature);
		}*/
		/* ---------- ---------- ---------- */

		///* ---------- Create Entities ---------- */

		//player 

		//ghost
		/*Duck::Entity ghost = Duck::ecs.CreateEntity();
		Duck::ecs.AddComponent<Duck::JiangShi>(
			ghost,
			{ 6.f, 3.f, 0.2f, 0.0f, 1.0f, aabb.ConvertToAABB(7.f, 7.f, 1.f, 1.f) }
		);*/

		for (std::vector<std::shared_ptr<Duck::GameObject>>::iterator i{ objectlist.begin() }; i != objectlist.end(); ++i)
		{
			Duck::GameObject* gameObj = i->get();
			if (gameObj) {
				Duck::Entity object = Duck::ecs.CreateEntity();
				Duck::ecs.AddComponent<Duck::GameObject>(
					object,
					{ gameObj->getX(), gameObj->getY(), gameObj->getVelocityX(),
					gameObj->getVelocityY(), gameObj->getgridCollisionFlag(),
					gameObj->GetImage(), gameObj->getState(), gameObj->getObj() }
				);
			}
		}

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
		/* ---------- Map Functions ---------- */
		std::shared_ptr<Duck::MapDataHandler> map1 = std::make_shared<Duck::MapDataHandler>("../txtfiles/Map/map1.txt");
		m_maplist.push_back(map1);

		// Create and add the second map to the list
		std::shared_ptr<Duck::MapDataHandler> map2 = std::make_shared<Duck::MapDataHandler>("../txtfiles/Map/map2.txt");
		m_maplist.push_back(map2);

		/* ---------- ---------- ---------- */

		/* ---------- Load Texture ---------- */

		m_Graphics = std::unique_ptr<Duck::Graphics>(new Duck::Graphics);


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
			//std::cout << image.c_str() << std::endl;
		}

		Duck::Shader::LoadTexture("../assets/images/empty.png");
		Image[OBJ_EMPTY] = Duck::Shader::LoadTexture("../assets/images/FloorTile1.png");
		Image[OBJ_PLAYER] = Duck::Shader::LoadTexture("../assets/images/Character1.png");
		Image[OBJ_WALL] = Duck::Shader::LoadTexture("../assets/images/WallTile1.png");
		Image[OBJ_GHOST] = Duck::Shader::LoadTexture("../assets/images/Ghost.png");
		Image[OBJ_NPC] = Duck::Shader::LoadTexture("../assets/images/empty.png"); //not yet created
		Image[OBJ_OBJ] = Duck::Shader::LoadTexture("../assets/images/empty.png"); //not yet created
		Duck::Shader::LoadTexture("../assets/images/FloorTile2.png"); //not yet created

		//uint32_t hello = Duck::Shader::LoadTexture("../assets/images/FloorTile5.jpg");


		//m_CharacterTexture  = Duck::Shader::LoadTexture("../assets/images/Character1.png");

		/* ---------- ---------- ---------- */

		/* ---------- Set Gridsize of Game ---------- */
		m_Graphics->SetGridSize(static_cast<int>(m_maplist[Duck::GetMapIndex()]->GetHeight()));
		/* ---------- ---------- ---------- */

		/* ---------- Audio ---------- */
		/*m_Audio = std::shared_ptr<Duck::Audio>(new Duck::Audio);
		m_SoundInfo = std::shared_ptr<Duck::SoundInfo>(new Duck::SoundInfo("test", "../Duck/src/Duck/Audio/Sfx/SCI-FI.wav"));
		m_Audio->init();
		m_Audio->loadSound(m_SoundInfo);*/
		/* ---------- ---------- ---------- */

	
		
		/* ---------- Game Objects ---------- */
		//create a list of game objects
		//m_gameobjList = new Duck::GameObject[MAX_NUMBER_OF_OBJ];

		// Creating the objects based on the map 
		//InitializeMap();
		m_maplist[Duck::GetMapIndex()]->InitializeMap(objectlist, m_gameobjList, p_player, m_Jiangshi, Image);

		//prints map
		m_maplist[Duck::GetMapIndex()]->printMapData();

		/* ---------- ---------- ---------- */

			/* ---------- Ghost Functions ---------- */
		// Load waypoint coordinates for Ghost
		m_Jiangshi.ReadWaypointsFromFile("../txtfiles/waypoints.txt");


		// Initialize Jiangshi Ghost
		m_Jiangshi.SetGhostProperties(
			m_maplist[Duck::GetMapIndex()]->GetGhostPositionX(),	// Position x
			m_maplist[Duck::GetMapIndex()]->GetGhostPositionY(),	// Position y
			0.f,	// Velocity x
			0.f,	// Velocity y
			12.f,	// Roam duration
			2.0f,	// Idle duration
			0.2f,	// Roam speed
			0.0f,	// Chase speed
			1.0f,	// Max chase speed
			aabb.ConvertToAABB(9.f, 9.f, 1.f, 1.f));
		std::cout << m_maplist[Duck::GetMapIndex()]->GetGhostPositionX() << std::endl;
		// Bounding box
			/* ---------- ---------- ---------- */

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

		if (isGamePlaying) {

		///* ---------- Updating Systems ---------- */
		//audioSystem->update();
		if (!m_ImGuiLayer->GetGhostChanged()) {
			m_Jiangshi.Jiangshi(dt, p_player);	

		}
		/* ---------- ---------- ---------- */
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

			if (m_ImGuiLayer->GetUpdated())
			{
				m_maplist[Duck::GetMapIndex()]->InitializeMap(objectlist, m_gameobjList, p_player, m_Jiangshi, Image);
				m_ImGuiLayer->UpdateObjects(m_maplist, objectlist);
				m_ImGuiLayer->SetUpdated();

				m_Jiangshi.SetGhostProperties(
					m_maplist[Duck::GetMapIndex()]->GetGhostPositionX(),	// Position x
					m_maplist[Duck::GetMapIndex()]->GetGhostPositionY(),	// Position y
					0.f,	// Velocity x
					0.f,	// Velocity y
					12.f,	// Roam duration
					2.0f,	// Idle duration
					0.2f,	// Roam speed
					0.0f,	// Chase speed
					1.0f,	// Max chase speed
					aabb.ConvertToAABB(9.f, 9.f, 1.f, 1.f));
				std::cout << m_maplist[Duck::GetMapIndex()]->GetGhostPositionX() << std::endl;

			}
		}


		else {
			m_maplist[Duck::GetMapIndex()]->InitializeMap(objectlist, m_gameobjList, p_player, m_Jiangshi,Image);
			m_Jiangshi.SetGhostPositionX(m_maplist[Duck::GetMapIndex()]->GetGhostPositionX());
			m_Jiangshi.SetGhostPositionY(m_maplist[Duck::GetMapIndex()]->GetGhostPositionY());
			showGrid = true;
		}

		DUCK_TRACE("{0}", percentMove);

		Duck::RenderCommand::SetClearColor({ 0.2, 0.2, 0.2, 1 });
		Duck::RenderCommand::Clear();

		// Would be used for cameras
		Duck::Renderer::BeginScene();

		//Debug::GetInstance()->BeginSystemProfile("Graphics");
		// Would be used for cameras
		Duck::Renderer::BeginScene();

		Duck::AABB windowAABB = aabb.ConvertToAABB(0, 0, m_maplist[Duck::GetMapIndex()]->GetHeight(), m_maplist[Duck::GetMapIndex()]->GetWidth());
		Duck::AABB playerAABB = aabb.ConvertToAABB(p_player->getX(), p_player->getY(), CELL_SIZE, CELL_SIZE);

		if (m_phy.IsOutOfBounds(windowAABB, playerAABB)) {
			p_player->SetPositionX(static_cast<float>(m_maplist[Duck::GetMapIndex()]->SnapToCellX(CELL_SIZE, p_player->getX()))); // Adjust as needed
			p_player->SetPositionY(static_cast<float>(m_maplist[Duck::GetMapIndex()]->SnapToCellY(CELL_SIZE, p_player->getY())));
			p_player->SetVelocityX(0);
			p_player->SetVelocityY(0);
		}


		//draw objects
		m_Graphics->DrawBackground(Image[OBJ_EMPTY]);


		for (int i{}; i < objectlist.size(); i++) {
			Duck::AABB objectAABB = aabb.ConvertToAABB(objectlist[i]->getX(), objectlist[i]->getY(), CELL_SIZE, CELL_SIZE);
			Duck::AABB ghostAABB = aabb.ConvertToAABB(m_Jiangshi.GetGhostPositionX(), m_Jiangshi.GetGhostPositionY(), CELL_SIZE, CELL_SIZE);
			if (objectlist[i]->getObj() != OBJ_PLAYER && objectlist[i]->getObj() != OBJ_GHOST) {
				if (objectlist[i]->getObj() != OBJ_EMPTY && m_phy.CollisionIntersection_RectRect(playerAABB, { p_player->getVelocityX(), p_player->getVelocityY() }, objectAABB, { objectlist[i]->getVelocityX(), objectlist[i]->getVelocityY() }, dt)) {
					DUCK_CORE_INFO("Player: Collision Detected!");
					p_player->SetPositionX(static_cast<float>(m_maplist[Duck::GetMapIndex()]->SnapToCellX(1, p_player->getX())));
					p_player->SetPositionY(static_cast<float>(m_maplist[Duck::GetMapIndex()]->SnapToCellY(1, p_player->getY())));
					p_player->SetVelocityX(0);
					p_player->SetVelocityY(0);
					isMoving = false;
				}
				//wall collides with ghost
				if ((objectlist[i]->getObj() != OBJ_EMPTY && m_phy.CollisionIntersection_RectRect(ghostAABB, { m_Jiangshi.getVelocityX(), m_Jiangshi.getVelocityY() }, objectAABB, { objectlist[i]->getVelocityX(), objectlist[i]->getVelocityY() }, dt))) {
					m_Jiangshi.SetGhostPositionX(static_cast<float>(m_maplist[Duck::GetMapIndex()]->SnapToCellX(1, m_Jiangshi.GetGhostPositionX())));
					m_Jiangshi.SetGhostPositionY(static_cast<float>(m_maplist[Duck::GetMapIndex()]->SnapToCellY(1, m_Jiangshi.GetGhostPositionY())));
					m_Jiangshi.SetVelocityX(0);
					m_Jiangshi.SetVelocityY(0);
				}
		
				m_Graphics->DrawSquareObject(objectlist[i]->getX(), objectlist[i]->getY(), CELL_SIZE, (float)PlayerOrientation, objectlist[i]->GetImage(), showBB);
				
			}
		}
		if (!m_ImGuiLayer->GetGhostChanged()) {
			m_Graphics->DrawSquareObject(static_cast<float>((m_map->SnapToCellX(1, m_Jiangshi.GetGhostPositionX()))), static_cast<float>((m_map->SnapToCellY(1.f, m_Jiangshi.GetGhostPositionY()))), CELL_SIZE, (float)PlayerOrientation, Image[OBJ_GHOST], showBB);
		}
		m_Graphics->DrawSquareObject(p_player->getX(), p_player->getY(), CELL_SIZE, (float)PlayerOrientation, p_player->GetImage(), showBB);

		if (showGrid) {
			m_Graphics->ShowGrid();
		}
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
private:
	Duck::Coordinator ecs;

	Duck::Ghost m_Jiangshi;
	std::shared_ptr<Duck::SoundInfo> m_SoundInfo;
	std::shared_ptr<Duck::MapDataHandler> m_map;
	std::unique_ptr<Duck::Graphics> m_Graphics;
	Duck::ImGuiLayer* m_ImGuiLayer;

	std::vector<std::shared_ptr<Duck::GameObject>> objectlist;
	std::vector<std::shared_ptr<Duck::MapDataHandler>> m_maplist;
	std::shared_ptr<Duck::GameObject> m_gameobjList;
	std::shared_ptr<Duck::GameObject> p_player;

	Duck::AABB aabb;
	Duck::PhysicsLib m_phy;

	uint32_t m_CharacterTexture;
	uint32_t m_GhostTexture;
	uint32_t m_BackgroundTexture2;

	Duck::Time runtime;
	int mapindex = 0;

	int numOfObjects;
	unsigned const int MAX_NUMBER_OF_OBJ = 30;
	unsigned const int CELL_SIZE = 1;

	const float         PLAYER_VELOCITY = 20.f;

	bool                loadFiles = false;
	bool				showGrid = false;
	bool				GridChecker = false;
	bool				showBB = false;

	int					PlayerOrientation = 0;
	bool				isMoving = false;
	float				percentMove{};
	MathLib::Vector2D	initialPosition{};
	uint32_t			Image[20];

	std::shared_ptr<Duck::AudioSystem> audioSystem;
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
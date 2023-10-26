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
		//ecs.Init();

		///* ---------- Register Components ---------- */
		//ecs.RegisterComponent<Duck::AudioComponent>();

		///* ---------- Register Systems -> init system ---------- */
		//audioSystem = ecs.RegisterSystem<Duck::AudioSystem>();
		//{
		//	Duck::Signature signature;
		//	signature.set(ecs.GetComponentType<Duck::AudioComponent>());
		//	ecs.SetSystemSignature<Duck::AudioSystem>(signature);
		//}
		//audioSystem->init();

		///* ---------- Create Entities ---------- */
		//Duck::Entity audio1 = ecs.CreateEntity();

		//ecs.AddComponent<Duck::AudioComponent>(
		//	audio1,
		//	{ "oof", "../Duck/src/Duck/Audio/assets/oof.wav" }
		//);
		/* ---------- ---------- ---------- */

		/* ---------- Map Functions ---------- */
		m_map = std::shared_ptr<Duck::MapDataHandler>(new Duck::MapDataHandler);

		// Getting information from map file.
		m_map->GetMapData("../txtfiles/map.txt");

		// Print map layout to console
		m_map->printMapData();
		/* ---------- ---------- ---------- */

		/* ---------- Load Texture ---------- */
		m_Graphics = std::unique_ptr<Duck::Graphics>(new Duck::Graphics);
		m_CharacterTexture = Duck::Shader::LoadTexture("../images/Character1.png");
		m_GhostTexture = Duck::Shader::LoadTexture("../images/Ghost.png");
		m_BackgroundTexture = Duck::Shader::LoadTexture("../images/FloorTile1.png");
		m_BackgroundTexture2 = Duck::Shader::LoadTexture("../images/FloorTile2.png");

		/* ---------- ---------- ---------- */

		/* ---------- Set Gridsize of Game ---------- */
		m_Graphics->SetGridSize(static_cast<int>(m_map->GetHeight()));
		/* ---------- ---------- ---------- */


		/* ---------- Audio ---------- */
		/*m_Audio = std::shared_ptr<Duck::Audio>(new Duck::Audio);
		m_SoundInfo = std::shared_ptr<Duck::SoundInfo>(new Duck::SoundInfo("test", "../Duck/src/Duck/Audio/Sfx/SCI-FI.wav"));
		m_Audio->init();
		m_Audio->loadSound(m_SoundInfo);*/
		/* ---------- ---------- ---------- */

		/* ---------- Ghost Functions ---------- */
		// Load waypoint coordinates for Ghost
		//m_Jiangshi.ReadWaypointsFromFile("../txtfiles/waypoints.txt");
		m_Jiangshi.ReadWaypointsFromFile("../txtfiles/waypoints.txt");

		// Initialize Jiangshi Ghost
		m_Jiangshi.SetGhostProperties(
			7.f,	// Position x
			7.f,	// Position y
			0.f,	// Velocity x
			0.f,	// Velocity y
			6.f,	// Roam duration
			3.0f,	// Idle duration
			0.2f,	// Roam speed
			0.0f,	// Chase speed
			1.0f,	// Max chase speed
			aabb.ConvertToAABB(7.f, 7.f, 1.f, 1.f));	// Bounding box
		/* ---------- ---------- ---------- */

		/* ---------- Game Objects ---------- */
		//create a list of game objects
		numOfObjects = 0;
		//m_gameobjList = new Duck::GameObject[MAX_NUMBER_OF_OBJ];

		// Creating the objects based on the map 
		for (int i{}; i < m_map->GetWidth(); i++) {
			for (int j{}; j < m_map->GetHeight(); j++) {
				if (numOfObjects < MAX_NUMBER_OF_OBJ) {
					int cellValue = m_map->GetCellValue(i, j);
					switch (cellValue) {
					case 0:
						break;
						//player
					case 1:
						objectlist.push_back(m_gameobjList->CreateObj(i, j, STATE_NONE, OBJ_PLAYER));
						numOfObjects++;
						break;
					case 2:
						objectlist.push_back(m_gameobjList->CreateObj(i, j, STATE_NONE, OBJ_OBJ));
						numOfObjects++;
						break;
					case 3:
						objectlist.push_back(m_gameobjList->CreateObj(i, j, STATE_NONE, OBJ_GHOST));
						numOfObjects++;
						break;
					default:
						break;
					}
				}
			}
		}

		for (int i{}; i < objectlist.size(); i++) {
			if (objectlist[i]->getObj() == OBJ_PLAYER) {
				p_player = objectlist[i];
			}
		}
		/* ---------- ---------- ---------- */

		m_ImGuiLayer = new Duck::ImGuiLayer(m_map, objectlist);
		m_ImGuiLayer->SetName("ImGui");
		Duck::Application::Get().PushOverlay(m_ImGuiLayer);
	}

	void OnUpdate() override {

		runtime.update();
		static auto startTime = std::chrono::high_resolution_clock::now();

		// Inside your game loop
		auto currentTime = std::chrono::high_resolution_clock::now();
		double frameTime = std::chrono::duration<double>(currentTime - startTime).count();
		startTime = currentTime;

		// Calculate FPS
		fps = 1.0 / frameTime;
		float dt = static_cast<float>(runtime.getDeltaTime());

		//updating systems
		//audioSystem->update();
		if (isGamePlaying) {
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

			if (!isMoving) {
				percentMove = 0.0f;
				if (p_player->getVelocityX() != 0.f || p_player->getVelocityY() != 0.f) {
					initialPosition = std::make_pair(p_player->getX(), p_player->getY());
					isMoving = true;
				}
			}
			else if (p_player->getVelocityX() != 0.f && p_player->getVelocityY() == 0.0f) {
				isMoving = true;
				percentMove += PLAYER_VELOCITY * dt;

				if (percentMove <= 1.0f) {
					p_player->SetPositionX(initialPosition.first + (CELL_SIZE * p_player->getVelocityX() * PLAYER_VELOCITY));
					percentMove = 0.0f;
					isMoving = false;
				}
				else {
					p_player->SetPositionX(initialPosition.first + (CELL_SIZE * p_player->getVelocityX() * percentMove));
				}
			}
			else if (p_player->getVelocityY() != 0.f && p_player->getVelocityX() == 0.0f) {
				isMoving = true;
				percentMove += PLAYER_VELOCITY * dt;

				if (percentMove <= 1.0f) {
					p_player->SetPositionY(initialPosition.second + (CELL_SIZE * p_player->getVelocityY() * PLAYER_VELOCITY));
					percentMove = 0.0f;
					isMoving = false;
				}
				else {
					p_player->SetPositionY(initialPosition.second + (CELL_SIZE * p_player->getVelocityY() * percentMove));
				}
			}
			else {
				isMoving = false;
			}

			Duck::RenderCommand::SetClearColor({ 0.2, 0.2, 0.2, 1 });
			Duck::RenderCommand::Clear();

			// Would be used for cameras
			Duck::Renderer::BeginScene();

			//Debug::GetInstance()->BeginSystemProfile("Graphics");
			// Would be used for cameras
			Duck::Renderer::BeginScene();

			// Ghost Function
			m_Jiangshi.Jiangshi(dt, p_player);

		}
			Duck::AABB windowAABB = aabb.ConvertToAABB(0, 0, m_map->GetHeight(), m_map->GetWidth());
			Duck::AABB playerAABB = aabb.ConvertToAABB(p_player->getX(), p_player->getY(), CELL_SIZE, CELL_SIZE);

			if (m_phy.IsOutOfBounds(windowAABB, playerAABB)) {
				p_player->SetPositionX(static_cast<float>(m_map->SnapToCellX(CELL_SIZE, p_player->getX()))); // Adjust as needed
				p_player->SetPositionY(static_cast<float>(m_map->SnapToCellY(CELL_SIZE, p_player->getY())));
				p_player->SetVelocityX(0);
				p_player->SetVelocityY(0);
			}


			//draw objects
			m_Graphics->DrawBackground(m_BackgroundTexture);


			for (int i{}; i < objectlist.size(); i++) {
				Duck::AABB objectAABB = aabb.ConvertToAABB(objectlist[i]->getX(), objectlist[i]->getY(), CELL_SIZE, CELL_SIZE);
				if (objectlist[i]->getObj() == OBJ_OBJ) {
					if (m_phy.CollisionIntersection_RectRect(playerAABB, { p_player->getVelocityX(), p_player->getVelocityY() }, objectAABB, { objectlist[i]->getVelocityX(), objectlist[i]->getVelocityY() }, dt)) {
						DUCK_CORE_INFO("Player: Collision Detected!");
						p_player->SetPositionX(static_cast<float>(m_map->SnapToCellX(1, p_player->getX())));
						p_player->SetPositionY(static_cast<float>(m_map->SnapToCellY(1, p_player->getY())));
						p_player->SetVelocityX(0);
						p_player->SetVelocityY(0);
					}
					else if (p_player->getState() != STATE_NONE) {
						//DUCK_CORE_INFO("Player: No Collision Detected!");
					}
					m_Graphics->DrawSquareObject(objectlist[i]->getX(), objectlist[i]->getY(), CELL_SIZE, (float)PlayerOrientation, m_BackgroundTexture2, showBB);
				}

			}
			m_Graphics->DrawSquareObject(static_cast<float>((m_map->SnapToCellX(1, m_Jiangshi.GetGhostPositionX()))), static_cast<float>((m_map->SnapToCellY(1.f, m_Jiangshi.GetGhostPositionY()))), CELL_SIZE, (float)PlayerOrientation, m_GhostTexture, showBB);

			m_Graphics->DrawSquareObject(p_player->getX(), p_player->getY(), CELL_SIZE, (float)PlayerOrientation, m_CharacterTexture, showBB);

			if (showGrid) {
				m_Graphics->ShowGrid();
			}
			//m_Graphics->DrawSquareObject(static_cast<float>((m_map->SnapToCellX(1, p_player->getX()))), static_cast<float>((m_map->SnapToCellY(1.f, p_player->getY()))), CELL_SIZE, (float)PlayerOrientation, m_CharacterTexture, showBB);

			//Debug::GetInstance()->EndSystemProfile("Graphics");

			// Testing of variable watch
			//std::string deltatime = std::to_string(runtime.getDeltaTime());
			//Debug::GetInstance()->WatchVariable("DT", deltatime);

			//Debug::GetInstance()->BeginSystemProfile("Audio");
			//KRISTY - testing audio manager
			//m_Audio->playSound(m_SoundInfo);
			//Debug::GetInstance()->EndSystemProfile("Audio");

		
		}

		void OnEvent(Duck::Event & event) override {

			if (event.GetEventType() == Duck::EventType::KeyPressed) {
				Duck::KeyPressedEvent& keyEvent = dynamic_cast<Duck::KeyPressedEvent&>(event);
				if (keyEvent.GetKeyCode() == Duck::Key::I) {
					showImGuiWindow = !showImGuiWindow; // Toggle the window's visibility
				
				}
				else if (keyEvent.GetKeyCode() == Duck::Key::G) {
					showGrid = !showGrid;
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
				case Duck::Key::W:
				case Duck::Key::S:
					p_player->SetState(STATE_NONE);
				default:
					p_player->SetState(STATE_NONE);
					break;
				}
			}


		}

private:
	//Duck::Coordinator ecs;

	//std::shared_ptr<Duck::AudioSystem> audioSystem;

	std::shared_ptr<Duck::SoundInfo> m_SoundInfo;
	//std::shared_ptr<Duck::Audio> m_Audio;
	std::shared_ptr<Duck::MapDataHandler> m_map;
	std::unique_ptr<Duck::Graphics> m_Graphics;
	Duck::ImGuiLayer* m_ImGuiLayer;

	std::vector<std::shared_ptr<Duck::GameObject>> objectlist;
	std::shared_ptr<Duck::GameObject> m_gameobjList;
	std::shared_ptr<Duck::GameObject> p_player;
	//std::shared_ptr<Duck::GameObject> p_Jiangshi;

	Duck::AABB aabb;
	Duck::PhysicsLib m_phy;

	uint32_t m_CharacterTexture;
	uint32_t m_GhostTexture;
	uint32_t m_BackgroundTexture, m_BackgroundTexture2;

	Duck::Ghost m_Jiangshi;

	Duck::Time runtime;

	int numOfObjects;
	unsigned const int MAX_NUMBER_OF_OBJ = 30;
	unsigned const int CELL_SIZE = 1;

	const float         PLAYER_VELOCITY = .5f;

	bool                loadFiles = false;
	bool				showGrid = false;
	bool				showBB = false;

	int					PlayerOrientation = 0;
	bool				isMoving = false;
	float				percentMove = 0.0f;
	std::pair<float, float>	initialPosition{};
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
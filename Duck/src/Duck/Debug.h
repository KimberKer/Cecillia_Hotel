#pragma once
#include <GLFW/glfw3.h>
#include <string>
#include <map>


	class Debug
	{
	private:
		int frameCount;
		double accumulateTime;

		std::map<std::string, double> systemProfileStartTime;

		std::map<std::string, double> systemProfileDuration;

	public:
		Debug();
		~Debug();

		void Initialize(GLFWwindow* window);
		void CleanDebug();

		void BeginSystemProfile(const std::string& SystemName);
		double EndSystemProfile(const std::string& SystemName);

		void Update(double deltaTime);

		double GetSystemDuration(const std::string& systemName);

	};



#include "World08.h"
#include "Core/Core.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"

using namespace std;

int main(int argc, char* argv[])
{
	INFO_LOG("Initialize Engine...")

	//nc::MemoryTracker::Initialize();
	nc::seedRandom((unsigned int)time(nullptr));
	nc::setFilePath("assets");

	ENGINE.Initialize();

	auto world = make_unique<nc::World08>();
	world->Initialize();

	string testString = "THIS is a TEST string";
	cout << nc::StringUtils::ToUpper(testString) << endl;
	cout << nc::StringUtils::ToLower(testString) << endl;
	if (nc::StringUtils::IsEqualIgnoreCase(nc::StringUtils::ToUpper(testString), nc::StringUtils::ToLower(testString)))
	{
		cout << "true" << endl;
	}
	cout << nc::StringUtils::CreateUnique(testString);

	// main loop
	bool quit = false;
	while (!quit)
	{
		// update
		ENGINE.Update();
		quit = ENGINE.IsQuit();

		world->Update(ENGINE.GetTime().GetDeltaTime());

		// draw
		world->Draw(*ENGINE.GetSystem<nc::Renderer>());
	}

	world->Shutdown();
	ENGINE.Shutdown();

	return 0;
}

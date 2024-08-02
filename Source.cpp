#ifndef SOURCE_H
#define SOURCE_H

#include <vector>
#include "TestApp.h"
//#include "Model.h"
#include "DDSReader.h"
#include "WICTextureLoader.h"

using namespace Axiom;
using namespace std;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	// Refactor the BaseWin32Application class so that it works without passing an instance handle to it.
	/*TestApp app(hInstance);
	app.Run();*/

	// Create an instance of the importer class.
	//Assimp::Importer importer;

	//// Read the given file with some postprocessing.
	//const aiScene* scene = importer.ReadFile("E:\\Dev\\Axiom\\DamagedHelmet.glb",
	//	aiProcess_CalcTangentSpace |
	//	aiProcess_Triangulate |
	//	aiProcess_JoinIdenticalVertices |
	//	aiProcess_SortByPType);

	//Model model("E:\\Dev\\Axiom\\DamagedHelmet.glb");

	Axiom::LoadTextureFromFilename(L"E:\\Dev\\Axiom\\1353436.png");
	
	return 0;
}

#endif

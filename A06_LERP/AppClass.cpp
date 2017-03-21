#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Assignment  06 - LERP"); // Window Name
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), ZERO_V3, REAXISY);

	// Color of the screen
	m_v4ClearColor = vector4(REBLACK, 1); // Set the clear color to black

	m_pMeshMngr->LoadModel("Sorted\\WallEye.bto", "WallEye");

	fDuration = 1.0f;
}

void AppClass::Update(void)
{
#pragma region Does not change anything here
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
#pragma endregion

#pragma region Does not need changes but feel free to change anything here
	//Lets us know how much time has passed since the last call
	double fTimeSpan = m_pSystem->LapClock(); //Delta time (between frame calls)

	//cumulative time
	static double fRunTime = 0.0f; //How much time has passed since the program started
	fRunTime += fTimeSpan; 
#pragma endregion

#pragma region Your Code goes here

	// GetTcikCount returns a DWORD, a long that doesn't have a sign
	static DWORD timerSinceBoot = GetTickCount();
	// current time - time since boot = total time the program has been running
	DWORD timerSinceStart = GetTickCount() - timerSinceBoot;

	// GetTickCount gives millisecond, divide by 1000 to get seconds
	static float fTimer = 0.0f;
	fTimer = timerSinceStart / 1000.0f;

	// float to subtract from percentage to keep it a value between 0.0 and 1.0
	// I use this because fTimer keeps increasing based on the program run time, which eventually goes past 1s
	static float percentageSubtractor = 0.0f;

	// int to keep track of index of the point location array
	static int arrayPositionTracker;

	// Print the information
	// printLine like console.writeline
	// print same thing but doesn't make new line
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->PrintLine("Total Time:" + std::to_string(fTimer));

	
	// Vector3 array to hold vector3's for locations
	static vector3* locationArray = new vector3[11];
	// Make the vector translations for a point locations
	locationArray[0] = vector3(-4.0f, -2.0f, 5.0f);
	locationArray[1] = vector3(1.0f, -2.0f, 5.0f);
	locationArray[2] = vector3(-3.0f, -1.0f, 3.0f);
	locationArray[3] = vector3(2.0f, -1.0f, 3.0f);
	locationArray[4] = vector3(-2.0f, 0.0f, 0.0f);
	locationArray[5] = vector3(3.0f, 0.0f, 0.0f);
	locationArray[6] = vector3(-1.0f, 1.0f, -3.0f);
	locationArray[7] = vector3(4.0f, 1.0f, -3.0f);
	locationArray[8] = vector3(0.0f, 2.0f, -5.0f);
	locationArray[9] = vector3(5.0f, 2.0f, -5.0f);
	locationArray[10] = vector3(1.0f, 3.0f, -5.0f);

	// Matrix4 array to hold Matrices for locations
	static matrix4* locationMatrices = new matrix4[11];
	// Make matrices for all point locations
	// First translate them to the correct location
	locationMatrices[0] = glm::translate(locationArray[0]);
	locationMatrices[1] = glm::translate(locationArray[1]);
	locationMatrices[2] = glm::translate(locationArray[2]);
	locationMatrices[3] = glm::translate(locationArray[3]);
	locationMatrices[4] = glm::translate(locationArray[4]);
	locationMatrices[5] = glm::translate(locationArray[5]);
	locationMatrices[6] = glm::translate(locationArray[6]);
	locationMatrices[7] = glm::translate(locationArray[7]);
	locationMatrices[8] = glm::translate(locationArray[8]);
	locationMatrices[9] = glm::translate(locationArray[9]);
	locationMatrices[10] = glm::translate(locationArray[10]);

	// Then scale them to 0.1f
	locationMatrices[0] = glm::scale(locationMatrices[0], vector3(0.1f, 0.1f, 0.1f));
	locationMatrices[1] = glm::scale(locationMatrices[1], vector3(0.1f, 0.1f, 0.1f));
	locationMatrices[2] = glm::scale(locationMatrices[2], vector3(0.1f, 0.1f, 0.1f));
	locationMatrices[3] = glm::scale(locationMatrices[3], vector3(0.1f, 0.1f, 0.1f));
	locationMatrices[4] = glm::scale(locationMatrices[4], vector3(0.1f, 0.1f, 0.1f));
	locationMatrices[5] = glm::scale(locationMatrices[5], vector3(0.1f, 0.1f, 0.1f));
	locationMatrices[6] = glm::scale(locationMatrices[6], vector3(0.1f, 0.1f, 0.1f));
	locationMatrices[7] = glm::scale(locationMatrices[7], vector3(0.1f, 0.1f, 0.1f));
	locationMatrices[8] = glm::scale(locationMatrices[8], vector3(0.1f, 0.1f, 0.1f));
	locationMatrices[9] = glm::scale(locationMatrices[9], vector3(0.1f, 0.1f, 0.1f));
	locationMatrices[10] = glm::scale(locationMatrices[10], vector3(0.1f, 0.1f, 0.1f));

	// Render spheres at all point locations
	m_pMeshMngr->AddSphereToRenderList(locationMatrices[0], RERED, WIRE);
	m_pMeshMngr->AddSphereToRenderList(locationMatrices[1], RERED, WIRE);
	m_pMeshMngr->AddSphereToRenderList(locationMatrices[2], RERED, WIRE);
	m_pMeshMngr->AddSphereToRenderList(locationMatrices[3], RERED, WIRE);
	m_pMeshMngr->AddSphereToRenderList(locationMatrices[4], RERED, WIRE);
	m_pMeshMngr->AddSphereToRenderList(locationMatrices[5], RERED, WIRE);
	m_pMeshMngr->AddSphereToRenderList(locationMatrices[6], RERED, WIRE);
	m_pMeshMngr->AddSphereToRenderList(locationMatrices[7], RERED, WIRE);
	m_pMeshMngr->AddSphereToRenderList(locationMatrices[8], RERED, WIRE);
	m_pMeshMngr->AddSphereToRenderList(locationMatrices[9], RERED, WIRE);
	m_pMeshMngr->AddSphereToRenderList(locationMatrices[10], RERED, WIRE);

	// Start and end vectors for LERP
	vector3 v3Start;
	vector3 v3End;

	// Set the start and end vectors with arrayPositionTracker and arrayPositionTracker + 1
	// If the start vector is the last position, set the end position to the 0 index
	if (arrayPositionTracker < 10) {
		v3Start = locationArray[arrayPositionTracker];
		v3End = locationArray[arrayPositionTracker + 1];
	}
	else {
		v3Start = locationArray[arrayPositionTracker];
		v3End = locationArray[0];
	}
	
	// MapValue(original value to map, current min, current max, new min, new max)
	float percentage = MapValue(fTimer, 0.0f, fDuration, 0.0f, 1.0f);
	
	// Subtract the percentageSubtractor from the percentage to make it a value between 0.0 and 1.0
	// (Probably an easier way to do this but it works)
	percentage -= percentageSubtractor;

	// Check if the percentage is greater than the duration (1.0)
	// if so, reset and increment values
	if (percentage > fDuration) {
		percentage = 1.0f; // make sure percentage does not go above 1.0 (will leave path)
		percentageSubtractor += 1.0f; // incremement percentageSubtractor by 1
		if (arrayPositionTracker < 10) {
			arrayPositionTracker += 1;
		}
		else {
			arrayPositionTracker = 0;
			percentage = 0.0f;
		}
		
	}

	// Use LERP to get the current translation
	vector3 v3Current = glm::lerp(v3Start, v3End, percentage);
	// Matrix for WallEye transformations
	matrix4 m4WallEye;
	// translate the WallEye matrix
	m4WallEye = glm::translate(v3Current);

	// Draw the percentage to the Screen
	m_pMeshMngr->PrintLine("Percentage:" + std::to_string(percentage));

	// Matrix, Color, MeshRender (WIRE, SOLID, WIRE | SOLID)
	// Update the matrix of the model
	m_pMeshMngr->SetModelMatrix(m4WallEye, "WallEye");
#pragma endregion

#pragma region Does not need changes but feel free to change anything here
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//std::cout << nFPS << std::endl;

	//Print info on the screen
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->PrintLine(std::to_string(nFPS), RERED);

	
	


	
#pragma endregion
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	//Render the grid based on the camera's mode:
	m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}
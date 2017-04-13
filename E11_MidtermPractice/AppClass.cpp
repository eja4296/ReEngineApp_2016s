#include "AppClass.h"
void AppClass::Update(void)
{
#pragma region DOES NOT NEED CHANGES
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
#pragma endregion
#pragma region FEEL FREE TO USE THIS CLOCK
	//Calculate delta and total times
	static double dTotalTime = 0.0; //Total time of the simulation
	double dDeltaTime = m_pSystem->LapClock(); //time difference between function calls
	dTotalTime += dDeltaTime; //Incrementing the time differences 
#pragma endregion
#pragma region YOUR CODE GOES HERE
	m_m4Steve = glm::mat4(1.0f); // same as m_m4Steve = IDENTITY_M4; setting the identity to steve

	static float timer1 = 0.0f;
	static bool posDirection = true;

	// change direction of translation
	if (timer1 > 5.0f) {
		posDirection = false;
	}
	if (timer1 < 0.0f) {
		posDirection = true;
	}

	if (posDirection == true) {
		timer1 += (float)dDeltaTime;
	}
	else {
		timer1 -= dDeltaTime;
	}
	
	// Rotation first
	static float rotation = 0.0f;

	float rotAngle = 360.0 / 5.0;

	rotation += rotAngle * dDeltaTime;
	
	m_m4Steve = glm::rotate(m_m4Steve, rotation, vector3(0.0f, 0.0f, 1.0f));

	// Translation second
	vector3 v3Start = vector3(0.0f, 0.0f, 0.0f);
	vector3 v3End = vector3(0.0f, 5.0f, 0.0f);

	float percentage = MapValue(timer1, 0.0f, 5.0f, 0.0f, 1.0f);

	vector3 v3Current = glm::lerp(v3Start, v3End, percentage);

	m_m4Steve = glm::translate(m_m4Steve, v3Current);


	

#pragma endregion
#pragma region DOES NOT NEED CHANGES
	//Set the model matrix
	m_pMeshMngr->SetModelMatrix(m_m4Steve, "Steve");
	
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//Print info on the screen
	m_pMeshMngr->PrintLine("");//Add a line on top
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("Seconds:");
	m_pMeshMngr->PrintLine(std::to_string(dTotalTime), RERED);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
}

#include "AppClass.h"
void AppClass::Update(void)
{
#pragma region DOES NOT NEED CHANGES
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
	static float fTimer = 0.0f;//creates a timer
	static uint uClock = m_pSystem->GenClock();//ask the system for a new clock id
	float fDeltaTime = m_pSystem->LapClock(uClock);//lap the selected clock
	fTimer += fDeltaTime;//add the delta time to the current clock
#pragma endregion

#pragma region YOUR CODE GOES HERE
	modelMatrix = IDENTITY_M4;

	// Own timer and bool checker
	static float timer1 = 0.0f;
	static bool posDirection = true;

	// change direction of translation
	if (timer1 >= 1.0f) {
		posDirection = false;
	}
	if (timer1 <= 0.0f) {
		posDirection = true;
	}
	if (posDirection == true) {
		timer1 += (float)fDeltaTime;
	}
	else {
		timer1 -= (float)fDeltaTime;
	}

	// Lerp for y translation, 1 second up to (0,3,0) and 1 second back to (0,0,0)
	vector3 v3Start = vector3(0.0f, 0.0f, 0.0f);
	vector3 v3End = vector3(0.0f, 3.0f, 0.0f);
	static float percentage1 = 0.0f;
	percentage1 = MapValue(timer1, 0.0f, 1.0f, 0.0f, 1.0f);
	vector3 v3Current = glm::lerp(v3Start, v3End, percentage1);

	modelMatrix = glm::translate(modelMatrix, v3Current);


	// rotation animation for 2 seconds, twice 360 degrees around the tip of the sword in the z axis
	quaternion quat1 = glm::angleAxis(0.0f, vector3(0.0f, 0.0f, 1.0f));
	quaternion quat2 = glm::angleAxis(359.0f, vector3(0.0f, 0.0f, 1.0f));
	static float percentage2 = 0.0f;
	percentage2 = MapValue(fTimer, 0.0f, 1.0f, 0.0f, 1.0f);
	quaternion quat3 = glm::mix(quat1, quat2, percentage2);

	modelMatrix *= glm::mat4_cast(quat3);

#pragma endregion

#pragma region DOES NOT NEED CHANGES
	m_pMeshMngr->SetModelMatrix(modelMatrix, 0);//Set the model matrix to the model

	m_pMeshMngr->AddSkyboxToRenderList();//Adds a skybox to the renderlist
	m_pMeshMngr->AddInstanceToRenderList("ALL"); //Adds all loaded instances to the render list

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine("");//Add a line on top
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->PrintLine("Timer: ");
	m_pMeshMngr->PrintLine(std::to_string(fTimer), REGREEN);

	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->PrintLine(std::to_string(nFPS), RERED);
#pragma endregion
}


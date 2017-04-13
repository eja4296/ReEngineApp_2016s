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

	// rotation for 2.5 seconds
	quaternion quat1 = glm::angleAxis(359.0f, vector3(0.0f, 0.0f, 1.0f));
	quaternion quat2 = glm::angleAxis(0.0f, vector3(0.0f, 0.0f, 1.0f));
	static float percentage = 0.0f;
	percentage = MapValue(fTimer, 0.0f, 2.5f, 0.0f, 1.0f);
	quaternion quat3 = glm::mix(quat1, quat2, percentage);
	modelMatrix *= glm::mat4_cast(quat3);

	// translation to 3 units away
	modelMatrix = glm::translate(modelMatrix, vector3(0.0f, -3.0f, 0.0f));

	// Counteract shield rotation so it always points down
	quat1 = glm::angleAxis(0.0f, vector3(0.0f, 0.0f, 1.0f));
	quat2 = glm::angleAxis(359.0f, vector3(0.0f, 0.0f, 1.0f));
	percentage = 0.0f;
	percentage = MapValue(fTimer, 0.0f, 2.5f, 0.0f, 1.0f);
	quat3 = glm::mix(quat1, quat2, percentage);
	modelMatrix *= glm::mat4_cast(quat3);

	// reset timer and percentage after completing a full roation
	if (fTimer > 2.5) {
		percentage = 0;
		fTimer = 0;
	}

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
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
}


#include "AppClass.h"

void AppClass::InitWindow(String a_sWindowName)
{
	//Using Base InitWindow method
	super::InitWindow("E12 - Instance Rendering");
	m_v4ClearColor = vector4(REBLACK, 1.0f);
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), vector3(0.0f, 0.0f, 0.0f), REAXISY);

	m_pMesh = new MyMesh();
	
	//Creating the Mesh points
	m_pMesh->AddVertexPosition(vector3(-1.0f, 0.0f, 0.0f));
	m_pMesh->AddVertexColor(RERED);
	m_pMesh->AddVertexPosition(vector3(1.0f, 0.0f, 0.0f));
	m_pMesh->AddVertexColor(REBLUE);
	m_pMesh->AddVertexPosition(vector3(0.0f, 1.0f, 0.0f));
	m_pMesh->AddVertexColor(REGREEN);

	/*
	m_pMesh->AddVertexPosition(vector3(-1.0f,  1.0f, 0.0f));
	m_pMesh->AddVertexColor(REBLUE);
	m_pMesh->AddVertexPosition(vector3(1.0f, -1.0f, 0.0f));
	m_pMesh->AddVertexColor(REBLUE);
	m_pMesh->AddVertexPosition(vector3( 1.0f, 1.0f, 0.0f));
	m_pMesh->AddVertexColor(REBLUE);
	*/

	//Compiling the mesh
	m_pMesh->CompileOpenGL3X();
}

void AppClass::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->UpdateTime();

	//Is the arcball active?
	if (m_bArcBall == true)
		ArcBall();

	//Is the first person camera active?
	if (m_bFPC == true)
		CameraRotation();

	//Calculate Camera
	m_pCameraMngr->CalculateView();

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	printf("FPS: %d            \r", nFPS);//print the Frames per Second
										  //Print info on the screen
	m_pMeshMngr->PrintLine("");//Add a line on top
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	ClearScreen();
	
	//Matrices from the camera
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();

	//m_pMesh->Render(m4Projection, m4View, IDENTITY_M4);//Rendering nObject(s)	

	// MY CODE
	bool drawLeft = true;
	const int NUM_OF_ITERATIONS = 16;
	int pascalsTriangle[NUM_OF_ITERATIONS][NUM_OF_ITERATIONS];

	// Create Pascal's Triangle
	for (int i = 0; i < NUM_OF_ITERATIONS; i++) {
		
		for (int j = 0; j < i + 1; j++) {
			pascalsTriangle[i][j] = 1;
			if (i >= 2 && j > 0 && j < i) {
				pascalsTriangle[i][j] = pascalsTriangle[i - 1][j - 1] + pascalsTriangle[i - 1][j];
			}
			/*
			m_pMeshMngr->Print(std::to_string(pascalsTriangle[i][j]));
			m_pMeshMngr->Print(":");
			*/
		}
		//m_pMeshMngr->PrintLine("");
	}

	int numOfTrianlges = 1;
	
	// Make Sierpinski's Trianlge
	for (int i = 0; i < NUM_OF_ITERATIONS; i++) {

		for (int j = 0; j < numOfTrianlges; j++) {

			// compare interation position with position in Pascal's Triangle
			if (pascalsTriangle[i][j] % 2 == 0) {
				// DO NOTHING FOR EVEN NUMBERS
			}
			else {
				// DRAW FOR ODD NUMBERS
				m_pMesh->Render(m4Projection, m4View, glm::translate(vector3((-i + (j * 2)), -i, 0.0f)));
			}
		}
		numOfTrianlges++;
	}


	// Tried to do it with only 1 Render call but it would not work
	/*
	m_fMatrixArray = new float[m_nObjects * 16];
	for (int nObject = 0; nObject < m_nObjects; nObject++)
	{
		const float* m4MVP;

		for (int i = 0; i < NUM_OF_ITERATIONS; i++) {

			for (int j = 0; j < numOfTrianlges; j++) {

				// compare interation position with position in Pascal's Triangle
				if (pascalsTriangle[i][j] % 2 == 0) {
					// DO NOTHING FOR EVEN NUMBERS
				}
				else {
					// DRAW FOR ODD NUMBERS
					
					m4MVP = glm::value_ptr(
						glm::translate(vector3((-i + (j * 2)), -i, 0.0f))
						);
					memcpy(&m_fMatrixArray[nObject * 16], m4MVP, 16 * sizeof(float));
				}
			}
			numOfTrianlges++;
		}
	}
	*/

	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	SafeDelete(m_fMatrixArray);
	if (m_pMesh != nullptr)
	{
		delete m_pMesh;
		m_pMesh = nullptr;
	}
	super::Release();
}
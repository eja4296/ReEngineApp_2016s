#include "MyBoundingBoxClass.h"

MyBoundingBoxClass::MyBoundingBoxClass(std::vector<vector3> vertexList)
{
	m_bColliding = false;
	m_fRadius = 0.0f;
	m_v3CenterGlobal = vector3(0.0f);

	if (vertexList.size() < 1)
		return;

	m_v3Min = vertexList[0];
	m_v3Max = vertexList[0];

	


	for (int i = 1; i < vertexList.size(); i++)
	{
		if (m_v3Min.x > vertexList[i].x)
		{
			m_v3Min.x = vertexList[i].x;
		}
		else if (m_v3Max.x < vertexList[i].x)
		{
			m_v3Max.x = vertexList[i].x;
		}

		if (m_v3Min.y > vertexList[i].y)
		{
			m_v3Min.y = vertexList[i].y;
		}
		else if (m_v3Max.y < vertexList[i].y)
		{
			m_v3Max.y = vertexList[i].y;
		}

		if (m_v3Min.z > vertexList[i].z)
		{
			m_v3Min.z = vertexList[i].z;
		}
		else if (m_v3Max.z < vertexList[i].z)
		{
			m_v3Max.z = vertexList[i].z;
		}
	}

	// Set Min X
	if (m_v3MinNewBox.x > m_v3Min.x)
	{
		m_v3MinNewBox.x = m_v3Min.x;
	}
	if(m_v3MinNewBox.x > m_v3Min.y)
	{
		m_v3MinNewBox.x = m_v3Min.y;
	}
	if(m_v3MinNewBox.x > m_v3Min.z)
	{
		m_v3MinNewBox.x = m_v3Min.z;
	}

	// Set Min Y
	if (m_v3MinNewBox.y > m_v3Min.x)
	{
		m_v3MinNewBox.y = m_v3Min.x;
	}
	if(m_v3MinNewBox.y > m_v3Min.y)
	{
		m_v3MinNewBox.y = m_v3Min.y;
	}
	if(m_v3MinNewBox.y > m_v3Min.z)
	{
		m_v3MinNewBox.y = m_v3Min.z;
	}

	// Set Min Y
	if (m_v3MinNewBox.z > m_v3Min.x)
	{
		m_v3MinNewBox.z = m_v3Min.x;
	}
	if (m_v3MinNewBox.z > m_v3Min.y)
	{
		m_v3MinNewBox.z = m_v3Min.y;
	}
	if (m_v3MinNewBox.z > m_v3Min.z)
	{
		m_v3MinNewBox.z = m_v3Min.z;
	}

	// Set Max X
	if(m_v3MaxNewBox.x < m_v3Max.x)
	{
		m_v3MaxNewBox.x = m_v3Max.x;
	}
	if(m_v3MaxNewBox.x < m_v3Max.y)
	{
		m_v3MaxNewBox.x = m_v3Max.y;
	}
	if (m_v3MaxNewBox.x < m_v3Max.z)
	{
		m_v3MaxNewBox.x = m_v3Max.z;
	}

	// Set Max Y
	if (m_v3MaxNewBox.y < m_v3Max.x)
	{
		m_v3MaxNewBox.y = m_v3Max.x;
	}
	if (m_v3MaxNewBox.y < m_v3Max.y)
	{
		m_v3MaxNewBox.y = m_v3Max.y;
	}
	if (m_v3MaxNewBox.y < m_v3Max.z)
	{
		m_v3MaxNewBox.y = m_v3Max.z;
	}

	// Set Max Z
	if (m_v3MaxNewBox.z < m_v3Max.x)
	{
		m_v3MaxNewBox.z = m_v3Max.x;
	}
	if (m_v3MaxNewBox.z < m_v3Max.y)
	{
		m_v3MaxNewBox.z = m_v3Max.y;
	}
	if (m_v3MaxNewBox.z < m_v3Max.z)
	{
		m_v3MaxNewBox.z = m_v3Max.z;
	}

	//m_v3MinNewBox.x = ;
	//m_v3MaxNewBox;

	m_v3CenterLocal = m_v3CenterGlobal = (m_v3Max + m_v3Min) / 2.0f;
	m_fRadius = glm::distance(m_v3CenterGlobal, m_v3Max);
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	m_v3Size = m_v3Max - m_v3Min;

	m_v3MinG = m_v3Min;
	m_v3MaxG = m_v3Max;

	m_v3CenterLocalNewBox = m_v3CenterGlobalNewBox = (m_v3MaxNewBox + m_v3MinNewBox) / 2.0f;
	m_fRadiusNewBox = glm::distance(m_v3CenterGlobalNewBox, m_v3MaxNewBox);
	//m_pMeshMngr = MeshManagerSingleton::GetInstance();
	m_v3SizeNewBox = m_v3MaxNewBox - m_v3MinNewBox;

	m_v3MinNewBoxG = m_v3MinNewBox;
	m_v3MaxNewBoxG = m_v3MaxNewBox;
	
	//m_v3Size.x = glm::distance(vector3(m_v3Min.x, 0.0, 0.0), vector3(m_v3Max.x, 0.0, 0.0));
	//m_v3Size.y = glm::distance(vector3(0.0, m_v3Min.y, 0.0), vector3(0.0, m_v3Max.y, 0.0));
	//m_v3Size.z = glm::distance(vector3(0.0, 0.0, m_v3Min.z), vector3(0.0, 0.0, m_v3Max.z));
}

void MyBoundingBoxClass::RenderSphere()
{
	vector3 v3Color = REGREEN;
	if (true == m_bColliding)
		v3Color = RERED;

	m_pMeshMngr->AddCubeToRenderList(
		m_m4ToWorld *
		glm::translate(m_v3CenterLocal) *
		glm::scale(m_v3Size),
		v3Color, WIRE);

	

	m_pMeshMngr->AddCubeToRenderList(
		m_m4ToWorldNewBox *
		glm::translate(m_v3CenterLocalNewBox) *
		glm::scale(m_v3SizeNewBox),
		v3Color, WIRE);
}
void MyBoundingBoxClass::SetModelMatrix(matrix4 a_m4ToWorld)
{
	if (m_m4ToWorld == a_m4ToWorld)
		return;

	m_m4ToWorld = a_m4ToWorld;
	m_v3CenterGlobal = vector3(m_m4ToWorld * vector4(m_v3CenterLocal, 1.0f));
	m_v3MinG = vector3(m_m4ToWorld * vector4(m_v3Min, 1.0f));
	m_v3MaxG = vector3(m_m4ToWorld * vector4(m_v3Max, 1.0f));

	// Set Min X
	if (m_v3MinNewBox.x > m_v3Min.x)
	{
		m_v3MinNewBox.x = m_v3Min.x;
	}
	if (m_v3MinNewBox.x > m_v3Min.y)
	{
		m_v3MinNewBox.x = m_v3Min.y;
	}
	if (m_v3MinNewBox.x > m_v3Min.z)
	{
		m_v3MinNewBox.x = m_v3Min.z;
	}

	// Set Min Y
	if (m_v3MinNewBox.y > m_v3Min.x)
	{
		m_v3MinNewBox.y = m_v3Min.x;
	}
	if (m_v3MinNewBox.y > m_v3Min.y)
	{
		m_v3MinNewBox.y = m_v3Min.y;
	}
	if (m_v3MinNewBox.y > m_v3Min.z)
	{
		m_v3MinNewBox.y = m_v3Min.z;
	}

	// Set Min Y
	if (m_v3MinNewBox.z > m_v3Min.x)
	{
		m_v3MinNewBox.z = m_v3Min.x;
	}
	if (m_v3MinNewBox.z > m_v3Min.y)
	{
		m_v3MinNewBox.z = m_v3Min.y;
	}
	if (m_v3MinNewBox.z > m_v3Min.z)
	{
		m_v3MinNewBox.z = m_v3Min.z;
	}

	// Set Max X
	if (m_v3MaxNewBox.x < m_v3Max.x)
	{
		m_v3MaxNewBox.x = m_v3Max.x;
	}
	if (m_v3MaxNewBox.x < m_v3Max.y)
	{
		m_v3MaxNewBox.x = m_v3Max.y;
	}
	if (m_v3MaxNewBox.x < m_v3Max.z)
	{
		m_v3MaxNewBox.x = m_v3Max.z;
	}

	// Set Max Y
	if (m_v3MaxNewBox.y < m_v3Max.x)
	{
		m_v3MaxNewBox.y = m_v3Max.x;
	}
	if (m_v3MaxNewBox.y < m_v3Max.y)
	{
		m_v3MaxNewBox.y = m_v3Max.y;
	}
	if (m_v3MaxNewBox.y < m_v3Max.z)
	{
		m_v3MaxNewBox.y = m_v3Max.z;
	}

	// Set Max Z
	if (m_v3MaxNewBox.z < m_v3Max.x)
	{
		m_v3MaxNewBox.z = m_v3Max.x;
	}
	if (m_v3MaxNewBox.z < m_v3Max.y)
	{
		m_v3MaxNewBox.z = m_v3Max.y;
	}
	if (m_v3MaxNewBox.z < m_v3Max.z)
	{
		m_v3MaxNewBox.z = m_v3Max.z;
	}


	m_v3CenterLocalNewBox = m_v3CenterGlobalNewBox = (m_v3MaxNewBox + m_v3MinNewBox) / 2.0f;
	m_fRadiusNewBox = glm::distance(m_v3CenterGlobalNewBox, m_v3MaxNewBox);
	//m_pMeshMngr = MeshManagerSingleton::GetInstance();
	m_v3SizeNewBox = m_v3MaxNewBox - m_v3MinNewBox;

	m_v3MinNewBoxG = m_v3MinNewBox;
	m_v3MaxNewBoxG = m_v3MaxNewBox;

	m_m4ToWorldNewBox = a_m4ToWorld;
	m_v3CenterGlobalNewBox = vector3(m_m4ToWorldNewBox * vector4(m_v3CenterLocalNewBox, 1.0f));
	m_v3MinNewBoxG = vector3(m_m4ToWorldNewBox * vector4(m_v3MinNewBox, 1.0f));
	m_v3MaxNewBoxG = vector3(m_m4ToWorldNewBox * vector4(m_v3MaxNewBox, 1.0f));
}

bool MyBoundingBoxClass::IsColliding(MyBoundingBoxClass* a_other)
{
	if (this->m_v3MaxG.x < a_other->m_v3MinG.x)
		return false;
	if (this->m_v3MinG.x > a_other->m_v3MaxG.x)
		return false;

	if (this->m_v3MaxG.y < a_other->m_v3MinG.y)
		return false;
	if (this->m_v3MinG.y > a_other->m_v3MaxG.y)
		return false;

	if (this->m_v3MaxG.z < a_other->m_v3MinG.z)
		return false;
	if (this->m_v3MinG.z > a_other->m_v3MaxG.z)
		return false;

	return true;
}

void MyBoundingBoxClass::SetColliding(bool input) { m_bColliding = input; }
void MyBoundingBoxClass::SetCenterLocal(vector3 input) { m_v3CenterLocal = input; }
void MyBoundingBoxClass::SetCenterGlobal(vector3 input) { m_v3CenterGlobal = input; }
void MyBoundingBoxClass::SetRadius(float input) { m_fRadius = input; }
bool MyBoundingBoxClass::GetColliding(void) { return m_bColliding; }
vector3 MyBoundingBoxClass::GetCenterLocal(void) { return m_v3CenterLocal; }
vector3 MyBoundingBoxClass::GetCenterGlobal(void) { return m_v3CenterGlobal; }
float MyBoundingBoxClass::GetRadius(void) { return m_fRadius; }
matrix4 MyBoundingBoxClass::GetModelMatrix(void) { return m_m4ToWorld; }
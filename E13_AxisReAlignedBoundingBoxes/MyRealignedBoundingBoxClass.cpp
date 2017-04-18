#include "MyRealignedBoundingBoxClass.h"

MyRealignedBoundingBoxClass::MyRealignedBoundingBoxClass(std::vector<vector3> vertexList)
{
	m_bColliding = false;
	m_fRadius = 0.0f;
	m_v3CenterGlobal = vector3(0.0f);

	newVertexList = vertexList;

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

	m_v3CenterLocal = m_v3CenterGlobal = (m_v3Max + m_v3Min) / 2.0f;
	m_fRadius = glm::distance(m_v3CenterGlobal, m_v3Max);
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	m_v3Size = m_v3Max - m_v3Min;

	m_v3MinG = m_v3Min;
	m_v3MaxG = m_v3Max;

	//m_v3Size.x = glm::distance(vector3(m_v3Min.x, 0.0, 0.0), vector3(m_v3Max.x, 0.0, 0.0));
	//m_v3Size.y = glm::distance(vector3(0.0, m_v3Min.y, 0.0), vector3(0.0, m_v3Max.y, 0.0));
	//m_v3Size.z = glm::distance(vector3(0.0, 0.0, m_v3Min.z), vector3(0.0, 0.0, m_v3Max.z));
}

void MyRealignedBoundingBoxClass::RenderSphere()
{
	vector3 v3Color = REGREEN;
	if (true == m_bColliding)
		v3Color = RERED;

	m_pMeshMngr->AddCubeToRenderList(
		glm::translate(m_v3CenterGlobal) *
		m_m4ToWorld *
		glm::translate(m_v3CenterLocal) *
		glm::inverse(m_m4ToWorld) *
		glm::scale(vector3(newScale) * 2.0f),
		v3Color,
		WIRE);

}
void MyRealignedBoundingBoxClass::SetModelMatrix(matrix4 a_m4ToWorld)
{
	if (m_m4ToWorld == a_m4ToWorld)
		return;

	m_m4ToWorld = a_m4ToWorld;
	m_v3CenterGlobal = vector3(m_m4ToWorld * vector4(m_v3CenterLocal, 1.0f));
	

	for (int i = 0; i < newVertexList.size(); i++)
	{
		newVertexList[i] = vector3(m_m4ToWorld * vector4(newVertexList[i], 1.0f));
	}

	// Tried to reset min and max so it resizes but still not what it should look like
	m_v3Min = vector3(0.0f, 0.0f, 0.0f);
	m_v3Max = vector3(0.0f, 0.0f, 0.0f);

	for (int i = 1; i < newVertexList.size(); i++)
	{
		if (m_v3Min.x > newVertexList[i].x)
		{
			m_v3Min.x = newVertexList[i].x;
		}
		else if (m_v3Max.x < newVertexList[i].x)
		{
			m_v3Max.x = newVertexList[i].x;
		}

		if (m_v3Min.y > newVertexList[i].y)
		{
			m_v3Min.y = newVertexList[i].y;
		}
		else if (m_v3Max.y < newVertexList[i].y)
		{
			m_v3Max.y = newVertexList[i].y;
		}

		if (m_v3Min.z > newVertexList[i].z)
		{
			m_v3Min.z = newVertexList[i].z;
		}
		else if (m_v3Max.z < newVertexList[i].z)
		{
			m_v3Max.z = newVertexList[i].z;
		}
	}

	newScale = m_v3Max - m_v3Min;

}

bool MyRealignedBoundingBoxClass::IsColliding(MyRealignedBoundingBoxClass* a_other)
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
/*
MyRealignedBoundingBoxClass::MyRealignedBoundingBoxClass() {

}
*/
void MyRealignedBoundingBoxClass::SetColliding(bool input) { m_bColliding = input; }
void MyRealignedBoundingBoxClass::SetCenterLocal(vector3 input) { m_v3CenterLocal = input; }
void MyRealignedBoundingBoxClass::SetCenterGlobal(vector3 input) { m_v3CenterGlobal = input; }
void MyRealignedBoundingBoxClass::SetRadius(float input) { m_fRadius = input; }
bool MyRealignedBoundingBoxClass::GetColliding(void) { return m_bColliding; }
vector3 MyRealignedBoundingBoxClass::GetCenterLocal(void) { return m_v3CenterLocal; }
vector3 MyRealignedBoundingBoxClass::GetCenterGlobal(void) { return m_v3CenterGlobal; }
float MyRealignedBoundingBoxClass::GetRadius(void) { return m_fRadius; }
matrix4 MyRealignedBoundingBoxClass::GetModelMatrix(void) { return m_m4ToWorld; }